
add_test(NAME core/graph COMMAND graph_tests)

file(GLOB _sources "*.cpp")
file(GLOB _headers "*.h")
add_executable(graph_tests
                ${_sources}
                ${_headers}
                )
target_link_libraries(graph_tests graph)

set_target_properties(graph_tests PROPERTIES
  LINKER_LANGUAGE CXX
  FOLDER "tests/core")
  
 
# Credit: http://www.cmake.org/pipermail/cmake/2011-August/045966.html
set(DEST_LIBNAME "${CMAKE_CURRENT_BINARY_DIR}/${LIBNAME}")


function(copy_deps DEBUG RELEASE RELWITHDEBINFO what)
	add_custom_command(TARGET graph_tests POST_BUILD
		COMMAND ${CMAKE_COMMAND}
		-DCONFIG=$<CONFIGURATION>
		-DFULLPATH_RELEASE=${RELEASE}
		-DFULLPATH_RELWITHDEBINFO=${RELWITHDEBINFO}
		-DFULLPATH_DEBUG=${DEBUG}
		-DDEST_LIBNAME=${DEST_LIBNAME}
		-P ${CMAKE_SOURCE_DIR}/tests/copy_file_configuration.cmake
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Copying ${what}"
		VERBATIM
		)
endfunction(copy_deps)

function(copy_dependency target)
	get_target_property(DEP_LOCATION_DEBUG ${target} LOCATION_Debug)
	get_target_property(DEP_LOCATION_RELEASE ${target} LOCATION_Release)
	get_target_property(DEP_LOCATION_RELWITHDEBINFO ${target} LOCATION_RelWithDebInfo)
	copy_deps(${DEP_LOCATION_DEBUG} ${DEP_LOCATION_RELEASE} ${DEP_LOCATION_RELWITHDEBINFO} "${target}")
endfunction(copy_dependency)

function(copy_imported_dependency target)
	get_target_property(DEP_LOCATION_DEBUG ${target} IMPORTED_LOCATION_DEBUG)
	get_target_property(DEP_LOCATION_RELEASE ${target} IMPORTED_LOCATION_RELEASE)
	get_target_property(DEP_LOCATION_RELWITHDEBINFO ${target} IMPORTED_LOCATION_RELWITHDEBINFO)
	copy_deps(${DEP_LOCATION_DEBUG} ${DEP_LOCATION_RELEASE} ${DEP_LOCATION_RELWITHDEBINFO} "${target}")
endfunction(copy_imported_dependency)

#	- copy UTF
copy_deps(${UTF_FULLPATH_DEBUG} ${UTF_FULLPATH_RELEASE} ${UTF_FULLPATH_RELEASE} "Boost Unit Test Framework")

#	- copy dependencies
copy_dependency(trackelement)
copy_dependency(topology)

copy_imported_dependency(status_track)
