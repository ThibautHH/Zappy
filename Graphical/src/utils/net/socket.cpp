/*
** EPITECH PROJECT, 2024
** Utils
** File description:
** utils::net::socket
*/

#include <system_error>
#include <unistd.h>

#include "addressinfo.hpp"
#include "socket.hpp"
#include "sockaddress.hpp"

using namespace utils::net;

socket::socket(enum domain domain, enum type type, enum protocol protocol)
    : _domain(domain), _type(type), _protocol(protocol),
#define i(x) static_cast<int>(x)
    _fd(::socket(i(domain), i(type), i(protocol))),
#undef i
    _bound(false), _connected(false)
{
    if (this->_fd == -1)
        throw std::system_error(errno, std::system_category(), "socket");
}

void socket::bind(sockaddress address)
{
    if (this->_bound)
        throw std::logic_error("socket already bound");
    if (::bind(this->_fd, address.sockaddr(), address.addrlen()) == -1)
        throw std::system_error(errno, std::system_category(), "bind");
    this->_bound = true;
}

void socket::bind(addressinfo info)
{
    for (auto addr : info)
        try {
            this->bind(addr);
            return;
        } catch (const std::system_error &e) {
            if (e.code().value() != EADDRINUSE)
                throw;
        }
    throw std::system_error(EADDRINUSE, std::system_category(), "bind");
}

void socket::listen(int backlog)
{
    if (this->_type == type::datagram)
        throw std::logic_error("cannot listen on connection-less socket");
    if (!this->_bound)
        throw std::logic_error("socket not bound");
    if (::listen(this->_fd, backlog) == -1)
        throw std::system_error(errno, std::system_category(), "listen");
}

void socket::connect(sockaddress address)
{
    if (this->_connected
        // Allow connection resetting
        && address.family() != domain::unspecified
        // except for Unix sockets, which cannot connect more than once
        && this->_domain != domain::unix)
        throw std::logic_error("socket already connected");
    if (::connect(this->_fd, address.sockaddr(), address.addrlen()) == -1)
        throw std::system_error(errno, std::system_category(), "connect");
    this->_connected = (address.family() != domain::unspecified);
}

void socket::connect(addressinfo info)
{
    for (auto addr : info)
        try {
            this->connect(addr);
            return;
        } catch (const std::system_error &e) {
            if (e.code().value() != ECONNREFUSED)
                throw;
        }
    throw std::system_error(ECONNREFUSED, std::system_category(), "connect");
}
