//
// Created on 2021/2/9.
//

#ifndef CPP20DOJO__UTILS_H_
#define CPP20DOJO__UTILS_H_

#include <iostream>
#include <thread>

inline
void fake_costly_computing(int const seconds = 3) {
    for (auto i = 0; [[maybe_unused]] auto const _ : std::vector<int>(seconds, 1)) {
        std::cout << "computing " << i++ << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

#endif //CPP20DOJO__UTILS_H_
