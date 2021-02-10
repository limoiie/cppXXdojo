#include <iostream>
#include <future>

#include <gtest/gtest.h>

#include "../utils.h"

TEST(TestTaskPromise, test_promise) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto promise = std::promise<int>();
    auto future = promise.get_future();
    auto other_thread = std::thread([](std::promise<int> p) {
        fake_costly_computing();
        p.set_value(10);
    }, std::move(promise));

    std::cout << "waiting ..." << std::endl << future.get() << std::endl;

    other_thread.join();
}
