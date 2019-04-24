include_directories(${gtest_SOURCE_DIR}/include)
include_directories(${gmock_SOURCE_DIR}/include)

# ------------------------------------------------------------------------------
# Dependency Libraries: from "deps" and / or "externals"
# ------------------------------------------------------------------------------
#stb
message(${DYNAMIC_LIBRARIES})

set(TESTING_DEPENDENCIES gtest gtest_main gmock gmock_main)

# ------------------------------------------------------------------------------
# Project Libraries: from "src" (sources)
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# CTest coverage one by one --> Detailed test execution, usefull for VS or online testing
# ------------------------------------------------------------------------------
function(CreateTest TYPE NAME ADDITIONAL_TESTING_DEPENDENCIES)
	set(TEST_NAME ${TYPE}_${NAME})
	add_executable(${TEST_NAME} ${NAME}.cpp)
        message("Additional DEPS -----------> ${ADDITIONAL_TESTING_DEPENDENCIES}")
	target_link_libraries(${TEST_NAME} PRIVATE ${TESTING_DEPENDENCIES} ${ADDITIONAL_TESTING_DEPENDENCIES} "${PROJECT_SOURCE_MODULES}" coverage_config) #Note: see if glfw has to be included...

    add_test(
		NAME ${TEST_NAME}
		COMMAND $<TARGET_FILE:${TEST_NAME}> )
endfunction()

# ------------------------------------------------------------------------------
# Main Tests
# ------------------------------------------------------------------------------
add_subdirectory(integration)
add_subdirectory(unit)
