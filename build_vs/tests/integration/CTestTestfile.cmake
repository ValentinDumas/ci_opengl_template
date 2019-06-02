# CMake generated Testfile for 
# Source directory: C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/tests/integration
# Build directory: C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/tests/integration
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(integration_test_robot "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/tests/integration/Debug/integration_test_robot.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(integration_test_robot "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/tests/integration/Release/integration_test_robot.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(integration_test_robot "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/tests/integration/MinSizeRel/integration_test_robot.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(integration_test_robot "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/tests/integration/RelWithDebInfo/integration_test_robot.exe")
else()
  add_test(integration_test_robot NOT_AVAILABLE)
endif()
