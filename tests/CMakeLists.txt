if( Boost_FOUND )

	message(STATUS "\n ############ SETTING UP TEST MODULE ############ ")
	message(STATUS "boost-include-dirs : ${Boost_INCLUDE_DIRS}")
	message(STATUS "Boost_LIBRARIES : ${Boost_LIBRARIES}")
		
	#set(DEPENDENCIES
	#  .
	#  ..
	#  ../source/*.cpp
	#  ../source/*.h
	#)
	add_executable( 
		${TEST_NAME} 
		${DEPENDENCIES}
	)
	target_compile_features(
		${TEST_NAME} 
		PRIVATE cxx_std_14
	)
	target_include_directories(
		${TEST_NAME}
		PRIVATE ${Boost_INCLUDE_DIRS}
		PRIVATE ${DEPENDENCIES}
	)
	target_link_libraries( 
		${TEST_NAME}
		PRIVATE ${Boost_LIBRARIES} 
	)

elseif( NOT Boost_FOUND)
	message(STATUS "cannot find Boost!!!!!!!!!!!")
endif()