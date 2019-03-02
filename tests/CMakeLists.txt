set(EXTERNAL_MODULES glm stb gtest gtest_main gmock gmock_main)
set(PROJECT_SOURCE_MODULES project_src_lib)

# Default testing mode as STANDALONE (offline)
set(STANDALONE_TESTING ON)
if(STANDALONE_TESTING)
    message("Tests are configured in STANDALONE mode")
else()
    message("Tests are configured in ONLINE mode")
endif()

function(CreateTest TYPE NAME)
	set(SAMPLE_NAME test_${NAME})
	add_executable(${SAMPLE_NAME} ${NAME}.cpp)
	target_link_libraries(${SAMPLE_NAME} PRIVATE ${EXTERNAL_MODULES} ${PROJECT_SOURCE_MODULES}) #Note: see if glfw has to be included...
	target_compile_definitions(${SAMPLE_NAME} PRIVATE test_${TYPE}_main=main)

	add_test(
		NAME ${SAMPLE_NAME}
		COMMAND $<TARGET_FILE:${SAMPLE_NAME}> )
endfunction()

add_subdirectory(integration)
add_subdirectory(unit)
