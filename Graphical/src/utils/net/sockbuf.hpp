/*
** EPITECH PROJECT, 2024
** Utils
** File description:
** utils::net::sockbuf
*/

#ifndef UTILS_NET_SOCKBUF_HPP_
    #define UTILS_NET_SOCKBUF_HPP_

    #include <cerrno>
    //#include <locale>
    #include <system_error>
    #include <unistd.h>
    #include <streambuf>
    #include <sys/socket.h>

    #include "socket.hpp"

namespace utils::net {
    template<class CharT, class Traits = std::char_traits<CharT>>
    class basic_sockbuf : public std::basic_streambuf<CharT, Traits> {
        private:
            typedef CharT char_type;
            typedef Traits traits_type;
            static_assert(std::is_same_v<typename Traits::char_type, CharT>, "Traits::char_type must be CharT");
            typedef Traits::int_type int_type;
            typedef Traits::pos_type pos_type;
            typedef Traits::off_type off_type;

            char_type _ibuf[BUFSIZ], _obuf[BUFSIZ];

            const class socket _socket;
            bool _shutdown = false;
            bool _block = true;

            //std::locale _locale;

        public:
            basic_sockbuf(class socket socket)
                : std::basic_streambuf<CharT, Traits>(), _socket(std::move(socket))
            {
                if (!_socket.connected())
                    throw std::logic_error("socket not connected");
                this->setg(_ibuf, _ibuf, _ibuf);
                this->setp(_obuf, _obuf + BUFSIZ + 1);
            }

            ~basic_sockbuf()
            {
                this->sync();
            }

            constexpr const class socket &socket() const noexcept { return _socket; }

            constexpr bool block() const noexcept { return _block; }
            constexpr bool block(bool block) noexcept { bool old = _block; _block = block; return old; }
            constexpr bool shutdown() const noexcept { return _shutdown; }

        protected:
            //virtual void imbue(const std::locale &loc) override
            //{
            //    this->_locale = loc;
            //}

            virtual int sync() override
            {
                return this->overflow(Traits::eof()) | this->underflow();
            }

            virtual std::streamsize showmanyc() override
            {
                int count = recv(this->_socket.fd(), NULL, BUFSIZ, MSG_DONTWAIT | MSG_PEEK | MSG_TRUNC);
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wlogical-op"
                if (count == 0 || (count < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)))
    #pragma GCC diagnostic pop
                    return -1;
                if (count < 0)
                    throw std::system_error(errno, std::system_category(), "recv");
                return count;
            }

            virtual int_type underflow() override
            {
                int res = recv(this->_socket.fd(), this->eback(), BUFSIZ, this->_block ? 0 : MSG_DONTWAIT);
                if (res == 0)
                    return Traits::eof();
                if (res < 0)
                    throw std::system_error(errno, std::system_category(), "recv");
                this->setg(this->eback(), this->eback(), this->eback() + res);
                return Traits::to_int_type(*this->gptr());
            }

            virtual int_type overflow(int_type ch) override
            {
                if (this->_shutdown)
                    return Traits::eof();
                int res = send(this->_socket.fd(), this->pbase(), this->pptr() - this->pbase(), MSG_NOSIGNAL);
                if (res < 0) {
                    if (errno == EPIPE) {
                        this->_shutdown = true;
                        return Traits::eof();
                    } else
                        throw std::system_error(errno, std::system_category(), "send");
                }
                this->setp(this->pbase(), this->epptr());
                if (ch != Traits::eof())
                    this->sputc(ch);
                return !Traits::eof();
            }
    };

    typedef basic_sockbuf<char> sockbuf;
    typedef basic_sockbuf<wchar_t> wsockbuf;
}

#endif /* !UTILS_NET_SOCKBUF_HPP_ */
