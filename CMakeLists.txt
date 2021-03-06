cmake_minimum_required(VERSION 3.17)
project(cpp20dojo)

set(CMAKE_CXX_STANDARD 20)

# -fcoroutines is required by header <coroutine>
set(CMAKE_CXX_FLAGS "-pthread -fcoroutines")

find_package(GTest CONFIG REQUIRED)

add_executable(cpp20dojo
    main.cpp
    0600-0799-general-utilities-library/0602-cxx11-pair-tuple/case01-pair-tuple.cpp
    0600-0799-general-utilities-library/0608-cxx11-tie/case01.cpp
    0600-0799-general-utilities-library/0620-cxx17-optional-any-variant/case01-optional.cpp
    0600-0799-general-utilities-library/0620-cxx17-optional-any-variant/case02-any.cpp
    0600-0799-general-utilities-library/0620-cxx17-optional-any-variant/case03-variant.cpp
    0800-cxx17-declaration-structured-binding/case01.cpp
    0920-cxx11-thread/case01.cpp
    0921-cxx20-jthread/case01.cpp
    0950-cxx11-bind/case01.cpp
    1000-cxx11-promise-future/case01.cpp
    1001-cxx11-packaged-tasks/case01.cpp
    1050-cxx11-async-launch/case01.cpp
    2000-cxx20-concepts/case01-basics.cpp
    2020-cxx20-ranges/case01-basics.cpp
    )

target_link_libraries(cpp20dojo
    GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

enable_testing()