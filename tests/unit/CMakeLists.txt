# ------------------------------------------------------------------------------
# File: CMakeLists.txt
# Created by Spark on 28/04/2019.
# ------------------------------------------------------------------------------

project(unit_tests)

# ------------------------------------------------------------------------------
# Target details
# ------------------------------------------------------------------------------
GetRecursiveItemsFromPath(${PROJECT_NAME}_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")
set(${PROJECT_NAME}_INCLUDE_DIRS "")
set(${PROJECT_NAME}_LIBRARIES ${TESTS_LIBRARIES} glm ${PROJECT_SOURCE_MODULES})
set(${PROJECT_NAME}_COVERAGE ON)
set(${PROJECT_NAME}_WARNINGS OFF)

# ------------------------------------------------------------------------------
# Target executable
# ------------------------------------------------------------------------------
add_custom_executable(${PROJECT_NAME} "${${PROJECT_NAME}_SOURCE_FILES}" PUBLIC "${${PROJECT_NAME}_INCLUDE_DIRS}" "${${PROJECT_NAME}_LIBRARIES}" ${PROJECT_NAME}_COVERAGE ${PROJECT_NAME}_WARNINGS)

# ------------------------------------------------------------------------------
# Create unit tests
# ------------------------------------------------------------------------------
macro(CreateUnitTest test_name relative_test_dir)
    CreateTest(unit ${test_name} "${relative_test_dir}" "${${PROJECT_NAME}_LIBRARIES}")
endmacro()

# Note: Write the name and the relative directory for a test you want to create.
CreateUnitTest(test_robot ${CMAKE_CURRENT_SOURCE_DIR})

# ------------------------------------------------------------------------------
# Unit tests subdirectories
# ------------------------------------------------------------------------------
# Note: All subdirectories containing can be written there.
add_subdirectory(mathematics)