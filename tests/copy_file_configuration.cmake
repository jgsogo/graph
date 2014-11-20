
if(CONFIG STREQUAL Release)
	execute_process(COMMAND ${CMAKE_COMMAND} -E copy "${FULLPATH_RELEASE}" "${DEST_LIBNAME}Release/"
		RESULT_VARIABLE resultado
 		ERROR_VARIABLE erro)
	MESSAGE ("resultado: " ${resultado})
	MESSAGE ("erro: " ${erro})
endif()

if(CONFIG STREQUAL RelWithDebInfo)
	execute_process(COMMAND ${CMAKE_COMMAND} -E copy "${FULLPATH_RELWITHDEBINFO}" "${DEST_LIBNAME}RelWithDebInfo/"
		RESULT_VARIABLE resultado
 		ERROR_VARIABLE erro)
	MESSAGE ("resultado: " ${resultado})
	MESSAGE ("erro: " ${erro})
endif()

if(CONFIG STREQUAL Debug)
	execute_process(COMMAND ${CMAKE_COMMAND} -E copy "${FULLPATH_DEBUG}" "${DEST_LIBNAME}Debug/"
		RESULT_VARIABLE resultado
 		ERROR_VARIABLE erro)
	MESSAGE ("resultado: " ${resultado})
	MESSAGE ("erro: " ${erro})
endif()
