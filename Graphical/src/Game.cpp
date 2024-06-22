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
    std::string message = "";
    if (!message.empty()) {
        Protocol::parseServerMessage(gameState, message);
        renderer.updateGameState(gameState);
    }
}

void Game::render() {
    window.clear();
    renderer.draw();
    window.display();
}
