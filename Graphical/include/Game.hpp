/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Game.hpp
*/

#ifndef GAME_HPP
    #define GAME_HPP

    #include <SFML/Graphics.hpp>
    #include "Renderer.hpp"
    #include "GameState.hpp"
    #include "Network.hpp"

    class Game {
    public:
        Game(sf::RenderWindow& window);
        void run();

    private:
        void handleEvents();
        void update();
        void render();

        sf::RenderWindow& window;
        Renderer renderer;
        GameState gameState;
        Network network;
    };

#endif
