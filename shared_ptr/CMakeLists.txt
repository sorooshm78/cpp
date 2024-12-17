cmake_minimum_required(VERSION 3.10)

project(shared_ptr)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)

add_executable(test_shared_ptr test.cpp)

target_link_libraries(test_shared_ptr GTest::GTest GTest::Main)

include_directories(${GTEST_INCLUDE_DIRS})
