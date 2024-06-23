/*
** EPITECH PROJECT, 2024
** Utils
** File description:
** utils namespace concepts
*/

#ifndef UTILS_CONCEPTS_HPP_
    #define UTILS_CONCEPTS_HPP_

    #include <concepts>
    #include <type_traits>

    #define fwd(a) std::forward<decltype(a)>(a)

namespace utils {
    template<typename T>
    concept enum_type = std::is_enum_v<T>;

    template<typename T, typename U>
    concept same_ref_as =
        std::same_as<std::remove_reference_t<T>, std::remove_reference_t<U>>;

    template<typename T, typename U>
    concept same_type_as =
        std::same_as<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;

    template<typename T, typename U>
    concept ref_convertible_to =
        std::convertible_to<
            std::add_lvalue_reference_t<std::remove_reference_t<T>>,
            std::add_lvalue_reference_t<std::remove_reference_t<U>>
        >;
}

#endif /* !UTILS_CONCEPTS_HPP_ */
