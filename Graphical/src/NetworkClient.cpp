/*
** EPITECH PROJECT, 2024
** Zappy GUI
** File description:
** Zappy::GUI::NetworkClient
*/

#include <sstream>

#include "utils/net/addressinfo.hpp"

#include "NetworkClient.hpp"

using namespace Zappy::GUI;

NetworkClient::NetworkClient(std::string host, std::string port)
    : _sockstream(utils::net::addressinfo(host, port).make_socket())
{
    std::string line;
    std::getline(_sockstream, line);
    if (line != "WELCOME")
        throw std::runtime_error("Invalid welcome message");
    _sockstream << "GRAPHIC" << std::endl;
    _sockstream.block(false);
}

void NetworkClient::getPlayer(int id)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _sockstream << "ppo #" << id
        << "\nplv #" << id
        << "\npin #" << id << std::endl;
}

bool NetworkClient::poll(Event &event)
{
    std::lock_guard<std::mutex> lock(_mutex);
    std::string line;
    std::getline(_sockstream, line);
    if (!_sockstream.eof())
        _sockstream.clear();
    if (line.empty())
        return false;
    std::istringstream(line) >> event;
    return true;
}
