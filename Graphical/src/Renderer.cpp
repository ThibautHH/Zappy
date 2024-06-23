/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Renderer.cpp
*/

#include "../include/Renderer.hpp"
#include "../include/GameState.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

Renderer::Renderer(sf::RenderWindow& window)
    : mWindow(window) {
    if (!mBackgroundTexture.loadFromFile("assets/background.png")) {
        std::cout << "Error: can't load background texture." << std::endl;
    }
    mBackgroundSprite.setTexture(mBackgroundTexture);

    if (!mPlayerTexture.loadFromFile("assets/player.png")) {
        std::cout << "Error: can't load player texture." << std::endl;
    }
    mPlayerSprite.setTexture(mPlayerTexture);

    if (!mEggTexture.loadFromFile("assets/egg.png")) {
        std::cout << "Error: can't load egg texture." << std::endl;
    }
    mEggSprite.setTexture(mEggTexture);

    mView = window.getDefaultView();

}

void Renderer::updateGameState(const GameState& gameState) {
    mGameState = gameState;
}

void Renderer::draw() {
    mWindow.clear();

    int width = mGameState.getWidth();
    int height = mGameState.getHeight();

    float windowWidth = mWindow.getSize().x;
    float windowHeight = mWindow.getSize().y;
    float mapWidth = width * mBackgroundTexture.getSize().x;
    float mapHeight = height * mBackgroundTexture.getSize().y;
    float zoomX = windowWidth / mapWidth;
    float zoomY = windowHeight / mapHeight;
    float zoomLevel = std::min(zoomX, zoomY);

    mView.setSize(windowWidth, windowHeight);
    mView.setCenter(mapWidth / 2, mapHeight / 2);
    mView.zoom(1.0f / zoomLevel);
    mWindow.setView(mView);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            mBackgroundSprite.setPosition(x * mBackgroundTexture.getSize().x, y * mBackgroundTexture.getSize().y);
            mWindow.draw(mBackgroundSprite);

        }
    }

    const auto& players = mGameState.getPlayers();
    for (const auto& pair : players) {
        const auto& player = pair.second;
        mPlayerSprite.setPosition(player.x * mBackgroundTexture.getSize().x, player.y * mBackgroundTexture.getSize().y);
        mWindow.draw(mPlayerSprite);
    }

    const auto& eggs = mGameState.getEggs();
    for (const auto& pair : eggs) {
        const auto& egg = pair.second;
        mEggSprite.setPosition(egg.x * mBackgroundTexture.getSize().x, egg.y * mBackgroundTexture.getSize().y);
        mWindow.draw(mEggSprite);
    }

    mWindow.display();
}
