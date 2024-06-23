/*
** EPITECH PROJECT, 2024
** Utils
** File description:
** utils::extract
*/

#ifndef UTILS_EXTRACT_HPP_
    #define UTILS_EXTRACT_HPP_

    #include <istream>
    #include <optional>
    #include <utility>

    #include "concepts.hpp"

namespace utils {
    template <typename T>
    inline void extract(ref_convertible_to<std::istream> auto &&is, T &value, std::istream &target)
    {
        T v{};
        fwd(is) >> v;
        if (is.fail())
            return target.setstate(std::ios_base::failbit);
        value = v;
    }

    template<typename T>
    constexpr void extract(ref_convertible_to<std::istream> auto &&is, T &value) { return extract(fwd(is), value, fwd(is)); }

    template <typename T>
    inline std::optional<T> extract(ref_convertible_to<std::istream> auto &&is, std::istream &target)
    {
        T value{};
        fwd(is) >> value;
        if (is.fail())
            return target.setstate(std::ios_base::failbit), std::nullopt;
        return value;
    }

    template <typename T>
    constexpr decltype(auto) extract(ref_convertible_to<std::istream> auto &&is) { return extract<T>(fwd(is), fwd(is)); }

    template <typename T>
    inline T extract(ref_convertible_to<std::istream> auto &&is, T &&defaultValue)
    {
        T value{};
        fwd(is) >> value;
        if (is.fail())
            return std::forward<T>(defaultValue);
        return value;
    }
}

#endif /* !UTILS_EXTRACT_HPP_ */
