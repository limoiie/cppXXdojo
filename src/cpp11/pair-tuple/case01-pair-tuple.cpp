#include <iostream>
#include <tuple>

#include <gtest/gtest.h>

/**
 * reference from https://en.cppreference.com/w/cpp/utility/tuple
 */

TEST(TestPairTuple, test_pair__make_and_get) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto const first = 10;
    auto const second = "string";

    auto pair = std::make_pair(first, second);

    ASSERT_EQ(pair.first, first);
    ASSERT_EQ(std::get<0>(pair), first);

    ASSERT_EQ(pair.second, second);
    ASSERT_EQ(std::get<1>(pair), second);

    pair.first = 11;
    ASSERT_EQ(pair.first, 11);
}

TEST(TestPairTuple, test_tuple__make_and_get) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto const student0 = std::make_tuple(0, 3.8, 'A', "Lisa Simpson");
    std::cout << "ID:"     << std::get<0>(student0) << std::endl
              << "GPA:"    << std::get<1>(student0) << std::endl
              << "grade: " << std::get<2>(student0) << std::endl
              << "name: "  << std::get<3>(student0) << std::endl;
}

/**
 * Require C++17
 */
TEST(TestPairTuple, test_tuple__structure_binding) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    // c++17 structured binding
    auto const student0 = std::make_tuple(0, 3.8, 'A', "Lisa Simpson");
    auto [id, gpa, grade, name] = student0;
    std::cout << "ID:"     << id   << std::endl
              << "GPA:"    << gpa   << std::endl
              << "grade: " << grade << std::endl
              << "name: "  << name  << std::endl;
}

TEST(TestTuple, test_concat_tuple) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto part1 = std::make_tuple("Hello", ',');
    auto part2 = std::make_tuple("World", '!');

    auto const cat = std::tuple_cat(part1, part2);
    std::cout << std::get<0>(cat) << std::get<1>(cat) << ' '
              << std::get<2>(cat) << std::get<3>(cat) << std::endl;
}