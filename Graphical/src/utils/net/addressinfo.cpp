/*
** EPITECH PROJECT, 2024
** Utils
** File description:
** utils::net::addressinfo
*/

#include <cerrno>
#include <memory>
#include <netdb.h>
#include <optional>

#include "addressinfo.hpp"

using namespace utils::net;

const class addressinfo_error_category addressinfo_error_category = {};

std::string addressinfo_error_category::message(int code) const
{
    if (code == EAI_SYSTEM)
        return std::system_category().message(errno);
    return gai_strerror(code);
}

std::error_condition addressinfo_error_category::default_error_condition(int code) const noexcept
{
    if (code == EAI_SYSTEM)
        return std::error_condition(errno, std::system_category());
    return std::error_condition(code, *this);
}

addressinfo::addressinfo(std::string service, bool passive, bool name,
    enum socket::domain family, enum socket::type type, enum socket::protocol protocol)
    : _passive(passive), _host(), _service(std::move(service)),
    _info(this->get_info(family, type, protocol, name), freeaddrinfo)
{
}

addressinfo::addressinfo(std::string service, const socket &socket, bool passive, bool name)
    : _passive(passive), _host(), _service(std::move(service)),
    _info(this->get_info(socket.domain(), socket.type(), socket.protocol(), name), freeaddrinfo)
{
}

addressinfo::addressinfo(std::string host, std::optional<std::string> service, bool name,
    enum socket::domain family, enum socket::type type, enum socket::protocol protocol)
    : _passive(false), _host(std::move(host)), _service(std::move(service)),
    _info(this->get_info(family, type, protocol, name), freeaddrinfo)
{
}

addressinfo::addressinfo(std::string host, std::optional<std::string> service, const socket &socket, bool name)
    : _passive(false), _host(std::move(host)), _service(std::move(service)),
    _info(this->get_info(socket.domain(), socket.type(), socket.protocol(), name), freeaddrinfo)
{
}

utils::net::socket addressinfo::make_socket() const
{
    for (auto addr : *this) {
        utils::net::socket socket(addr.family(), addr.type(), addr.protocol());
        if (this->is_passive())
            try {
                socket.bind(addr);
            } catch (const std::system_error &e) {
                if (e.code().value() == EADDRINUSE)
                    continue;
                throw;
            }
        else
            try {
                socket.connect(addr);
            } catch (const std::system_error &e) {
                if (e.code().value() == ECONNREFUSED)
                    continue;
                throw;
            }
        return socket;
    }
    throw std::runtime_error("no valid address");
}

addressinfo::info_type *addressinfo::get_info(enum socket::domain family, enum socket::type type, enum socket::protocol protocol, bool name)
{
    const info_type hints = {
        (this->is_passive() ? AI_PASSIVE : 0) | (name ? AI_CANONNAME : 0),
        static_cast<int>(family),
        static_cast<int>(type),
        static_cast<int>(protocol),
        0, nullptr, nullptr, nullptr
    };
    info_type *info;
    if (int status = getaddrinfo(this->_host.value_or(nullptr).c_str(), this->_service.value_or(nullptr).c_str(),
            std::addressof(hints), std::addressof(info));
        status != 0)
        throw std::system_error(status, addressinfo_category(), "getaddrinfo");
    return info;
}
