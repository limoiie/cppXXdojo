#ifndef CPP_XX_DOJO_UTILS_H
#define CPP_XX_DOJO_UTILS_H

#include <ranges>
#include <iomanip>
#include <iostream>

void print_str_range(std::ranges::range auto &range) {
    for (std::movable auto const &val: range) {
        std::cout << std::quoted(val, '/') << ' ';
    }
    std::cout << std::endl;
}

void print_range(std::ranges::range auto const &range) {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnconstrainedVariableType"
    for (auto const &val: range) {
#pragma clang diagnostic pop
        std::cout << val << ' ';
    }
    std::cout << std::endl;
}

void print_range(std::ranges::range auto &&range) {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnconstrainedVariableType"
    for (auto const &val: range) {
#pragma clang diagnostic pop
        std::cout << val << ' ';
    }
    std::cout << std::endl;
}

#endif //CPP_XX_DOJO_UTILS_H
