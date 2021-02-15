#include <iostream>
#include <ranges>
#include <vector>
#include <bits/iterator_concepts.h>

#include <gtest/gtest.h>

TEST(TestRanges, test_ranges) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto v = std::vector<int>();
    auto x = std::__detail::__ranges_begin(v);

    auto z = std::ranges::iota_view<int, int>();

    auto nums = std::views::iota(0, 6);
    auto even = [](int i) { return 0 == i % 2; };
    auto square = [](int i) { return i * i; };

    for (auto const num : nums | std::views::filter(even) |
                          std::views::transform(square)) {
        std::cout << num << ' ';
    }

}
