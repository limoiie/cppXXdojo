#ifndef CPP_XX_DOJO_UTILS_H_
#define CPP_XX_DOJO_UTILS_H_

#include <iostream>
#include <thread>

inline
void fake_costly_computing(int const seconds = 3) {
    for (auto i = 0; i < seconds; ++i) {
        std::cout << "computing " << i << " seconds" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

#endif //CPP_XX_DOJO_UTILS_H_
