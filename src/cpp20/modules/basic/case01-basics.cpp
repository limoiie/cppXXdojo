import module_a;

#include <iostream>

#include <gtest/gtest.h>


TEST(TestModule, test_call_function_of_module) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    // ok: use of visible functions from module_a
    std::cout << hello_from_hidden_inner() << std::endl;
    std::cout << add(0, 0) << std::endl;
    std::cout << minus(0, 0) << std::endl;
    std::cout << hi::english() << std::endl;
    std::cout << hi::french() << std::endl;

    // error: use of invisible function world from module_a
    //world();
}
