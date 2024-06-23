/*
** EPITECH PROJECT, 2024
** Utils
** File description:
** utils::enum_traits
*/

#ifndef UTILS_ENUM_TRAITS_HPP_
    #define UTILS_ENUM_TRAITS_HPP_

    #include <iostream>
    #include <span>
    #include <string_view>
    #include <unordered_map>

    #include "concepts.hpp"

namespace utils {
    template<enum_type T>
    struct enum_traits {
        static const int xalloc_index;
        typedef T value_type;
        typedef const std::unordered_map<T, std::string_view> to_string_type;
        typedef const std::unordered_map<std::string_view, T> from_string_type;
        typedef const std::span<const value_type> valid_values_type;

        static to_string_type to_string;
        static from_string_type from_string;
        static valid_values_type valid_values;

        static std::ios_base &alpha(std::ios_base &s)
        {
            s.iword(xalloc_index) = 1;
            return s;
        }

        static std::ios_base &noalpha(std::ios_base &s)
        {
            s.iword(xalloc_index) = 0;
            return s;
        }

        template<std::convertible_to<std::ios_base> U>
        static decltype(auto) copy_alpha(U &&s, std::ios_base &other)
        {
            s.iword(xalloc_index) = other.iword(xalloc_index);
            return std::forward<U>(s);
        }
    };

    template<enum_type T>
    const int enum_traits<T>::xalloc_index = std::ios_base::xalloc();

    template<typename T>
    concept has_enum_traits =
        enum_type<T>
        && requires {
            { utils::enum_traits<T>::xalloc_index } -> std::convertible_to<int>;
        };

    template<typename T>
    concept has_output_enum_traits =
        has_enum_traits<T>
        && requires(T t) {
            { utils::enum_traits<T>::to_string.at(t) } -> std::convertible_to<std::string_view>;
        };

    template<typename T>
    concept has_input_enum_traits =
        has_enum_traits<T>
        && requires(std::string_view s) {
            { utils::enum_traits<T>::from_string.at(s) } -> std::convertible_to<T>;
        } && requires(T t) {
            { utils::enum_traits<T>::valid_values.begin() } -> std::same_as<typename utils::enum_traits<T>::valid_values_type::iterator>;
            { utils::enum_traits<T>::valid_values.end() } -> std::same_as<typename utils::enum_traits<T>::valid_values_type::iterator>;
        };
}

#endif /* !UTILS_ENUM_TRAITS_HPP_ */
