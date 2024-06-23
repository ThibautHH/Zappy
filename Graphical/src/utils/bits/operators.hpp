/*
** EPITECH PROJECT, 2024
** Utils
** File description:
** utils namespace operators raw definition
*/

template<utils::has_output_enum_traits T>
inline std::ostream& operator<<(std::ostream& os, T value)
{
    return os.iword(utils::enum_traits<T>::xalloc_index)
        ? (os << utils::enum_traits<T>::to_string.at(value))
        : (os << static_cast<std::underlying_type_t<T>>(value));
}

template<utils::has_input_enum_traits T>
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
