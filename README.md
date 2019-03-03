# CI C++/OpenGL Template

Continuous Integration template project in C++ with CMake.
This project includes the most needed OpenGL libraries to start a project.

[![GitHub version](https://badge.fury.io/gh/valentindumas%2Fci_opengl_template.svg)](https://badge.fury.io/gh/valentindumas%2Fci_opengl_template)
[![Build Status](https://travis-ci.org/ValentinDumas/ci_opengl_template.svg?branch=master)](https://travis-ci.org/ValentinDumas/ci_opengl_template)
[![Build status](https://ci.appveyor.com/api/projects/status/g4vc2xg31g7vqu81?svg=true)](https://ci.appveyor.com/project/ValentinDumas/ci-opengl-template)
[![Coverage Status](https://coveralls.io/repos/github/ValentinDumas/ci_opengl_template/badge.svg)](https://coveralls.io/github/ValentinDumas/ci_opengl_template)
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
This template is configured to work with the following tools for continuous integration.
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
      - "deps/externals/"

#### Codacy
Codacy automates code review and analysis.
This project uses Codacy to detect potential writing issues and regressions in the source code.
It can detect different kind of potential issues:
-   Security
-   Error Prone
-   Code Style
-   Compatibility
-   Unused Code (= Dead Code)
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

## 4. Installation
... coming soon ...
talk about packages to install for each platform
IDEs ?

## 5. Project configuration
... coming soon ...
show & talk about in-project configurations to setup Doxygen, GitCheck, etc correctly
