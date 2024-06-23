/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Protocol.hpp
*/

#ifndef PROTOCOL_HPP
    #define PROTOCOL_HPP

    #include "GameState.hpp"
    #include <string>

    class Protocol {
    public:
        static void parseServerMessage(GameState& gameState, const std::string& message);
    };

#endif
