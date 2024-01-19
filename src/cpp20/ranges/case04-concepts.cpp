#include <ranges>

#include <gtest/gtest.h>

TEST(TestRangesConcepts, test_check_type) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    // ranges::range: any type that provides a 'begin' iterator and an 'end' iterator
    ASSERT_TRUE(std::ranges::range<int[4]>);
    ASSERT_FALSE(std::ranges::range<int[]>);  // error: array of unknown bound is not a range
    ASSERT_TRUE(std::ranges::range<std::vector<int>>);
    ASSERT_TRUE(std::ranges::range<std::set<int>>);
    ASSERT_TRUE(std::ranges::range<decltype(std::views::iota(4))>);

    // ranges::borrowed_range: any range type that is obtained from an expression of it
    // can be safely returned without danger of dangling
    ASSERT_TRUE(std::ranges::borrowed_range<std::vector<int>&>);
    ASSERT_TRUE(std::ranges::borrowed_range<std::vector<int> const&>);
    ASSERT_FALSE(std::ranges::borrowed_range<std::vector<int>&&>);  // error: rvalue reference is not a borrowed range
    ASSERT_FALSE(std::ranges::borrowed_range<std::vector<int>>);  // error: copied value is not a borrowed range

    // ranges::sized_range any range type whose size is known in constant time
    ASSERT_TRUE(std::ranges::sized_range<int[4]>);
    ASSERT_FALSE(std::ranges::sized_range<int[]>);  // error: array of unknown bound is not a sized range
    ASSERT_TRUE(std::ranges::sized_range<std::vector<int>>); // ?? strange
    ASSERT_FALSE(std::ranges::sized_range<decltype(std::views::iota(4))>);

    // other range types:
    // ranges::view                  :specifies that a range is a view, that is, it has constant time copy/move/assignment
    // ranges::input_range           :specifies a range whose iterator type satisfies input_iterator
    // ranges::output_range          :specifies a range whose iterator type satisfies output_iterator
    // ranges::forward_range         :specifies a range whose iterator type satisfies forward_iterator
    // ranges::bidirectional_range   :specifies a range whose iterator type satisfies bidirectional_iterator
    // ranges::random_access_range   :specifies a range whose iterator type satisfies random_iterator
    // ranges::contiguous_range      :specifies a range whose iterator type satisfies random_iterator
    // ranges::common_range          :specifies that a range has identical iterator and sentinel types
    // ranges::viewable_range        :specifies the requirements for a range to be safely converted to a view

}
