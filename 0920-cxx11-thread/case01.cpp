#include <iostream>
#include <thread>

#include <gtest/gtest.h>

#include "../utils.h"

static
void foo() {
    std::cout << "You have called foo!" << std::endl;
    fake_costly_computing();
}

static
void goo(int const val) {
    std::cout << "You have called goo with " << val << "!" << std::endl;
    fake_costly_computing();
}

/**
 * The method join() of thread th will block the current thread which has
 * launched th until thread th exits
 */
TEST(TestThread, test_join_by_function) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;
    auto th = std::thread(foo);
    th.join();  // this will cause the current thread blocked until thread th finished
}

/**
 * The method detach() of thread th will leave itself running on the background
 */
TEST(TestThread, test_detach_by_function) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;
    auto th = std::thread(foo);
    th.detach();  // this will leave thread th running on the background, no one waits for it
}

/**
 * NOTE: A thread must be either joined (by calling join()) or detached (by
 * calling detach()) before the object is destroyed.
 * If neither join() nor detach() is called when the thread is destroyed, the
 * program will terminated without an active exception.
 *
 * Try to uncommented following test case and run it to see the error
 */
/**
TEST(TestThread, fail_by_function) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;
    auto th = std::thread(foo);
    // neither th.join() nor th.detach()
}
 */

TEST(TestThread, test_by_function_with_arguments) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;
    auto th = std::thread(goo, 10);  // just append the arguments after the function object
    th.join();
}

TEST(TestThread, test_by_lambda) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;
    auto th = std::thread([]() {
        std::cout << "You have called a lambda!" << std::endl;
        fake_costly_computing();
    });
    th.join();
}