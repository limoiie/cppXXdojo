#include <future>
#include <string>

#include <gtest/gtest.h>

#include "../utils.h"

/*
 * std::packaged_task encapsulates std::function with std::promise
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
