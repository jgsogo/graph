include (GenerateExportHeader)

#------------------------------------------
#   List source files
file(GLOB _headers "*.h")
file(GLOB _src "*.cpp")
set(SRC_FILES
	${_headers}
	${_src}	
	config.h.in
	CMakeLists.txt
	)

# Looking for boost
include_directories( ${Boost_INCLUDE_DIRS} )

#------------------------------------------
#   Add export macro and
#       remove useless warnings

if(WIN32)
# remove warning C4275: se ha utilizado una interfaz no de DLL class
# remove warning C4996: 'standard function': This function or variable may be unsafe...
# remove warning C4251: 'atribute' : class 'name' necesita tener una interfaz DLL...

add_definitions(-D_CRT_SECURE_NO_WARNINGS /wd4275 /wd4251)
endif(WIN32)

#macro
#ConfigFile()
configure_file(config.h.in "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY)


#------------------------------------------
#        Build a library
add_definitions(-D_UNICODE -DUNICODE /Zm110)
add_compiler_export_flags()
add_library(graph STATIC ${SRC_FILES})
generate_export_header(graph)

use_precompiled_header2(
    graph
    "stdafx.h"
    "stdafx.cpp"
    ${_src}	
    )
	
set_target_properties(graph PROPERTIES
  PUBLIC_HEADER "search_algorithm.h;depth_first_search.h;breadth_first_search.h;visitor.h;traits.h;chart_impl.h;graph.h;chart_traits.h;vertex_traits.h;edge_traits.h;events.h;${CMAKE_CURRENT_BINARY_DIR}/config.h;${CMAKE_CURRENT_BINARY_DIR}/graph_export.h;"
  LINKER_LANGUAGE CXX
  FOLDER "core")

  
install(TARGETS graph
  # IMPORTANT: Add the config library to the "export-set"
  EXPORT core-targets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" COMPONENT lib  
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/core/graph"
    COMPONENT graph)
