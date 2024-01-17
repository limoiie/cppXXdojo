#include <iostream>
#include <thread>
#include <mutex>

#include <gtest/gtest.h>

#include "../utils.h"

/**
 * The class jthread represents a single thread of execution. It has the same
 * general behavior as std::thread, except that jthread automatically rejoins
 * on destruction, and can be cancelled/stopped in certain situations.
 */

using namespace std::chrono_literals;

static
void foo() {
    std::cout << "You called foo!" << std::endl;
    fake_costly_computing();
}

TEST(TestJthread, test_jthread) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto _ = std::jthread (foo);
    // It's totally fine without calling join() or detach(). In fact, this
    // thread will automatically rejoin on destruction
}

/**
 * jthread can be cancelled/stopped by calling request_stop
 */
TEST(TestJthread, test_stop_jthread) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;
    auto const time_working = 5;
    auto const time_to_stop = 2s;

    // if the first argument of wrapped function is std::stop_token, then this
    // thread can be cancelled/stopped by calling request_stop().
    // NOTE: no need to pass a value for the first argument since it will be
    // created and passed automatically
    auto th = std::jthread([&](std::stop_token const& token) {
        for (auto i = 1; i <= time_working; ++i) {
            std::cout << "computing step " << i << "/" << time_working << std::endl;
            std::this_thread::sleep_for(1s);
            if (token.stop_requested()) {
                break;
            }
        }
    });

    std::this_thread::sleep_for(time_to_stop);
    std::cout << "Request for stop: " << th.request_stop() << std::endl;
    th.join();  // this line can be commented since it will rejoin automatically
}

/**
 * jthread can be cancelled/stopped on destruction
 */
TEST(TestJthread, test_stop_on_destruction_automatically) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;
    auto const time_working = 5;
    auto const time_to_stop = 2s;

    // if the first argument of wrapped function is std::stop_token, then this
    // thread can be cancelled/stopped by destruction.
    // NOTE: no need to pass a value for the first argument since it will be
    // created and passed automatically
    auto th = std::jthread([&](std::stop_token const& token) {
        std::mutex mutex;
        std::unique_lock lock(mutex);
        for (auto i = 1; i <= time_working; ++i) {
            std::cout << "computing step " << i << "/" << time_working << std::endl;
            std::this_thread::sleep_for(1s);
            if (token.stop_requested()) {
                break;
            }
        }
    });

    std::this_thread::sleep_for(time_to_stop);
    std::cout << "The thread will be stopped automatically due to the destruction" << std::endl;
    // Or automatically using RAII:
    // th's destructor will call request_stop() and join the thread automatically.
}