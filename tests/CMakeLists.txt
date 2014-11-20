
message(STATUS "--------------- Tests ---------------")

#SET(CTEST_OUTPUT_ON_FAILURE TRUE)

# We need boost as shared library for unit_tests
set(Old_Boost_USE_STATIC_LIBS ${Boost_USE_STATIC_LIBS})
set(Old_Boost_USE_STATIC_RUNTIME ${Boost_USE_STATIC_RUNTIME})

set(Boost_USE_STATIC_LIBS OFF CACHE INTERNAL "") 
set(Boost_USE_STATIC_RUNTIME OFF CACHE INTERNAL "")

BoostInstall(unit_test_framework)

add_definitions(-DBOOST_TEST_DYN_LINK)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${LOKI_INCLUDE_DIRS})

get_filename_component(UTF_BASE_NAME ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY_RELEASE} NAME_WE)
get_filename_component(UTF_PATH ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY_RELEASE} PATH)
set(UTF_FULLPATH_RELEASE "${UTF_PATH}/${UTF_BASE_NAME}.dll")

get_filename_component(UTF_BASE_NAME_DEBUG ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY_DEBUG} NAME_WE)
get_filename_component(UTF_PATH_DEBUG ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY_RELEASE} PATH)
set(UTF_FULLPATH_DEBUG "${UTF_PATH_DEBUG}/${UTF_BASE_NAME_DEBUG}.dll")


# Custom target to pass tests automatically on compilation
add_custom_target(_ALL_TESTS)
set_target_properties(_ALL_TESTS PROPERTIES
  LINKER_LANGUAGE CXX
  FOLDER "tests"
  EXCLUDE_FROM_ALL TRUE)
add_custom_command(TARGET _ALL_TESTS POST_BUILD COMMAND ${CMAKE_CTEST_COMMAND} --verbose --extra-verbose -C $<CONFIGURATION>)


# Add all test projects
add_subdirectory(status_track)
add_subdirectory(comunication)
add_subdirectory(settings)
add_subdirectory(graph)


# Revert boost variables, just in case
set(Boost_USE_STATIC_LIBS ${Old_Boost_USE_STATIC_LIBS})
set(Boost_USE_STATIC_RUNTIME ${Old_Boost_USE_STATIC_RUNTIME})