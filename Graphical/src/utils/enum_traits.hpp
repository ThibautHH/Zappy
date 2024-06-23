/*
** EPITECH PROJECT, 2024
** Utils
** File description:
** utils::enum_traits
*/

#ifndef UTILS_ENUM_TRAITS_HPP_
    #define UTILS_ENUM_TRAITS_HPP_

    #include <algorithm>
    #include <iostream>
    #include <span>
    #include <sstream>
    #include <string_view>
    #include <type_traits>
    #include <unordered_map>

    #include "extract.hpp"

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

    template<has_output_enum_traits T>
    inline std::ostream& operator<<(std::ostream& os, T value)
    {
        return os.iword(utils::enum_traits<T>::xalloc_index)
            ? (os << utils::enum_traits<T>::to_string.at(value))
            : (os << static_cast<std::underlying_type_t<T>>(value));
    }

    template<has_input_enum_traits T>
    inline std::istream& operator>>(std::istream& is, T& value)
    {
        std::string word;
        is >> word;
        if (is.iword(utils::enum_traits<T>::xalloc_index))
            try {
                value = utils::enum_traits<T>::from_string.at(word);
            } catch (const std::out_of_range &) {
                is.setstate(std::ios_base::failbit);
            }
        else {
            auto v = utils::extract<std::underlying_type_t<T>>(std::istringstream(word), is);
            if (!v.has_value())
                return is;
            const auto end = utils::enum_traits<T>::valid_values.end();
            if (std::find(utils::enum_traits<T>::valid_values.begin(), end, static_cast<T>(v.value())) == end)
                is.setstate(std::ios_base::failbit);
            else
                value = static_cast<T>(v.value());
        }
        return is;
    }
}

#endif /* !UTILS_ENUM_TRAITS_HPP_ */
