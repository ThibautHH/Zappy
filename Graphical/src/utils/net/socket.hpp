/*
** EPITECH PROJECT, 2024
** Utils
** File description:
** utils::net::socket
*/

#ifndef UTILS_NET_SOCKET_HPP_
    #define UTILS_NET_SOCKET_HPP_

    #include <memory>
    #include <netinet/in.h>
    #include <sys/socket.h>

    #include "../utility.hpp"

namespace utils::net {
    class sockaddress;
    class addressinfo;

    class socket {
        public:
            enum class domain { unspecified = AF_UNSPEC, inet = AF_INET, inet6 = AF_INET6, unix = AF_UNIX };
            enum class type { any = 0, stream = SOCK_STREAM, datagram = SOCK_DGRAM, sequence = SOCK_SEQPACKET };
            enum class protocol { free = 0, tcp = IPPROTO_TCP, udp = IPPROTO_UDP };

            socket(domain domain, type type = type::stream, protocol protocol = protocol::free);

            socket(const socket &) = delete;
            constexpr socket(socket &&other) noexcept
                : _domain(other._domain), _type(other._type), _protocol(other._protocol),
                _fd(other._fd), _bound(other._bound), _connected(other._connected),
                _shutdown(other._shutdown), _eof(other._eof)
            {
                other._domain = domain::unspecified;
                other._type = type::any;
                other._protocol = protocol::free;
                other._fd = -1;
                other._bound = false;
                other._connected = false;
                other._shutdown = false;
                other._eof = false;
            }

            constexpr ~socket()
            {
                if (this->_fd != -1)
                    ::close(this->_fd);
            }

            socket &operator=(const socket &) = delete;

            constexpr domain domain() const noexcept { return this->_domain; }
            constexpr type type() const noexcept { return this->_type; }
            constexpr protocol protocol() const noexcept { return this->_protocol; }

            constexpr int fd() const noexcept { return this->_fd; }
            constexpr bool bound() const noexcept { return this->_bound; }
            constexpr bool connected() const noexcept { return this->_connected; }
            constexpr bool shutdown() const noexcept { return this->_shutdown; }
            constexpr void shutdown(bool shutdown) noexcept { this->_shutdown = shutdown; }
            constexpr bool eof() const noexcept { return this->_eof; }
            constexpr void eof(bool eof) noexcept { this->_eof = eof; }

            void bind(sockaddress address);
            void bind(addressinfo info);
            void listen(int backlog = 0);

            void connect(sockaddress address);
            void connect(addressinfo info);

        private:
            enum domain _domain;
            enum type _type;
            enum protocol _protocol;
            int _fd;
            bool _bound, _connected,
                _shutdown, _eof;
    };
}

#endif /* !UTILS_NET_SOCKET_HPP_ */
