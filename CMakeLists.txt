cmake_minimum_required(VERSION 3.17)
project(cppXXdojo)

find_package(GTest CONFIG REQUIRED)


#=============================================================================
# All features together
#=============================================================================

add_executable(cppXXdojo
        main.cpp
        src/cpp11/pair-tuple/case01-pair-tuple.cpp
        src/cpp11/tie/case01.cpp
        src/cpp17/optional-any-variant/case01-optional.cpp
        src/cpp17/optional-any-variant/case02-any.cpp
        src/cpp17/optional-any-variant/case03-variant.cpp
        src/cpp17/declaration-structured-binding/case01.cpp
        src/cpp11/thread/case01.cpp
        src/cpp20/jthread/case01.cpp
        src/cpp11/bind/case01.cpp
        src/cpp11/promise-future/case01.cpp
        src/cpp11/packaged-tasks/case01.cpp
        src/cpp11/async-launch/case01.cpp
        src/cpp20/concepts/case01-basics.cpp
        src/cpp20/ranges/case01-basics.cpp
        src/cpp20/ranges/case02-creation.cpp
        src/cpp20/ranges/case03-adaptors.cpp
        src/cpp20/ranges/case04-concepts.cpp
        src/cpp20/ranges/case05-custom-view.cpp
#        src/cpp20/modules/basic/case01-basics.cpp
#        src/cpp20/modules/nested/case01-basics.cpp
#        src/cpp20/modules/partitions/case01-basics.cpp
)

target_link_libraries(cppXXdojo
        GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
# currently disabled because of an error saying unexpected syntax included by gtest
#        cpp20dojo_modules
)

set_target_properties(cppXXdojo PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_compile_options(cppXXdojo PRIVATE
        # These flags are required by gcc:
        #   -pthread is required by header <thread>
        #   -fmodules-ts is required by header <module>
        #   -fcoroutines is required by header <coroutine>
        $<$<CXX_COMPILER_ID:GNU>:-pthread -fmodules-ts -fcoroutines>
)


#=============================================================================
# C++11 features
#=============================================================================

add_executable(cpp11dojo
        main.cpp
        src/cpp11/pair-tuple/case01-pair-tuple.cpp
        src/cpp11/tie/case01.cpp
        src/cpp11/thread/case01.cpp
        src/cpp11/bind/case01.cpp
        src/cpp11/promise-future/case01.cpp
        src/cpp11/packaged-tasks/case01.cpp
        src/cpp11/async-launch/case01.cpp
)

set_target_properties(cpp11dojo PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_compile_options(cpp11dojo PRIVATE
        # These flags are required by gcc:
        #   -pthread is required by header <thread>
        $<$<CXX_COMPILER_ID:GNU>:-pthread>
)

target_link_libraries(cpp11dojo
        GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
)


#=============================================================================
# C++17 features
#=============================================================================

add_executable(cpp17dojo
        main.cpp
        src/cpp17/optional-any-variant/case01-optional.cpp
        src/cpp17/optional-any-variant/case02-any.cpp
        src/cpp17/optional-any-variant/case03-variant.cpp
        src/cpp17/declaration-structured-binding/case01.cpp
)

set_target_properties(cpp17dojo PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_compile_options(cpp17dojo PRIVATE
        # empty for now
)

target_link_libraries(cpp17dojo
        GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
)


#=============================================================================
# C++20 features
#=============================================================================

add_library(cpp20dojo_modules MODULE
        src/cpp20/modules/basic/module_a.cpp
        src/cpp20/modules/nested/module_hidden_inner.cpp
        src/cpp20/modules/nested/module_outer.cpp
        src/cpp20/modules/nested/module_exported_inner.cpp
        src/cpp20/modules/global_and_private_fragment/module_with_global_fragment.cpp
        src/cpp20/modules/global_and_private_fragment/module_with_private_fragment.cpp
        src/cpp20/modules/partitions/module-A-B.cpp
        src/cpp20/modules/partitions/module-A-C.cpp
        src/cpp20/modules/partitions/module-A.cpp
)

set_target_properties(cpp20dojo_modules PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_compile_options(cpp20dojo_modules PRIVATE
        # These flags are required by gcc:
        #   -fmodules-ts is required by header <module>
        $<$<CXX_COMPILER_ID:GNU>:-fmodules-ts>
)

add_executable(cpp20dojo
        main.cpp
        src/cpp20/jthread/case01.cpp
        src/cpp20/concepts/case01-basics.cpp
        src/cpp20/ranges/case01-basics.cpp
        src/cpp20/ranges/case02-creation.cpp
        src/cpp20/ranges/case03-adaptors.cpp
        src/cpp20/ranges/case04-concepts.cpp
        src/cpp20/ranges/case05-custom-view.cpp
#        src/cpp20/modules/basic/case01-basics.cpp
#        src/cpp20/modules/nested/case01-basics.cpp
#        src/cpp20/modules/partitions/case01-basics.cpp
)

set_target_properties(cpp20dojo PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_compile_options(cpp20dojo PRIVATE
        # These flags are required by gcc:
        #   -pthread is required by header <thread>
        #   -fmodules-ts is required by header <module>
        #   -fcoroutines is required by header <coroutine>
        $<$<CXX_COMPILER_ID:GNU>:-pthread -fmodules-ts -fcoroutines>
)

target_link_libraries(cpp20dojo
        GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
# currently disabled because of an error saying unexpected syntax included by gtest
#        cpp20dojo_modules
)

enable_testing()
