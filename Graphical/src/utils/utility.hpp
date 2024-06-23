/*
** EPITECH PROJECT, 2024
** Utils
** File description:
** utils namespace utilities
*/

#ifndef UTILS_UTILITY_HPP_
    #define UTILS_UTILITY_HPP_

    #include <type_traits>

namespace utils {
    template<typename T>
    constexpr typename std::add_lvalue_reference<T>::type declvar() noexcept
    {
        static_assert(false, "declvar not allowed in an evaluated context");
    }
}

#endif /* !UTILS_UTILITY_HPP_ */
