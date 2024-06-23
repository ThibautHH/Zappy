/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Game.cpp
*/

#include "Game.hpp"

using namespace Zappy::GUI;

Game::Game(NetworkClient client)
    : window(sf::VideoMode(800, 600), "Zappy GUI"),
    renderer(window), client(std::move(client)),
    gameState()
{}

void Game::run()
{
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
        if (event.type == sf::Event::Closed)
            window.close();
}

void Game::update()
{
    Event event;
    while (client.poll(event))
        event.update(gameState);
}

void Game::render()
{
    window.clear();
    renderer.draw(gameState);
    window.display();
}
