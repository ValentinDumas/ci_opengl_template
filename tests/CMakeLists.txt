set(EXTERNAL_MODULES glfw ${GLFW_LIBRARIES} glad ${GLAD_LIBRARIES} glm stb assimp::assimp Box2D project_src_lib gtest gtest_main gmock gmock_main)
set(PROJECT_SOURCE_MODULES project_src_lib)

# Default testing mode as STANDALONE (offline)
set(STANDALONE_TESTING ON)
if(STANDALONE_TESTING)
    message("Tests are configured in STANDALONE mode")
else()
    message("Tests are configured in ONLINE mode")
endif()

function(CreateTest TYPE NAME)
	set(SAMPLE_NAME ${TYPE}_${NAME})
	add_executable(${SAMPLE_NAME} ${NAME}.cpp)
	target_link_libraries(${SAMPLE_NAME} PRIVATE ${EXTERNAL_MODULES} ${PROJECT_SOURCE_MODULES}) #Note: see if glfw has to be included...

	add_test(
		NAME ${SAMPLE_NAME}
		COMMAND $<TARGET_FILE:${SAMPLE_NAME}> )
endfunction()

add_subdirectory(integration)
add_subdirectory(unit)
