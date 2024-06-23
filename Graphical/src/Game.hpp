/*
** EPITECH PROJECT, 2024
** Zappy GUI
** File description:
** Zappy::GUI::Game
*/

#ifndef ZAPPY_GUI_GAME_HPP_
    #define ZAPPY_GUI_GAME_HPP_

    #include <SFML/Graphics.hpp>
    #include <thread>
    #include "NetworkClient.hpp"
    #include "Renderer.hpp"
    #include "GameState.hpp"

namespace Zappy::GUI {
    class Game {
    public:
        Game(NetworkClient client);
        ~Game();
        void run();

    private:
        void handleEvents();
        void update();
        static void getPlayers(std::stop_token st, Game &game);

        sf::RenderWindow window;
        Renderer renderer;
        NetworkClient client;
        GameState gameState;
        std::jthread playerInfoThread;
    };
}

#endif /* !ZAPPY_GUI_GAME_HPP_ */
