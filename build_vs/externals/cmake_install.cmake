# Install script for directory: C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/externals

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/googletest/cmake_install.cmake")
  include("C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/cppfs/cmake_install.cmake")
  include("C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/luajit_2.0.3/cmake_install.cmake")
  include("C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/sfml_2.5.1/cmake_install.cmake")
  include("C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/glad/cmake_install.cmake")
  include("C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/glfw_3.2.1/cmake_install.cmake")
  include("C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/glm_0.9.9.3/cmake_install.cmake")
  include("C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/Box2D/cmake_install.cmake")
  include("C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/imgui_1.68/cmake_install.cmake")
  include("C:/Users/Spark/Desktop/apps/cppprojects/BOILERPLATES/ci_opengl_template/build_vs/externals/stb/cmake_install.cmake")

endif()

