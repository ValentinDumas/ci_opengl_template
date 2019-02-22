include_directories(deps/externals/googletest/googletest/include)
include_directories(deps/externals/googletest/googlemock/include)

set(EXTERNAL_MODULES gtest gtest_main gmock gmock_main)
set(PROJECT_SOURCE_MODULES project_src_lib)

add_subdirectory(integration)
#add_subdirectory(unit)

