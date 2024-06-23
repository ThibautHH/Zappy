/*
** EPITECH PROJECT, 2024
** Utils
** File description:
** utils::net::sockaddress
*/

#ifndef UTILS_NET_SOCKADDRESS_HPP_
    #define UTILS_NET_SOCKADDRESS_HPP_

    #include <netdb.h>
#include <optional>
    #include "socket.hpp"

namespace utils::net {
    class sockaddress {
        public:
            typedef const struct sockaddr *sockaddr_ptr;

            constexpr sockaddress(const sockaddr_ptr ptr, const socklen_t len) noexcept
                : _ptr(ptr), _len(len)
            {}

            constexpr sockaddr_ptr sockaddr() const noexcept { return this->_ptr; }
            constexpr socklen_t addrlen() const noexcept { return this->_len; }

            constexpr enum socket::domain family() const noexcept { return static_cast<enum socket::domain>(this->_ptr->sa_family); }

        private:
            const sockaddr_ptr _ptr;
            const socklen_t _len;
    };

    class sockaddressinfo : public sockaddress {
        public:
            typedef struct addrinfo info_type;

            constexpr sockaddressinfo(const info_type * const info) noexcept
                : sockaddress(info->ai_addr, info->ai_addrlen),
                _type(static_cast<enum socket::type>(info->ai_socktype)),
                _protocol(static_cast<enum socket::protocol>(info->ai_protocol)),
                canonical_name(info->ai_canonname ? std::make_optional(info->ai_canonname) : std::nullopt)
            {}

            constexpr enum socket::type type() const noexcept { return this->_type; }
            constexpr enum socket::protocol protocol() const noexcept { return this->_protocol; }
            constexpr std::optional<const std::string> canonname() const noexcept { return this->canonical_name; }

        private:
            const enum socket::type _type;
            const enum socket::protocol _protocol;
            const std::optional<const std::string> canonical_name;
    };

    // template<typename AddressType>
    // class sockaddress : public sockaddress_base {
    //     public:
    //         typedef sockaddress_base::sockaddr_ptr sockaddr_ptr;
    //         typedef std::remove_cvref_t<AddressType> address_type;
    //         typedef const address_type *address_ptr;

    //         constexpr address_ptr address() const noexcept { return std::addressof(_address); }

    //     protected:
    //         constexpr sockaddress(address_type address) noexcept
    //             : sockaddress_base(sizeof(address_type)), _address(std::move(address))
    //         {}

    //         constexpr virtual sockaddr_ptr addressp() const noexcept override { return reinterpret_cast<sockaddr_ptr>(std::addressof(_address)); }

    //     private:
    //         const address_type _address;
    // };

    // class sockaddress_in : public sockaddress<struct sockaddr_in> {
    //     public:
    //         typedef struct sockaddr_in address_type;

    //         constexpr sockaddress_in(const address_type address) : sockaddress(address)
    //         {
    //             if (address.sin_family != AF_INET)
    //                 throw std::invalid_argument("sockaddress_in: invalid address family");
    //         }
    // };

    // class sockaddress_in6 : public sockaddress {
    //     public:
    //         typedef struct sockaddr_in6 address_type;

    //         sockaddress_in6(const address_type &address)
    //             : sockaddress_in6(address_type(address))
    //         {
    //         }

    //         sockaddress_in6(in_port_t port, bool loopback = false)
    //             : sockaddress_in6({AF_INET6, htons(port), 0, loopback ? in6addr_loopback : in6addr_any})
    //         {
    //         }

    //     private:
    //         sockaddress_in6(address_type &&address)
    //             : sockaddress(std::addressof(_address)), _address(address)
    //         {
    //             if (_address.sin6_family != AF_INET6)
    //                 throw std::invalid_argument("sockaddress_in6: invalid address family");
    //         }

    //         const address_type _address;
    // };
}

#endif /* !UTILS_NET_SOCKADDRESS_HPP_ */
