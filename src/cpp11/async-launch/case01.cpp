#include <iostream>
#include <future>

#include <gtest/gtest.h>

#include "../../../utils.h"

/**
 * The function template async runs the function f asynchronously (potentially in
 * a separate thread which might be a part of a thread pool) and returns a
 * std::future that will eventually hold the result of that function call.
 *
 * reference from https://en.cppreference.com/w/cpp/thread/async
 */

/**
 * Run the given task asynchronously
 */
TEST(TestAsyncLaunch, test_async) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto result = std::async(std::launch::async, []() {
        fake_costly_computing(3);
        return 10;
    });

    std::cout << "Do other things..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << "Got the result: " << result.get() << std::endl;
}

/**
 * Run the given task synchronously
 */
TEST(TestAsyncLaunch, test_defered) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;

    // the lambda below would run only after the `get()` or `wait*()` are called
    auto result = std::async(std::launch::deferred, []() {
        fake_costly_computing(3);
        return 10;
    });

    std::cout << "Do other things..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << "Got the result: " << result.get() << std::endl;
}