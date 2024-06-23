/*
** EPITECH PROJECT, 2024
** Zappy GUI
** File description:
** Zappy::GUI::NetworkClient
*/

#ifndef ZAPPY_NETWORKCLIENT_HPP_
    #define ZAPPY_NETWORKCLIENT_HPP_

    #include <mutex>

    #include "utils/net/sockstream.hpp"

    #include "Event.hpp"

namespace Zappy::GUI {
    class NetworkClient {
        public:
            NetworkClient(std::string host, std::string port);
            NetworkClient(NetworkClient &&other)
                : _sockstream(std::move(other._sockstream)), _mutex()
            {}

            bool poll(Event &event);
            void getPlayer(int id);

        private:
            utils::net::sockstream _sockstream;
            std::mutex _mutex;
    };
}

#endif /* !ZAPPY_NETWORKCLIENT_HPP_ */
