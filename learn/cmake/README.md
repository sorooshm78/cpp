# Cmake

## Linke
* [How to Learn CMake in Just 20 Minutes](https://medium.com/swlh/how-to-learn-cmake-in-just-20-minutes-b8eb4767f2c)

## How to Learn CMake in Just 20 Minutes
If you have ever worked or written a C or C++ project, you have probably heard of the build system called CMake. For programmers that are new to C or C++, the concept of a separate build system usage a separate language may seem odd. However, knowledge of how to properly to properly compile, build and package a project is absolutely essential knowledge for a C++ programmer. In this guide, the roles CMake plays as a build system will be explained, and the most essential aspects and features of CMake will be discussed. You will learn how to use CMake to build libraries and executables, in hopefully under 20 minutes.

### Why is CMake even used?
Unlike many other programming languages, there is no centralized distribution of one, singular C++ compiler. The C++ language is modeled after an ISO standard specification, which several vendors of compilers like Microsoft or Clang, then implement. Each of those compilers, has different settings and options, and runs on a different operating system. Most C++ programs are intended be written to run cross platforms and on any modern compiler, doing that with a custom build script would prove difficult. It would require detailed knowledge of each compiler and operating system, and a ton of boilerplate code.

CMake generates build systems for C++ projects from an abstract script written in the CMake language. CMake provides an interface to specify build options and processes, without being concerned with compiler or operating system specific details. Do note, it only covers cross platform functionality for building the project, you are still responsible for the actual source code running on different platforms.

### Project structure and the CMakeLists.txt file
There are multiple ways to layout a C++ project. Some projects split their header and source files, by having one include directory and a src directory, while some put both in the same directories. For this purpose, we will use combined header and source directories, so the project structure is a little more straightforward.

At the beginning of each project must be a CMakeLists.txt file. This is the file name CMake recognizes as a build script file. A project can have multiple CMakeLists.txt, but only one in each directory. For the one in the top level directory of the project, the following must be present at the top of the file

```
cmake_minimum_required(VERSION 3.6) 
project(foo)
```

These two lines denote the minimum version of cmake required to build the project, and the name of the project. The minimum version is not that important for this case, as long as it is at least 3.0. Let’s take a look at a sample project layout below:

```
- CMakeLists.txt
- some.h
- some.cpp
- main.cpp
```

Here, there is a CMake file, CMakeLists.txt, a header file, some.h , and a source file, some.cpp . There’s also another source file, main.cpp . In most C++ projects, there is a library that contains the project’s code to be consumed by other projects and programs, as well as an executable that allows some of the code in the project to be run as a CLI program. For this example, some.cpp will represent the core library code, and main.cpp will represent the executable that’s also built.

### Building the library
In order to have CMake build a library, the source files that compose that library need to be specified in the CMakeLists.txt file. To do that, we have to construct a list of the files and call the add_library function.

In CMake, it’s important to understand variables and data types work very differently than perhaps any other language. All variables in CMake are strings. Lists in CMake are strings which contain the separator ; . Variables are created and destroyed using the set() and unset() functions. Below is an example of creating a list and printing it.

```
set(some_var "a" "b" "c")
message("${some_var}")
```

This will print
```
a;b;c
```

Above is another important feature of CMake, variable access. After a variable is created via the set() function, it’s value can only be accessed via the syntax ${var} . This is because, in CMake, everything is a string. Even unquoted values are strings. The statement message(hello) , treats hello as a five character string.

Now, to build our library, we must add the following to the build file, CMakeLists.txt:
```
set(FOO_SOURCES some.cpp)
add_library(foos STATIC "${FOO_SOURCES}")
```

In the call to add_library() , the source variable is accessed via the ${} syntax. However, we also pass in another argument, SHARED . This tells CMake whether we want a static library or shared library.

### Adding the executable
Now that we have added a library to the build file, we can expand the file to include instructions on building an executable and linking our library to that executable. Let’s make up a simple C++ file, main.cpp , that calls a function from our library:
```
#include "some.h"
int main(int argc, char const* argv[]) {
    someFunc(); // defined in some.cpp
    return 0;
}
```
Then, we can add to the build file the following:
```
add_executable(foot main.cpp)
target_link_libraries(foot foos)
```

The add_executable function works very similarly to add_library it takes in a name variable and a list representing the source files. In this case, since we know our executable only has one additional source file, we don’t need a separate variable to represent the sources as a list, we can just pass it in directly. The target_link_libraries function takes a target as the first argument, and then a list of other targets that must be libraries, to like to the first argument.

In CMake, a “target” is an object that is built by the resulting build system that CMake produces. In this example, both the library and the executable are build targets. In more complicated projects, custom targets are sometimes used to represent the creation of files needed by the built project. But for now, lets just stick to the basic build targets.

Putting it all together
Now that the process of writing a CMakeLists.txt file has been discussed, we can jump into running CMake and then using the build system generated by CMake to compile our code. If you don’t have CMake currently installed on your system, you can typically install it by running brew install cmake if you have home brew. Otherwise, try this link.

CMake is typically run in an empty directory, that references the path the CMakeLists.txt root file is in. For example, if one is currently in the directory of the project, these commands are often used:

mkdir build
cd build
cmake ..
This will run CMake, and get it to produce build files in the current directory. It will print out a lot of information, pertaining to the compiler it detected and is using to generate these files for.

Next, you will actually run the files CMake generated and compile the project. If you are on MacOS or Linux, you will run make . If you are on windows, you will typically run msbuild ALL_BUILD.vcxproj . This will cause the compiler to run and try to compile your code. Note: this might fail if your code has syntax errors or otherwise is incorrectly written. CMake does not detect or check language syntax, it is only concerned with the build process.

That’s all! Hopefully by now, you feel comfortable in CMake to the point you can write your own build files, and create simple projects in C++ using it. CMake, overall, is a vast framework with many specialized components that can help build almost any C++ project. As you advance and get more familiar with it, you will likely need more advanced and sophisticated CMake, like having multiple subdirectories, or adding in 3rd party libraries as dependencies to your project.