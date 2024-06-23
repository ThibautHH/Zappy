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
                _fd(other._fd), _bound(other._bound), _connected(other._connected)
            {
                other._fd = -1;
            }

            constexpr ~socket()
            {
                if (this->_fd != -1)
                    ::close(this->_fd);
            }

            socket &operator=(const socket &) = delete;
            constexpr socket &operator=(socket &&other) noexcept(noexcept(
                std::construct_at(std::addressof(utils::declvar<socket>()), std::declval<socket>())))
            {
                this->~socket();
                return *std::construct_at(this, std::move(other));
            }

            constexpr domain domain() const noexcept { return this->_domain; }
            constexpr type type() const noexcept { return this->_type; }
            constexpr protocol protocol() const noexcept { return this->_protocol; }

            constexpr int fd() const noexcept { return this->_fd; }
            constexpr bool bound() const noexcept { return this->_bound; }
            constexpr bool connected() const noexcept { return this->_connected; }

            void bind(sockaddress address);
            void bind(addressinfo info);
            void listen(int backlog = 0);

            void connect(sockaddress address);
            void connect(addressinfo info);

        private:
            const enum domain _domain;
            const enum type _type;
            const enum protocol _protocol;
            int _fd;
            bool _bound, _connected;
    };
}

#endif /* !UTILS_NET_SOCKET_HPP_ */
