import A;

#include <iostream>

#include <gtest/gtest.h>


TEST(TestModule, test_call_function_of_module_with_partitions) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    // ok: use of visible function from module A:B
    std::cout << hello_from_A_B() << std::endl;

    // error: use of invisible function from module A:C
    //hello_from_A_C();
}
