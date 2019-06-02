# CMake generated Testfile for 
# Source directory: C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/tests/unit
# Build directory: C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/tests/unit
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(unit_test_robot "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/tests/unit/Debug/unit_test_robot.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(unit_test_robot "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/tests/unit/Release/unit_test_robot.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(unit_test_robot "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/tests/unit/MinSizeRel/unit_test_robot.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(unit_test_robot "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/tests/unit/RelWithDebInfo/unit_test_robot.exe")
else()
  add_test(unit_test_robot NOT_AVAILABLE)
endif()
subdirs("mathematics")
