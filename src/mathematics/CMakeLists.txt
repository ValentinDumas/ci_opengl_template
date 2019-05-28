# ------------------------------------------------------------------------------
# File: CMakeLists.txt
# Created by Spark on 28/04/2019.
# ------------------------------------------------------------------------------

project(mathematics)

# ------------------------------------------------------------------------------
# Target details
# ------------------------------------------------------------------------------
#TODO: Check if we can handle multiple source files while building with CI Tools (online)
set(${PROJECT_NAME}_SOURCE_FILES complex.cpp)
set(${PROJECT_NAME}_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(${PROJECT_NAME}_LIBRARIES "")
set(${PROJECT_NAME}_COVERAGE ON)
set(${PROJECT_NAME}_WARNINGS ON)

# ------------------------------------------------------------------------------
# Target library
# ------------------------------------------------------------------------------
add_custom_library(STATIC ${PROJECT_NAME} "${${PROJECT_NAME}_SOURCE_FILES}" PUBLIC "${${PROJECT_NAME}_INCLUDE_DIRS}" "${${PROJECT_NAME}_LIBRARIES}" ${PROJECT_NAME}_COVERAGE ${PROJECT_NAME}_WARNINGS)