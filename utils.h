//
// Created on 2021/2/9.
//

#ifndef CPP20DOJO__UTILS_H_
#define CPP20DOJO__UTILS_H_

#include <iostream>
#include <thread>

inline
void fake_costly_computing() {
    for (auto const i : {1, 2, 3}) {
        std::cout << "computing " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

#endif //CPP20DOJO__UTILS_H_
