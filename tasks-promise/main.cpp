#include <iostream>
#include <future>

#include <gtest/gtest.h>

TEST(TestTaskPromise, test_task) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __FUNCTION__ << " ..." << std::endl;
    auto promise = std::promise<int>();
    auto future = promise.get_future();
    auto other_thread = std::thread([](std::promise<int> p) {
        for (auto const i : {1, 2, 3}) {
            std::cout << "computing " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        p.set_value(10);
    }, std::move(promise));

    std::cout << "waiting ..." << std::endl << future.get() << std::endl;
    other_thread.join();
}
