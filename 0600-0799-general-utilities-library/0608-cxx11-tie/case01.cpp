#include <iostream>
#include <tuple>

#include <gtest/gtest.h>

/*
 * Creates a tuple of lvalue references to its arguments or instances of std::ignore.
 *
 * The difference between std::tie and std::make_tuple is std::tie will forward the
 * references, which means the tuple made by std::tie could be lvalue.
 */

/**
 * std::tie may be used to unpack a std::tuple/std::pair
 */
TEST(TestTie, test_tie_to_upack_tuple) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto id = 0;
    auto gpa = 0.0;
    auto grade = ' ';

    auto student = std::make_tuple(1, "Lisa Barren", 3.8, 'A');

    // you can skip some fields by replacing with std::ignore
    std::tie(id, std::ignore, gpa, grade) = student;

    ASSERT_EQ(id, 1);
    ASSERT_EQ(gpa, 3.8);
    ASSERT_EQ(grade, 'A');

    id = 2;  // assignment to id/gpa/grade does not affect student
    ASSERT_EQ(std::get<0>(student), 1);
}

struct S {
    int n;
    std::string s;
    float d;
};

/**
 * std::tie can be used to introduce lexicographical comparison
 */
TEST(TestTie, test_used_for_lexicographical_comparison) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto compare = [](S const& lhs, S const& rhs) {
        return std::tie(lhs.n, lhs.s, lhs.d) < std::tie(rhs.n, rhs.s, rhs.d); // NOLINT(modernize-use-nullptr)
    };

    ASSERT_TRUE(compare({0, "limo", 1.0}, {1, "mori", 2.0}));
}
