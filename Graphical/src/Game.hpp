/*
** EPITECH PROJECT, 2024
** Zappy GUI
** File description:
** Zappy::GUI::Game
*/

#ifndef ZAPPY_GUI_GAME_HPP_
    #define ZAPPY_GUI_GAME_HPP_

    #include <SFML/Graphics.hpp>
    #include "NetworkClient.hpp"
    #include "Renderer.hpp"
    #include "GameState.hpp"

namespace Zappy::GUI {
    class Game {
    public:
        Game(NetworkClient client);
        void run();

    private:
        void handleEvents();
        void update();
        void render();

        sf::RenderWindow window;
        Renderer renderer;
        NetworkClient client;
        GameState gameState;
    };
}

#endif /* !ZAPPY_GUI_GAME_HPP_ */
