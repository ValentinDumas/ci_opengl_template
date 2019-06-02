# CMake generated Testfile for 
# Source directory: C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/tests/unit/mathematics
# Build directory: C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/tests/unit/mathematics
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(unit_test_complex "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/tests/unit/mathematics/Debug/unit_test_complex.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(unit_test_complex "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/tests/unit/mathematics/Release/unit_test_complex.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(unit_test_complex "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/tests/unit/mathematics/MinSizeRel/unit_test_complex.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(unit_test_complex "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/tests/unit/mathematics/RelWithDebInfo/unit_test_complex.exe")
else()
  add_test(unit_test_complex NOT_AVAILABLE)
endif()
