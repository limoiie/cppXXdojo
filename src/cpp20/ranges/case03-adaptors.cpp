#include <iomanip>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string_view>

#include <gtest/gtest.h>

#include "utils.h"

/**
 * For most views::xxx, there is a corresponding ranges::xxx_view,
 * e.g. views::filter and ranges::filter_view, views::take and ranges::take_view.
 * These two kinds of views are almost the same,
 * except that the former one wraps the latter one for the sake of convenience of usage.
 * In most cases, the former one is preferred to use.
 *
 * Maybe the only reasonable use case for the latter one is when you want to implement a custom view.
 *
 * > Always prefer views::meow over ranges::meow_view,
 * > unless you have a very explicit reason that you specifically need to use the latter -
 * > which almost certainly means that you’re in the context of implementing a view,
 * > rather than using one.
 *
 * See https://brevzin.github.io/c++/2023/03/14/prefer-views-meow/
 * See https://www.cppstories.com/2022/ranges-composition/
 */
TEST(TestRangesAdaptors, test_ranges_xx_view_vs_view_xx) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    using namespace std;

    auto nums = views::iota(0, 6);

    print_range(views::filter(nums, [](int i) { return 0 == i % 2; }));
    print_range(ranges::filter_view(nums, [](int i) { return 0 == i % 2; }));

    // output: 0 2 4

    print_range(views::take(nums, 3));
    print_range(ranges::take_view(nums, 3));

    // output: 0 1 2

}


TEST(TestRangesAdaptors, test_filtering) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    using namespace std;

    auto nums = views::iota(0, 6);

    print_range(views::all(nums));

    // output: 0 1 2 3 4 5

    print_range(views::filter(nums, [](int i) { return 0 == i % 2; }));

    // output: 0 2 4

    print_range(views::take(nums, 3));

    // output: 0 1 2

    print_range(views::drop(nums, 3));

    // output: 3 4 5

    print_range(views::take_while(nums, [](int i) { return i < 3; }));

    // output: 0 1 2

    print_range(views::drop_while(nums, [](int i) { return i < 3; }));

    // output: 3 4 5

    print_range(views::counted(nums.begin() + 2, 3));

    // output: 2 3 4

    using std::operator ""sv;

    constexpr auto words{"hello^-^world^-^2024"sv};
    constexpr auto delimiter{"^-^"sv};

    for (auto const word: views::split(words, delimiter)) {
        std::cout << std::quoted(std::string(ranges::begin(word), ranges::end(word)), '/') << ' ';
    }
    std::cout << std::endl;

    // output: /hello/ /world/ /2024/

}

TEST(TestRangesAdaptors, test_transforming) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    using namespace std;

    auto nums = views::iota(0, 6);

    print_range(views::transform(nums, [](int i) { return i * i; }));

    // output: 0 1 4 9 16 25

    print_range(views::reverse(nums));

    // output: 5 4 3 2 1 0

    auto pairs = std::vector<std::pair<int, char>>{
            {1, 'a'},
            {2, 'b'},
            {3, 'c'}
    };

    print_range(views::keys(pairs));

    // output: 1 2 3

    print_range(views::values(pairs));

    // output: a b c

    print_range(views::elements<0>(pairs));

    // output: 1 2 3

    print_range(views::elements<1>(pairs));

    // output: a b c

}

/**
 * Most combination adaptors are introduced in C++23.
 *
 * In C++20, there are only one combination adaptor: join,
 * which is used to concatenate multiple ranges into one range.
 */
TEST(TestRangesAdaptors, test_combining) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    using namespace std;

    print_range(views::join(std::vector<std::vector<int>>{
            {0},
            {1, 2, 3},
            {4, 5}}
    ));

    // output: 0 1 2 3 4 5

}

/**
 * The common_view can be useful for working with
 * legacy algorithms that expect the iterator and sentinel are of the same type.
 */
TEST(TestRangesAdaptors, test_common) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    using namespace std;

    auto nums = {0, 1, 2, 3, 4, 5};

    auto iterator = std::counted_iterator{nums.begin(), std::ssize(nums)};
    auto range = ranges::subrange{iterator, std::default_sentinel};

    // error: "common range" required
    //auto const e1 = std::accumulate(range.begin(), range.end(), 0);

    auto common_range = ranges::common_view{range};
    auto const e2 = std::accumulate(common_range.begin(), common_range.end(), 0);
    ASSERT_TRUE(e2 == 15);

}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-move-const-arg"
TEST(TestRangesAdaptors, test_ref_owning) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    using namespace std;

    auto nums = {0, 1, 2, 3, 4, 5};

    ranges::ref_view ref_view{nums};
    print_range(ref_view);

    // output: 0 1 2 3 4 5

    // error: no matching constructor, requires the 1st argument to be a rvalue
    //ranges::owning_view owning_view(ref_view);

    ranges::owning_view owning_view(std::move(ref_view));
    print_range(owning_view);

    // output: 0 1 2 3 4 5

}
#pragma clang diagnostic pop
