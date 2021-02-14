#include <iostream>
#include <thread>

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
    // thread will automatically rejoins on destruction
}

/**
 * jthread can be cancelled/stopped
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
        for (auto i = 0; i < time_working; ++i) {
            std::cout << "computing step " << i << std::endl;
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