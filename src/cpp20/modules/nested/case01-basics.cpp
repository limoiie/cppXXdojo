import module_outer;

import <iostream>;

#include <gtest/gtest.h>


TEST(TestModule, test_call_function_of_nest_imported_module) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    // ok: use of visible functions from module_outer
    hello_nested();

    // ok: module_exported_inner was export-imported, all its exported functions are visible
    hello_from_exported_inner();

    // error: use of invisible function world from module_a
    //hello_from_hidden_inner();
}
