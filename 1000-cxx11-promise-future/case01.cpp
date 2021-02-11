#include <iostream>
#include <future>

#include <gtest/gtest.h>

#include "../utils.h"

/**
 * The class template std::promise provides a facility to store a value
 * or an exception that is later acquired asynchronously via a std::future
 * object created by the std::promise object. Note that the std::promise
 * object is meant to be used only once.
 *
 * Each promise is associated with a shared state, which contains some
 * state information and a result which may be not yet evaluated, evaluated
 * to a value (possibly void) or evaluated to an exception. A promise may
 * do three things with the shared state:
 *   - make ready: the promise stores the result or the exception in the
 *       shared state. Marks the state ready and unblocks any thread waiting
 *       on a future associated with the shared state.
 *   - release: the promise gives up its reference to the shared state. If
 *       this was the last such reference, the shared state is destroyed.
 *       Unless this was a shared state created by std::async which is not
 *       yet ready, this operation does not block.
 *   - abandon: the promise stores the exception of type std::future_error
 *       with error code std::future_errc::broken_promise, makes the shared
 *       state ready, and then releases it.
 *
 * reference from https://en.cppreference.com/w/cpp/thread/promise
 * reference from https://en.cppreference.com/w/cpp/thread/future
 */

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

TEST(TestPromiseFuture, test_promise_wait) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto promise = std::promise<int>();
    auto future = promise.get_future();
    auto worker_thread = std::thread([](std::promise<int> p) {
        fake_costly_computing(4);
        p.set_value(10);
    }, std::move(promise));

    std::cout << "waiting " << std::endl;
    // wait() will block the current thread until set_value in working thread
    future.wait();
    std::cout << "get the value - " << future.get() << std::endl;

    worker_thread.join();
}

TEST(TestPromiseFuture, test_promise_wait_for) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto promise = std::promise<int>();
    auto future = promise.get_future();
    auto worker_thread = std::thread([](std::promise<int> p) {
        fake_costly_computing(4);
        p.set_value(10);
    }, std::move(promise));

    auto const waiting_duration = std::chrono::seconds(2);
    while (true) {
        std::cout << "waiting " << waiting_duration.count() << "s" << std::endl;
        switch (future.wait_for(waiting_duration)) {
            case std::future_status::ready:
                std::cout << "  ready: get the value - "
                          << future.get() << std::endl;
                break;
            case std::future_status::timeout:
                std::cout << "  timeout: need to wait more time"
                          << std::endl;
                continue;
            case std::future_status::deferred:
                std::cout << "  deferred: compute now and get the value - "
                          << future.get() << std::endl;
                break;
        }
        break;
    }

    worker_thread.join();
}