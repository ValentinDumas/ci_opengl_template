# ------------------------------------------------------------------------------
# Dependency Libraries: from "deps" and / or "externals"
# ------------------------------------------------------------------------------
#stb
set(EXTERNAL_MODULES glm gtest gtest_main gmock gmock_main)

# ------------------------------------------------------------------------------
# Project Libraries: from "src" (sources)
# ------------------------------------------------------------------------------
set(PROJECT_SOURCE_MODULES project_src_lib)

# ------------------------------------------------------------------------------
# Visual Studio / CTest coverage one by one
# ------------------------------------------------------------------------------
#function(CreateTest TYPE NAME)
#	set(SAMPLE_NAME ${TYPE}_${NAME})
#	add_executable(${SAMPLE_NAME} ${NAME}.cpp)
#	target_link_libraries(${SAMPLE_NAME} PRIVATE ${EXTERNAL_MODULES} ${PROJECT_SOURCE_MODULES}) #Note: see if glfw has to be included...
#
#	add_test(
#		NAME ${SAMPLE_NAME}
#		COMMAND $<TARGET_FILE:${SAMPLE_NAME}> )
#endfunction()

# ------------------------------------------------------------------------------
# Main Tests
# ------------------------------------------------------------------------------
add_subdirectory(integration)
add_subdirectory(unit)
