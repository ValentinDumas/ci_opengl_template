# Install script for directory: C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/externals/luajit_2.0.3

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/ci_opengl_template")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xRuntimex" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/luajit_2.0.3/Debug/wluajit.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/luajit_2.0.3/Release/wluajit.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/luajit_2.0.3/MinSizeRel/wluajit.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/luajit_2.0.3/RelWithDebInfo/wluajit.exe")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xRuntimex" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/luajit_2.0.3/Debug/luajit.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/luajit_2.0.3/Release/luajit.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/luajit_2.0.3/MinSizeRel/luajit.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/luajit_2.0.3/RelWithDebInfo/luajit.exe")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xLibraryx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/luajit_2.0.3/Debug/lua.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/luajit_2.0.3/Release/lua.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/luajit_2.0.3/MinSizeRel/lua.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/luajit_2.0.3/RelWithDebInfo/lua.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xRuntimex" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/luajit_2.0.3/Debug/lua.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/luajit_2.0.3/Release/lua.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/luajit_2.0.3/MinSizeRel/lua.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/luajit_2.0.3/RelWithDebInfo/lua.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xHeaderx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/externals/luajit_2.0.3/src/lua.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xHeaderx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/externals/luajit_2.0.3/src/luajit.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xHeaderx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/externals/luajit_2.0.3/src/lua.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xHeaderx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/externals/luajit_2.0.3/src/luaconf.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xHeaderx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/externals/luajit_2.0.3/src/lualib.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xHeaderx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/externals/luajit_2.0.3/src/lauxlib.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDocumentationx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/luajit/doc/" TYPE DIRECTORY FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/externals/luajit_2.0.3/doc/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xOtherx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/luajit/etc/" TYPE DIRECTORY FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/externals/luajit_2.0.3/etc/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDatax" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/luajit" TYPE FILE FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/externals/luajit_2.0.3/COPYRIGHT")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDatax" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/luajit" TYPE FILE FILES "C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/externals/luajit_2.0.3/README.md")
endif()

