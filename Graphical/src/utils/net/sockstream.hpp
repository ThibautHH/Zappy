/*
** EPITECH PROJECT, 2024
** Utils
** File description:
** utils::net::sockstream
*/

#ifndef UTILS_NET_SOCKSTREAM_HPP_
    #define UTILS_NET_SOCKSTREAM_HPP_

    #include <iostream>

    #include "socket.hpp"
    #include "sockbuf.hpp"

namespace utils::net {
    template<class CharT, class Traits = std::char_traits<CharT>>
    class basic_sockstream : public std::basic_iostream<CharT, Traits> {
        private:
            typedef CharT char_type;
            typedef Traits traits_type;
            static_assert(std::is_same_v<typename Traits::char_type, CharT>, "Traits::char_type must be CharT");
            typedef Traits::int_type int_type;
            typedef Traits::pos_type pos_type;
            typedef Traits::off_type off_type;
            typedef int native_handle_type;

            basic_sockbuf<CharT, Traits> _buf;

        public:
            basic_sockstream(socket socket)
                : std::basic_iostream<CharT, Traits>(&_buf), _buf(std::move(socket))
            {
            }

            constexpr native_handle_type native_handle() const noexcept { return _buf.socket().fd(); }

            constexpr bool block() const noexcept { return _buf.block(); }
            constexpr bool block(bool block) noexcept { return _buf.block(block); }
    };

    typedef basic_sockstream<char> sockstream;
    typedef basic_sockstream<wchar_t> wsockstream;
}

#endif /* !UTILS_NET_SOCKSTREAM_HPP_ */
