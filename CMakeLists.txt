cmake_minimum_required(VERSION 3.17)
project(cpp20dojo)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest CONFIG REQUIRED)

add_executable(cpp20dojo
    main.cpp
    promise-future/case01.cpp)
target_link_libraries(cpp20dojo
    GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

enable_testing()