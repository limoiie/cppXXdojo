import module_a;

#include <iostream>

#include <gtest/gtest.h>


TEST(TestModule, test_call_function_of_module) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    // ok: use of visible function hello from module_a
    hello();

    // error: use of invisible function world from module_a
    //world();
}
