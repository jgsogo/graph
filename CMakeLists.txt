cmake_minimum_required(VERSION 2.8)
project(core CXX)

set(CORE_MAJOR_VERSION 1)
set(CORE_MINOR_VERSION 0)
set(CORE_PATCH_VERSION 0)
set(CORE_VERSION
  ${CORE_MAJOR_VERSION}.${CORE_MINOR_VERSION}.${CORE_PATCH_VERSION})

# Set default for CMAKE_INSTALL_PREFIX
SET(CORE_INSTALL_PREFIX "C:/libraries/core" CACHE PATH "Prefix prepended to
install directories")
SET(CMAKE_INSTALL_PREFIX "${CORE_INSTALL_PREFIX}" CACHE INTERNAL "Prefix
prepended to install directories" FORCE)
  
# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/CMake/core)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")
  
# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

# set up include-directories
include_directories(
  "${PROJECT_SOURCE_DIR}"   # to find core/whatever/whatever.h
  "${PROJECT_BINARY_DIR}")  # to find core/whatever/config.h

OPTION(BUILD_EXAMPLES "Build examples" OFF)
OPTION(BUILD_TESTS "Build tests" ON)


# Look for VLD
include(depends/cmake/FindVLD.cmake)
if(VLD_FOUND)
	if(${BUILD_TESTS})
		message(WARNING "There is an issue regarding VLD and Boost Unit Testing (see #182). No VLD will be included if BUILD_TESTS is defined")
	else()	
		include_directories( ${VLD_INCLUDE_DIR} )
		add_definitions(-D_VLD)
	endif()
endif()

# Activate solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Activate testing
enable_testing()

# Add sub-directories
add_subdirectory(core)
if(${BUILD_EXAMPLES})
	add_subdirectory(examples) 
endif()

if(${BUILD_TESTS})
	add_subdirectory(tests)
endif()


# The interesting stuff goes here
# ===============================

# Add all targets to the build-tree export set
#export(TARGETS core FILE "${PROJECT_BINARY_DIR}/core-targets.cmake")

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE core)

# Create the core-config.cmake and core-config-version files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(core-config.cmake.in
  "${PROJECT_BINARY_DIR}/core-config.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${CORE_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(core-config.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/core-config.cmake" @ONLY)
# ... for both
configure_file(core-config-version.cmake.in
  "${PROJECT_BINARY_DIR}/core-config-version.cmake" @ONLY)

# Install the core-config.cmake and core-config-version.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/core-config.cmake"
  "${PROJECT_BINARY_DIR}/core-config-version.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

# Install the export set for use with the install-tree
install(EXPORT core-targets DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

  
message(STATUS "Files will be installed at ${CMAKE_INSTALL_PREFIX}")