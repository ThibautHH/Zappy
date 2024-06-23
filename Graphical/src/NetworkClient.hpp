/*
** EPITECH PROJECT, 2024
** Zappy GUI
** File description:
** Zappy::GUI::NetworkClient
*/

#ifndef ZAPPY_NETWORKCLIENT_HPP_
    #define ZAPPY_NETWORKCLIENT_HPP_

    #include "utils/net/sockstream.hpp"

    #include "Event.hpp"

namespace Zappy::GUI {
    class NetworkClient {
        public:
            NetworkClient(std::string host, std::string port);

            bool poll(Event &event);

        private:
            utils::net::sockstream _sockstream;
    };
}

#endif /* !ZAPPY_NETWORKCLIENT_HPP_ */
