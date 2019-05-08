if( Boost_FOUND 
	AND Qt5Widgets_FOUND 
	AND OpenGL_FOUND 
)

	message(STATUS "\n ############ SETTING UP MAIN MODULE ############ ")
	message(STATUS "DEPENDENCIES : ${DEPENDENCIES}") 
	message(STATUS "boost-include-dirs : ${Boost_INCLUDE_DIRS}")
	message(STATUS "Boost_LIBRARIES : ${Boost_LIBRARIES}")
	
	# String describing the version of the module.
	message(STATUS "Qt5Widgets_VERSION : ${Qt5Widgets_VERSION}")
	# List of libraries for use with the target_link_libraries command.
	message(STATUS "Qt5Widgets_LIBRARIES : ${Qt5Widgets_LIBRARIES}")
	# List of definitions for use with add_definitions.
	message(STATUS "Qt5Widgets_DEFINITIONS : ${Qt5Widgets_DEFINITIONS}")
	# List of definitions for use with the COMPILE_DEFINITIONS target property.
	message(STATUS "Qt5Widgets_COMPILE_DEFINITIONS : ${Qt5Widgets_COMPILE_DEFINITIONS}")
	# String of flags to be used when building executables.
	message(STATUS "Qt5Widgets_EXECUTABLE_COMPILE_FLAGS : ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
	
    #set(DEPENDENCIES
    #  .
	#  ..
    #  ../source/*.cpp
    #  ../source/*.h
	#)
	add_executable( 
		${EXECUTABLE_NAME} 
		${DEPENDENCIES} 
        ${QT_DEPS}
	)
	target_compile_features(
		${EXECUTABLE_NAME} 
		PRIVATE cxx_std_14
	)
	
	message(STATUS "OPENGL_INCLUDE_DIRS : ${OPENGL_INCLUDE_DIRS}")
	target_include_directories(
		${EXECUTABLE_NAME}
		PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
		PRIVATE ${Boost_INCLUDE_DIRS}
		PRIVATE ${Qt5Widgets_INCLUDE_DIRS}
		PRIVATE ${OPENGL_INCLUDE_DIRS}
	)
	
	message(STATUS "OPENGL_LIBRARIES : ${OPENGL_LIBRARIES}")
	target_link_libraries(
		${EXECUTABLE_NAME} 
		PRIVATE ${Boost_LIBRARIES} 
		PRIVATE ${Qt5Widgets_LIBRARIES}
		PRIVATE ${OPENGL_LIBRARIES}
	)
	
elseif( NOT Boost_FOUND)
	message(STATUS "cannot find Boost!!!!!!!!!!!")
elseif( NOT Qt5Widgets_FOUND)
	message(STATUS "cannot find Qt5Widgets!!!!!!!!!!!")
elseif( NOT OpenGL_FOUND)
	message(STATUS "cannot find OpenGL!!!!!!!!!!!")
endif()
