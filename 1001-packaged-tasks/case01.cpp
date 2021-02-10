#include <future>
#include <string>

#include <gtest/gtest.h>

#include "../utils.h"

/**
 * The class template std::packaged_task wraps any Callable target
 * (function, lambda expression, bind expression, or another function
 * object) so that it can be invoked asynchronously. Its return value
 * or exception thrown is stored in a shared state which can be
 * accessed through std::future objects.
 *
 * reference from https://en.cppreference.com/w/cpp/thread/packaged_task
 */

static int computing(int const age, std::string const& times) {
    fake_costly_computing();
    return age * atoi(times.c_str());
}

/**
 * Create a packaged_task with a function
 */
TEST(TestPackagedTask, test_func_task) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;

    std::packaged_task<int(int, std::string)> task(computing);
    auto fut = task.get_future();

    std::thread td(std::move(task), 10, "20");

    std::cout << "waiting ... " << std::endl << fut.get() << std::endl;

    td.join();
}

/**
 * Create a packaged_task with a bound function
 */
TEST(TestPackagedTask, test_bind_func_task) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;

    std::packaged_task<int()> task(std::bind(computing, 10, "20")); // NOLINT(modernize-avoid-bind)
    auto fut = task.get_future();

    std::thread td(std::move(task));

    std::cout << "waiting ... " << std::endl << fut.get() << std::endl;

    td.join();
}

/*
 * Create a packaged_task with a lambda
 */
TEST(TestPackagedTask, test_lambda_task) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;

    std::packaged_task<int(int, std::string)> task(
            [](int const age, std::string const& delta) {
                fake_costly_computing();
                return age + atoi(delta.c_str());
            });
    auto fut = task.get_future();

    std::thread td(std::move(task), 10, "20");

    std::cout << "waiting ... " << std::endl << fut.get() << std::endl;

    td.join();
}
