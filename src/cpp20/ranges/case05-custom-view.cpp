#include <ranges>

#include <gtest/gtest.h>

#include "utils.h"

/**
 * @brief A custom view for converting std::vector into a range
 *
 * @tparam T the type of the elements
 * @tparam A the allocator type
 */
template<class T, class A>
class vector_view : public std::ranges::view_interface<vector_view<T, A>> {
public:
    vector_view() = default;

    explicit vector_view(const std::vector<T, A> &vec) :
            m_begin(vec.cbegin()), m_end(vec.cend()) {}

    [[nodiscard]] auto begin() const { return m_begin; }

    [[nodiscard]] auto end() const { return m_end; }

private:
    typename std::vector<T, A>::const_iterator m_begin{}, m_end{};
};

TEST(TestRangesCustom, test_custom_view) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto nums = std::vector<int>{1, 2, 3, 4, 5};
    print_range(vector_view<int, std::allocator<int>>(nums));

    // output: 1 2 3 4 5
}
