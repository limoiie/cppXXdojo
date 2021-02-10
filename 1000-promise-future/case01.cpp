#include <iostream>
#include <future>

#include <gtest/gtest.h>

#include "../utils.h"

/**
 * Set a value for the promise in the other working thread
 */
TEST(TestPromiseFuture, test_promise) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto promise = std::promise<int>();
    auto future = promise.get_future();
    auto worker_thread = std::thread([](std::promise<int> p) {
        fake_costly_computing();
        p.set_value(10);
    }, std::move(promise));

    std::cout << "waiting ..." << std::endl << future.get() << std::endl;

    worker_thread.join();
}

/**
 * Set a value for the promise in the other working thread at thread exit
 *
 * todo: what's the difference between std::promise::set_value_at_thread_exit
 *   and std::promise::set_value? or, what's the use case for the former?
 */
TEST(TestPromiseFuture, test_promise_set_at_thread_exit) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto promise = std::promise<int>();
    auto future = promise.get_future();
    auto worker_thread = std::thread([](std::promise<int> p) {
        fake_costly_computing();
        p.set_value_at_thread_exit(10);
    }, std::move(promise));

    std::cout << "waiting ..." << std::endl << future.get() << std::endl;

    worker_thread.join();
}