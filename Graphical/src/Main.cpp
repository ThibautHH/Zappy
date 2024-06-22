/*
** EPITECH PROJECT, 2024
** Zappy GUI
** File description:
** Program entrypoint
*/

#include <SFML/Graphics.hpp>
#include "../include/Game.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Zappy GUI");
    Game game(window);

    game.run();

    return 0;
}
