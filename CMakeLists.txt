cmake_minimum_required(VERSION 3.1)

project(simple_test)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX") # CMake already contains W3 in its flags
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra-semi -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer")
endif()


find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(
    just_simple_test_ok
    examples/just_simple_test_ok.cpp
    simple_test.h
)

add_executable(
    just_simple_test_failures
    examples/just_simple_test_failures.cpp
    simple_test.h
)

add_executable(
    test_using_simple_test_ok
    examples/test_using_simple_test_ok.cpp
    examples/gtest_compatible_test_ok.h
    simple_test.h
)

add_executable(
    test_using_simple_test_failures
    examples/test_using_simple_test_failures.cpp
    examples/gtest_compatible_test_failures.h
    simple_test.h
)

add_executable(
    test_using_gtest_ok
    examples/test_using_gtest_ok.cpp
    examples/gtest_compatible_test_ok.h
)
target_link_libraries(test_using_gtest_ok GTest::gtest GTest::gtest_main)

add_executable(
    test_using_gtest_failures
    examples/test_using_gtest_failures.cpp
    examples/gtest_compatible_test_failures.h
)
target_link_libraries(test_using_gtest_failures GTest::gtest GTest::gtest_main)
