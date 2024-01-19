#include <iostream>
#include <any>

#include <gtest/gtest.h>

/**
 * The class any describes a type-safe container for single values of any type.
 *
 * reference from https://en.cppreference.com/w/cpp/utility/any
 */

TEST(TestAny, test_any_cast) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    // make boolean print as true/false instead of 1/0
    std::cout << std::boolalpha;

    // create an any container which can hold any value of any type
    std::any a;
    std::cout << "create any without init" << std::endl;

    // uninitialized any has no value
    ASSERT_FALSE(a.has_value());
    std::cout << "has value? " << a.has_value() << std::endl << std::endl;

    // change the contained value to an int
    std::cout << "assign int to any" << std::endl;
    a = 1;

    std::cout << "has value? " << a.has_value() << std::endl;
    std::cout << "value is " << a.type().name() << ": " << std::any_cast<int>(a) << std::endl << std::endl;
    ASSERT_EQ(a.type(), typeid(int));
    ASSERT_EQ(std::any_cast<int>(a), 1);

    // change the contained value to a double
    std::cout << "assign double to any" << std::endl;
    a = 3.14;

    std::cout << "has value? " << a.has_value() << std::endl;
    std::cout << "value is " << a.type().name() << ": " << std::any_cast<double>(a) << std::endl << std::endl;
    ASSERT_EQ(a.type(), typeid(double));
    ASSERT_EQ(std::any_cast<double>(a), 3.14);

    // change the contained value to a boolean
    std::cout << "assign bool to any" << std::endl;
    a = true;

    std::cout << "has value? " << a.has_value() << std::endl;
    std::cout << "value is " << a.type().name() << ": " << std::any_cast<bool>(a) << std::endl << std::endl;
    ASSERT_EQ(a.type(), typeid(bool));
    ASSERT_EQ(std::any_cast<bool>(a), true);

    // reset any to empty
    std::cout << "reset any" << std::endl;
    a.reset();

    std::cout << "has value? " << a.has_value() << std::endl;
    ASSERT_FALSE(a.has_value());

}

TEST(TestAny, test_bad_cast) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    std::any a = 1;

    // throw a bad_any_cast exception if casting any to the wrong type
    EXPECT_THROW(
            { std::any_cast<float>(a); },
            std::bad_any_cast
    );

    a.reset();

    // throw a bad_any_cast exception if casting an empty any
    EXPECT_THROW(
            { std::any_cast<int>(a); },
            std::bad_any_cast
    );

}

TEST(TestAny, test_pointer_to_contained_data) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    std::any a = 1;

    // initialize any with int value 1
    std::cout << "init any as " << a.type().name() << ": " << std::any_cast<int>(a) << '\n';
    ASSERT_EQ(a.type(), typeid(int));
    ASSERT_EQ(std::any_cast<int>(a), 1);

    // get pointer to contained data
    std::cout << "get address of contained value: p_a = std::any_cast<int>(&a)" << std::endl;
    int *p_a = std::any_cast<int>(&a);
    ASSERT_EQ(*p_a, 1);

    // modify contained value through the pointer
    std::cout << "put new value 2 at address p_a: *p_a = 2" << std::endl;
    *p_a = 2;

    // any value is changed
    std::cout << "any changed as " << a.type().name() << ": " << std::any_cast<int>(a) << '\n';
    ASSERT_EQ(a.type(), typeid(int));
    ASSERT_EQ(std::any_cast<int>(a), 2);

}
