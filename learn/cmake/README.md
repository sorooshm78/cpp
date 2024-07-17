# Cmake

## Linke
* [How to Learn CMake in Just 20 Minutes](https://medium.com/swlh/how-to-learn-cmake-in-just-20-minutes-b8eb4767f2c)
* [learning cmake a beginner guide](https://tuannguyen68.gitbooks.io/learning-cmake-a-beginner-s-guide/content/chap1/chap1.html)
* [modern cmake](https://cliutils.gitlab.io/modern-cmake/chapters/intro/running.html)


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

### Putting it all together
Now that the process of writing a CMakeLists.txt file has been discussed, we can jump into running CMake and then using the build system generated by CMake to compile our code. If you don’t have CMake currently installed on your system, you can typically install it by running brew install cmake if you have home brew. Otherwise, try this link.

CMake is typically run in an empty directory, that references the path the CMakeLists.txt root file is in. For example, if one is currently in the directory of the project, these commands are often used:
```
mkdir build
cd build
cmake ..
```

This will run CMake, and get it to produce build files in the current directory. It will print out a lot of information, pertaining to the compiler it detected and is using to generate these files for.

Next, you will actually run the files CMake generated and compile the project. If you are on MacOS or Linux, you will run make . If you are on windows, you will typically run msbuild ALL_BUILD.vcxproj . This will cause the compiler to run and try to compile your code. Note: this might fail if your code has syntax errors or otherwise is incorrectly written. CMake does not detect or check language syntax, it is only concerned with the build process.

That’s all! Hopefully by now, you feel comfortable in CMake to the point you can write your own build files, and create simple projects in C++ using it. CMake, overall, is a vast framework with many specialized components that can help build almost any C++ project. As you advance and get more familiar with it, you will likely need more advanced and sophisticated CMake, like having multiple subdirectories, or adding in 3rd party libraries as dependencies to your project.

Sure! Let's dive into CMake step-by-step with clear explanations and plenty of examples. CMake is a cross-platform tool that helps manage the build process of software projects. It generates native build files (like Makefiles on Unix or project files for Visual Studio) from simple configuration files.

### Table of Contents
1. Basic Project Setup
2. Adding Libraries
3. Using External Libraries
4. Advanced Topics
    - Conditional Statements
    - Custom Commands and Targets
    - Packaging
5. Example Projects

### 1. Basic Project Setup

#### Example 1: Simple Hello World

1. **Project Structure:**
```
MyProject/
├── CMakeLists.txt
└── main.cpp
```

2. **main.cpp**
```cpp
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```

3. **CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(MyProject VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(MyProject main.cpp)
```

4. **Building the Project:**
```sh
mkdir build
cd build
cmake ..
cmake --build .
```

This will generate and build the project, resulting in an executable `MyProject`.

### 2. Adding Libraries

#### Example 2: Creating and Linking a Static Library

1. **Project Structure:**
```
MyProject/
├── CMakeLists.txt
├── main.cpp
└── MathFunctions/
    ├── CMakeLists.txt
    ├── MathFunctions.h
    └── MathFunctions.cpp
```

2. **MathFunctions/MathFunctions.h**
```cpp
#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

int add(int a, int b);

#endif // MATHFUNCTIONS_H
```

3. **MathFunctions/MathFunctions.cpp**
```cpp
#include "MathFunctions.h"

int add(int a, int b) {
    return a + b;
}
```

4. **MathFunctions/CMakeLists.txt**
```cmake
add_library(MathFunctions STATIC MathFunctions.cpp)
```

5. **main.cpp**
```cpp
#include <iostream>
#include "MathFunctions.h"

int main() {
    std::cout << "3 + 4 = " << add(3, 4) << std::endl;
    return 0;
}
```

6. **CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 3.10)

project(MyProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(MathFunctions)

add_executable(MyProject main.cpp)
target_link_libraries(MyProject PRIVATE MathFunctions)
```

7. **Building the Project:**
```sh
mkdir build
cd build
cmake ..
cmake --build .
```

### 3. Using External Libraries

#### Example 3: Using the Boost Library

1. **Install Boost:**
   Make sure Boost is installed on your system.

2. **Project Structure:**
```
MyProject/
├── CMakeLists.txt
└── main.cpp
```

3. **main.cpp**
```cpp
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <string>

int main() {
    std::string s = "Boost Libraries";
    std::vector<std::string> words;
    boost::split(words, s, boost::is_any_of(" "));
    
    for(const auto& word : words) {
        std::cout << word << std::endl;
    }
    
    return 0;
}
```

4. **CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 3.10)

project(MyProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost 1.65 REQUIRED COMPONENTS algorithm)

add_executable(MyProject main.cpp)
target_link_libraries(MyProject PRIVATE Boost::algorithm)
```

5. **Building the Project:**
```sh
mkdir build
cd build
cmake ..
cmake --build .
```

### 4. Advanced Topics

#### Conditional Statements

```cmake
if(WIN32)
    message(STATUS "We are on Windows")
elseif(UNIX)
    message(STATUS "We are on Unix")
endif()
```

#### Custom Commands and Targets

```cmake
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/generated_file.cpp
    COMMAND generate_code > ${CMAKE_BINARY_DIR}/generated_file.cpp
    DEPENDS generate_code
)

add_custom_target(run ALL
    COMMAND MyProject
    DEPENDS MyProject
)
```

#### Packaging

Create a `CPackConfig.cmake` file:

```cmake
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "MyProject")
set(CPACK_PACKAGE_VERSION "1.0.0")
include(CPack)
```

Add to `CMakeLists.txt`:

```cmake
install(TARGETS MyProject DESTINATION bin)
include(CPackConfig.cmake)
```

### 5. Example Projects

#### Example 4: A More Complex Project with Multiple Libraries

1. **Project Structure:**
```
MyComplexProject/
├── CMakeLists.txt
├── main.cpp
├── MathFunctions/
│   ├── CMakeLists.txt
│   ├── MathFunctions.h
│   └── MathFunctions.cpp
└── StringFunctions/
    ├── CMakeLists.txt
    ├── StringFunctions.h
    └── StringFunctions.cpp
```

2. **MathFunctions/MathFunctions.h**
```cpp
#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

int add(int a, int b);

#endif // MATHFUNCTIONS_H
```

3. **MathFunctions/MathFunctions.cpp**
```cpp
#include "MathFunctions.h"

int add(int a, int b) {
    return a + b;
}
```

4. **MathFunctions/CMakeLists.txt**
```cmake
add_library(MathFunctions STATIC MathFunctions.cpp)
```

5. **StringFunctions/StringFunctions.h**
```cpp
#ifndef STRINGFUNCTIONS_H
#define STRINGFUNCTIONS_H

#include <string>
#include <vector>

void split(const std::string &s, char delimiter, std::vector<std::string> &tokens);

#endif // STRINGFUNCTIONS_H
```

6. **StringFunctions/StringFunctions.cpp**
```cpp
#include "StringFunctions.h"
#include <sstream>

void split(const std::string &s, char delimiter, std::vector<std::string> &tokens) {
    std::stringstream ss(s);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
}
```

7. **StringFunctions/CMakeLists.txt**
```cmake
add_library(StringFunctions STATIC StringFunctions.cpp)
```

8. **main.cpp**
```cpp
#include <iostream>
#include "MathFunctions.h"
#include "StringFunctions.h"
#include <vector>

int main() {
    std::cout << "3 + 4 = " << add(3, 4) << std::endl;
    
    std::string s = "Hello,World";
    std::vector<std::string> tokens;
    split(s, ',', tokens);
    
    for(const auto& token : tokens) {
        std::cout << token << std::endl;
    }
    
    return 0;
}
```

9. **CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 3.10)

project(MyComplexProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(MathFunctions)
add_subdirectory(StringFunctions)

add_executable(MyComplexProject main.cpp)
target_link_libraries(MyComplexProject PRIVATE MathFunctions StringFunctions)
```

10. **Building the Project:**
```sh
mkdir build
cd build
cmake ..
cmake --build .
```

### Conclusion

This guide has covered the basics of CMake, from setting up a simple project to linking libraries and using external dependencies. By following these examples, you should be able to build and manage more complex projects with ease.

For further reading, the official [CMake documentation](https://cmake.org/documentation/) is an excellent resource.


## More
Understanding the differences between static and shared libraries is crucial for managing and optimizing your software builds. Here's an explanation of both types, along with their advantages and disadvantages:

### Static Libraries

A static library is a collection of object files that are linked directly into the final executable at compile time. This means that the code from the static library is copied into the executable file.

**Characteristics:**
- **File Extension:** Typically `.a` (archive) on Unix-like systems, `.lib` on Windows.
- **Linking Time:** Static libraries are linked at compile time.
- **Execution:** No need for the library file at runtime since the code is already included in the executable.
- **Size:** The executable size is larger because it contains the library code.

**Advantages:**
- **Self-contained Executable:** The resulting executable is self-contained and doesn't depend on external library files at runtime.
- **Version Control:** No issues with library versioning or dependencies at runtime since the library is part of the executable.

**Disadvantages:**
- **Size:** Larger executable size due to the inclusion of the library code.
- **Updates:** If the library code needs to be updated, the executable must be recompiled.

### Shared Libraries

A shared library (also called a dynamic library) is a collection of object files that are linked at runtime. The executable contains references to the shared library but not the library code itself.

**Characteristics:**
- **File Extension:** Typically `.so` (shared object) on Unix-like systems, `.dll` (dynamic link library) on Windows.
- **Linking Time:** Shared libraries are linked at runtime.
- **Execution:** The library file must be available at runtime for the executable to function.
- **Size:** The executable size is smaller since it doesn't contain the library code.

**Advantages:**
- **Size:** Smaller executable size since the library code is not included in the executable.
- **Updates:** Shared libraries can be updated independently of the executable. A new version of the library can be used without recompiling the executable.

**Disadvantages:**
- **Dependencies:** The executable depends on the shared library file being present and compatible at runtime.
- **Version Control:** Potential issues with library versioning (e.g., "DLL Hell" on Windows) where different versions of the shared library might cause conflicts.

### When to Use Each Type

- **Static Libraries:**
  - When you need a self-contained executable that can run without relying on external files.
  - For distributing software where you want to avoid dependency issues.
  - In environments where the deployment of additional files (like shared libraries) is difficult or undesirable.

- **Shared Libraries:**
  - When you want to save disk space and memory, as multiple executables can share the same library.
  - For applications that can benefit from modularity and the ability to update libraries independently.
  - In systems where managing dependencies and versions of libraries is straightforward.

### Example with CMake

Here’s how you can specify whether to build a static or shared library using CMake:

#### Static Library

```cmake
add_library(MyLibrary STATIC src/mylibrary.cpp)
```

#### Shared Library

```cmake
add_library(MyLibrary SHARED src/mylibrary.cpp)
```

### Example Project Structure

```text
MyProject/
├── CMakeLists.txt
├── src/
│   ├── main.cpp
│   └── mylibrary.cpp
└── include/
    └── mylibrary.h
```

#### CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

# Create a static or shared library
add_library(MyLibrary STATIC src/mylibrary.cpp)  # Change STATIC to SHARED for a shared library

# Add the executable
add_executable(MyExecutable src/main.cpp)

# Link the library to the executable
target_link_libraries(MyExecutable PRIVATE MyLibrary)
```

### Conclusion

Both static and shared libraries have their own use cases and trade-offs. Choosing the right type depends on your project's requirements regarding deployment, update flexibility, and resource management. Understanding these differences helps in making informed decisions for efficient software development and deployment.