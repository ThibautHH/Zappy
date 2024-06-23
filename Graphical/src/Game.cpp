/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Game.cpp
*/

#include "../include/Game.hpp"
#include "../include/Protocol.hpp"
#include <iostream>

Game::Game(sf::RenderWindow& window)
    : window(window), renderer(window) {}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Game::update() {
    // test message
    std::string message = "msz 5 5";
    if (!message.empty()) {
        Protocol::parseServerMessage(gameState, message);
        renderer.updateGameState(gameState);
    }

    // code to test if it work
    int loop = 0;

    if (loop == 0) {
        gameState.updateTile(1, 1, {1, 2, 0, 0, 2, 0, 0});
        loop = 1;
    }
    // end of test
}


void Game::render() {
    window.clear();
    renderer.draw();
    window.display();
}
