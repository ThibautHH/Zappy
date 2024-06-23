/*
** EPITECH PROJECT, 2024
** Utils
** File description:
** utils::net::addressinfo
*/

#ifndef UTILS_NET_ADDRESSINFO_HPP_
    #define UTILS_NET_ADDRESSINFO_HPP_

    #include <memory>
    #include <netdb.h>
    #include <optional>

    #include "sockaddress.hpp"
    #include "socket.hpp"

namespace utils::net {
    class addressinfo_iterator;

    class addressinfo_error_category : public std::error_category {
        public:
            virtual constexpr const char *name() const noexcept override { return "addressinfo"; }

            virtual std::string message(int code) const override;

            virtual std::error_condition default_error_condition(int code) const noexcept override;
    };

    const addressinfo_error_category addressinfo_error_category;

    constexpr const std::error_category &addressinfo_category() noexcept { return addressinfo_error_category; }

    class addressinfo {
        public:
            typedef struct addrinfo info_type;
            typedef addressinfo_iterator iterator;
            typedef addressinfo_iterator const_iterator;

            inline _GLIBCXX23_CONSTEXPR iterator begin() noexcept;
            inline _GLIBCXX23_CONSTEXPR const_iterator begin() const noexcept;
            inline _GLIBCXX23_CONSTEXPR const_iterator cbegin() const noexcept;
            constexpr iterator end() noexcept;
            constexpr const_iterator end() const noexcept;
            constexpr const_iterator cend() const noexcept;

            addressinfo(std::string service, bool passive = true, bool name = false,
                enum socket::domain family = socket::domain::unspecified,
                enum socket::type type = socket::type::stream,
                enum socket::protocol protocol = socket::protocol::free);

            addressinfo(std::string service, const socket &socket, bool passive = true, bool name = false);

            addressinfo(std::string host, std::optional<std::string> service, bool name = false,
                enum socket::domain family = socket::domain::unspecified,
                enum socket::type type = socket::type::stream,
                enum socket::protocol protocol = socket::protocol::free);

            addressinfo(std::string host, std::optional<std::string> service, const socket &socket, bool name = false);

            constexpr bool is_passive() const noexcept { return this->_passive; }

            socket make_socket() const;

        private:
            const bool _passive;
            const std::optional<const std::string> _host, _service;
            const std::unique_ptr<std::remove_const_t<info_type>, decltype(freeaddrinfo) *> _info;

            info_type *get_info(enum socket::domain family, enum socket::type type, enum socket::protocol protocol, bool name);
    };

    struct addressinfo_iterator {
        using difference_type = std::ptrdiff_t;
        using value_type = sockaddressinfo;

        constexpr addressinfo_iterator(addressinfo::info_type * const info) noexcept
            : _info(info)
        {}

        constexpr value_type operator*() const noexcept { return value_type(this->_info); }

        constexpr addressinfo_iterator &operator++() noexcept
        {
            this->_info = this->_info->ai_next;
            return *this;
        }

        constexpr void operator++(int) noexcept { ++*this; }

        constexpr bool operator==(const addressinfo_iterator &other) const noexcept { return this->_info == other._info; }

        private:
            const addressinfo::info_type *_info;
    };

    static_assert(std::input_iterator<addressinfo_iterator>);

    _GLIBCXX23_CONSTEXPR addressinfo::iterator addressinfo::begin() noexcept { return this->cbegin(); }
    _GLIBCXX23_CONSTEXPR addressinfo::const_iterator addressinfo::begin() const noexcept { return this->cbegin(); }
    _GLIBCXX23_CONSTEXPR addressinfo::const_iterator addressinfo::cbegin() const noexcept { return addressinfo::const_iterator(this->_info.get()); }
    constexpr addressinfo::iterator addressinfo::end() noexcept { return this->cend(); }
    constexpr addressinfo::const_iterator addressinfo::end() const noexcept { return this->cend(); }
    constexpr addressinfo::const_iterator addressinfo::cend() const noexcept { return addressinfo::const_iterator(nullptr); }
}

#endif /* !UTILS_NET_ADDRESSINFO_HPP_ */
