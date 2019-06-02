# CI C++/OpenGL Template

Continuous Integration template project in C++ with CMake.
This project includes the most needed OpenGL libraries to start a project.

[![GitHub version](https://badge.fury.io/gh/valentindumas%2Fci_opengl_template.svg)](https://badge.fury.io/gh/valentindumas%2Fci_opengl_template)
[![Build Status](https://travis-ci.org/ValentinDumas/ci_opengl_template.svg?branch=master)](https://travis-ci.org/ValentinDumas/ci_opengl_template)
[![Build status](https://ci.appveyor.com/api/projects/status/g4vc2xg31g7vqu81?svg=true)](https://ci.appveyor.com/project/ValentinDumas/ci-opengl-template)
[![Codecov](https://codecov.io/gh/ValentinDumas/ci_opengl_template/branch/master/graph/badge.svg)](https://codecov.io/gh/ValentinDumas/ci_opengl_template)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/78ab13069ab94f8e82d6096a5db2d59f)](https://www.codacy.com/app/ValentinDumas/ci_opengl_template?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=ValentinDumas/ci_opengl_template&amp;utm_campaign=Badge_Grade)
[![Documentation](https://codedocs.xyz/ValentinDumas/ci_opengl_template.svg)](https://codedocs.xyz/ValentinDumas/ci_opengl_template/)

## 1. Description

This repository provides a continuous integration sample project.
This project was made with cmake and is cross-platform.
It is a good template for starting a cross-platform C++ OpenGL project.

## 2. Continuous Integration
Continuous integration is a process where a source code is checked each time a modification is made.
This process ensures that the result of the modifications does not produce a regression in a developed application.

### Continuous Integration Tools
This template provides testing support for Windows, Linux and macOS.
It is configured to work with the following tools for continuous integration:

#### Travis CI
Travis CI is a continuous integration tool for online compilation, testing and deployment.
It synchronizes with Github repositories in order to perform the following checks:
-   **Doxygen**, checks if some documentation is lacking in the source code.
-   **GitCheck**, checks if their is some wrong syntax among the modifications.
-   **Codecov**, generates a complete test coverage report.
-   **Google Sanitizers**, detects undefined behavior and other code anomalies.
-   **Valgrind**, detects possible memory leaks.
-   **GCC Compiler Tests**, checks if the source code compiles on GCC compilers.
-   **Clang Compiler Tests**, checks if the source code compiles on Clang compilers.
-   **XCode Compiler Tests**, checks if the source code compiles on XCode compilers.

The Travis CI configuration file is located in the root directory.

    .travis.yml

#### Appveyor
Appveyor is an online continuous integration tool which performs some checks for the source code on Windows platform.
-   **Visual Studio Compiler Tests**, checks if the source code compiles on Visual C++ compiler AND performes tests.

The Appveyor configuration file is located in the root directory.

    .appveyor.yml

#### Codecov
Codecov has highly integrated tools to group, merge, archive, and compare coverage reports.
It improves the source code review workflow and quality.

A configuration file is provided for Codecov.

    .codecov.yml

This file excludes the external dependencies from the project as they are not directly part of it.
Here is the configuration to ignore external dependencies:

    ignore:
      - "externals/"

#### Codacy
Codacy automates code review and analysis.
This project uses Codacy to detect potential writing issues and regressions in the source code.
It can detect different kind of potential issues:
-   Security
-   Error Prone
-   Code Style
-   Compatibility
-   Unused Code (<=> Dead Code)
-   Performance

### Documentation

#### Doxygen
Doxygen is an open source documentation generator capable of producing software documentation from the source code of a program.
To do this, it takes into account the syntax of the language in which the source code is written, as well as comments if they are written in a particular format.

This project uses Doxygen and it includes a Doxyfile. It is a configuration file used by Doxygen to generate a code documentation.

Here are the main customizable options from the Doxyfile to quickly generate a Doxygen documentation:
-   The name of the project

        PROJECT_NAME           = "CI OpenGL Template"

-   A quick description of the project

        PROJECT_BRIEF          = "An example of how to setup a complete CI environment for C, C++, OpenGL with CMake"

-   The parent folders (including their children) to take into account when generating the documentation.

        INPUT                  = src

-   The different folders to ignore while generating the documentation.

        EXCLUDE_PATTERNS       = */externals/*
        EXCLUDE_PATTERNS       += */docs/*
        EXCLUDE_PATTERNS       += */doc/*
        EXCLUDE_PATTERNS       += */.git/*
        EXCLUDE_PATTERNS       += */.idea/*
        EXCLUDE_PATTERNS       += */.vs/*
        EXCLUDE_PATTERNS       += */build/*

#### Codedocs
A documentation is automatically generated by Codedocs after each push request to Github.
It is available at: [https://codedocs.xyz/ValentinDumas/ci_opengl_template](https://codedocs.xyz/ValentinDumas/ci_opengl_template/)

A configuration file is setup to catch a Doxygen configuration located in the project.

    .codedocs

This file prevents generating the documentation for external dependencies.
As the Doxyfile (Doxygen configuration file) is already configured in the project, it is only needed to catch the configuration in the .codecov file with this line:

    DOXYFILE = NameOfTheDoxyfile.Extension

For this project, the name chosen for the Doxyfile is

    DOXYFILE = .doxygen.txt

The Doxyfile has a .txt extension to make it easier to edit.

## 3. Install the Dependencies
Although this repository can be made to run on most systems, it is still needed to install some basic dependencies:

**Linux distributions (e.g. Ubuntu 16.10 or higher)**

    sudo apt-get install git build-essential cmake

    sudo apt-get install xorg-dev libglu1-mesa-dev libbsd-dev libzzip-dev

And if you need a specific compiler for Linux, I suggest installing a GCC or Clang compiler:

    sudo apt-get install gcc-6 g++-6

    AND / OR

    sudo apt-get install clang-3.8 

**Windows (Visual Studio)**
Install the following packages:
-   Visual Studio SDK 10
-   Visual Studio 2017
-   Check "Desktop development with C++"
-   Check "C++ CLI / Support"
-   Check "Standard Library Modules"
-   CMake v3.6+
-   Git for Windows

**macOS**
-   XCode 7.3+
-   CMake v3.6+

## 4. Configure the analysis tools
The following provides a description of all of the analysis tools that have been integrated into the CI services used by this project including an explanation of how it works.

### Doxygen documentation tool
The CI is setup to check for missing documentation using doxygen.
Unlike most of the analysis tools used in this project, there is no make target for doxygen, and instead it is run using doxygen manually with the following script:

    - doxygen .doxygen.txt
    - |
      if [[ -s doxygen_warnings.txt ]]; then
        echo "You must fix doxygen before submitting a pull request"
        echo ""
        cat doxygen_warnings.txt
        exit -1
      fi

This script runs doxygen against the source code and any warnings are placed into a file called doxygen_warnings.txt.
If this file is empty, it means that the doxygen analysis passed, and all of the code is documented based on the settings in the .doxygen.txt configuration file.
If this files is not empty, the test fails, and prints the warnings generated by doxygen.

### Git Check
git diff --check provides a simple way to detect when whitespace errors has been checked into the repo, as well as checking when end-of-file newlines are either missing, or contain too many. More information about this check can be found here. This check is extremely useful for developers when PRs contain modifications unrelated to their specific changes.

    - |
      if [[ -n $(git diff --check HEAD^) ]]; then
        echo "You must remove whitespace before submitting a pull request"
        echo ""
        git diff --check HEAD^
        exit -1
      fi
      
This check simply runs git diff --check, which returns with an error if the check fails. If this occurs, the diff is displayed for the user to see.

### Codecov test coverage
Codecov is a powerful, yet simple to setup coverage tool.

    # ------------------------------------------------------------------------------
    # Coverage
    # ------------------------------------------------------------------------------
    add_library(coverage_config INTERFACE)
    option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
    if(ENABLE_COVERAGE)
        # Add required flags (GCC & LLVM/Clang)
        target_compile_options(coverage_config INTERFACE
                -O0        # no optimization
                -g         # generate debug info
                --coverage # sets all required flags
                )
        if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
            target_link_options(coverage_config INTERFACE --coverage)
        else()
            target_link_libraries(coverage_config INTERFACE --coverage)
        endif()
    endif(ENABLE_COVERAGE)

**The built library can be linked to a target executable to enable coverage on it**, like this:

    target_link_libraries(target_name PUBLIC coverage_config) # Include code-coverage for this target only

To setup coverage, we must enable GCOV support in our compiler (assumes GCC or Clang). Once this support is enabled, running make test will generate coverage stats that Codecov can analyze to give you a report of what code has or has not been unit tested.

    - cmake -DENABLE_COVERAGE=ON -DONLINE_TESTING=1 -DCMAKE_CXX_COMPILER="g++-6" ..
    - make -j4 # run project build
    - make test # run all tests
    - cd ..
    - bash <(curl -s https://codecov.io/bash)

The Travis CI test is as simple as compiling and running the unit tests, and then running Codecov's bash script. Once this is done, the results can be see on Codecov's website.

### Google Sanitizers
The Google Sanitizers are a dynamic analysis tool that is included in GCC and Clang/LLVM.

    if(ENABLE_ASAN)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
    endif()

    if(ENABLE_USAN)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
    endif()

    if(ENABLE_TSAN)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
    endif()

Each sanitizer has to be run in isolation, and thus we have one test per sanitizer group.
The flags for each set can be found on Google's GitHub page as well as Clang's usage documentation.

    - cmake -DENABLE_ASAN=ON -DCMAKE_CXX_COMPILER="g++-6" ..
    - make
    - make test

For each test, we turn on the specific check, and the unit tests, and if a check fails, the unit test will exit with a non-0 exit code, causing Travis CI to fail the test.
It should be noted that each new version of GCC and Clang comes with better support, and thus, like some of the other tools, you should stick to a specific version.

### Valgrind
Valgrind is another dynamic analysis tool that provides leak detection.

    set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --leak-check=full")
    set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --track-fds=yes")
    set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --trace-children=yes")
    set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --error-exitcode=1")

The easiest way to execute Valgrind is to use CMake's built-in support as it will handle error logic for you.
For this reason, we need to tell CMake what flags to give Valgrind.
In this case we enable all of its checks and tell Valgrind to exit with a non-0 exit code so that if a check fails, Travis CI will fail the test.

    - cmake -DCMAKE_CXX_COMPILER="g++-6" ..
    - make
    - ctest -T memcheck

To run the test, all we need to do is compile the code, and run the unit tests using ctest, enabling the memcheck mode.

## 5. Compile and Test locally
To compile and install this project template, use the following instructions:

**GCC / Clang**

    git clone https://github.com/ainfosec/ci_helloworld.git

    mkdir ci_helloworld/build
    cd ci_helloworld/build

    cmake ..

    make
    make test

**Visual Studio 2017 (NMake)**

    git clone https://github.com/ainfosec/ci_helloworld.git

    mkdir ci_helloworld/build
    cd ci_helloworld/build

    cmake -G "NMake Makefiles" ..

    nmake
    nmake test

**Visual Studio 2017 (MSBuild)**

    git clone https://github.com/ainfosec/ci_helloworld.git

    mkdir ci_helloworld/build
    cd ci_helloworld/build

    cmake -G "Visual Studio 15 2017 Win64" ..

    msbuild ci_helloworld.sln
    ctest

**XCode 7.3+**

    git clone https://github.com/ainfosec/ci_helloworld.git

    mkdir ci_helloworld/build
    cd ci_helloworld/build

    cmake ..

    make
    make test

## 6. External Dependencies
This project includes some useful libraries:
-   **GLFW**, provides a context to render the OpenGL stuff on screen.
-   **glad compatibility 3.3**, OpenGL + extensions loader.
-   **glm**, performs matrix and vectors calculations. It is GLSL compatible.
-   **SFML**, Simple and Fast Multimedia Library, complete library for 2D/3D game development
-   **googletest**, test / mock library.
-   **Box2D**, 2D physics library.
-   **assimp**, 3D model loading library.
-   **bullet**, coming soon...

## 7. How to adapt this project to your needs
You only need to:
-   Clone or fork this project

-   Choose an IDE for opening the project

-   Inside the IDE, search for "ci_opengl_template" and replace all occurences by the project name of your choice.

-   Setup your accounts on the following websites (you can login with github account):
    -   [Travis CI](https://travis-ci.org)
    -   [AppVeyor](https://ci.appveyor.com)
    -   [Codecov](https://codecov.io)
    -   [Codacy](https://app.codacy.com/)
    -   [Codedocs](https://codedocs.xyz)

-   Update all the badges from the repository by replacing the markdown code with your badge markdown in the README file.
    The different badges' codes can be found on their respective websites.
