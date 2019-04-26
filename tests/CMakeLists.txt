# TODO (note): keep an eye on PROJECT_SOURCE_MODULES: as the tests automatically link against all project modules, it may trigger a "Coverage report error" on CodeCov if a module is linked to glfw or glad.

# ------------------------------------------------------------------------------
# Dependency Libraries: from "deps" and / or "externals"
# ------------------------------------------------------------------------------
set(TESTS_LIBRARIES gtest gtest_main gmock gmock_main)

# ------------------------------------------------------------------------------
# Project Modules (all modules in a list)
# ------------------------------------------------------------------------------
get_property_by_name(PROJECT_SOURCE_MODULES P_PROJECT_SOURCE_MODULES)

# ------------------------------------------------------------------------------
# Create CTest tests one by one --> detailed test execution (usefull for bot VS and Online testing)
# ------------------------------------------------------------------------------
macro(CreateTest TYPE NAME PATH_TO_TEST ADDITIONAL_TESTING_DEPENDENCIES)
	set(TEST_NAME ${TYPE}_${NAME})
	add_executable(${TEST_NAME} ${PATH_TO_TEST}/${NAME}.cpp)
	target_link_libraries(${TEST_NAME} PRIVATE ${TESTING_DEPENDENCIES} ${ADDITIONAL_TESTING_DEPENDENCIES} ${PROJECT_SOURCE_MODULES} coverage_config) #Note: no detailed warnings (from gtest macro)
    add_test(NAME ${TEST_NAME} COMMAND $<TARGET_FILE:${TEST_NAME}>)
endmacro()

function(GetRecursiveItemsFromPath items_returned root_path pattern)
	# Look for items matching a given pattern
	file(GLOB_RECURSE items_found ${pattern})

	# Extract relative paths from root (absolute) paths
	foreach (item_path ${items_found})
		string(REPLACE "${root_path}/" "" item_relative_path ${item_path})
		list(APPEND items ${item_relative_path})
	endforeach ()

	# Return variable, containing all items found
	set(${items_returned} ${items} PARENT_SCOPE)
endfunction()

# ------------------------------------------------------------------------------
# Main Tests
# ------------------------------------------------------------------------------
add_subdirectory(integration)
add_subdirectory(unit)