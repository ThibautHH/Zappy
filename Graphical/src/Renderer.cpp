/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Renderer.cpp
*/

#include "Renderer.hpp"
#include "GameState.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace Zappy::GUI;

Renderer::Renderer(sf::RenderWindow& window)
    : mWindow(window) {
    if (!mBackgroundTexture.loadFromFile("assets/background2.png")) {
        std::cout << "Error: can't load background texture." << std::endl;
    }
    mBackgroundSprite.setTexture(mBackgroundTexture);

    if (!mPlayerTexture.loadFromFile("assets/player2.png")) {
        std::cout << "Error: can't load player texture." << std::endl;
    }
    mPlayerSprite.setTexture(mPlayerTexture);

    if (!mEggTexture.loadFromFile("assets/egg2.png")) {
        std::cout << "Error: can't load egg texture." << std::endl;
    }
    mEggSprite.setTexture(mEggTexture);

    if (!mResourceTexture.loadFromFile("assets/resource2.png")) {
        std::cout << "Error: can't load resource texture." << std::endl;
    }
    mResourceSprite.setTexture(mResourceTexture);

    if (!mFont.loadFromFile("assets/arial.ttf")) {
        std::cout << "Error: can't load font." << std::endl;
    }
    mResourceText.setFont(mFont);
    mResourceText.setCharacterSize(5);
    mResourceText.setFillColor(sf::Color::Red);

    mView = window.getDefaultView();
}


void Renderer::draw(const GameState& gameState)
{
    mWindow.clear();

    auto [width, height] = gameState.getSize();

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

    sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
    sf::Vector2f worldPosition = mWindow.mapPixelToCoords(mousePosition);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            mBackgroundSprite.setPosition(x * mBackgroundTexture.getSize().x, y * mBackgroundTexture.getSize().y);
            mWindow.draw(mBackgroundSprite);

            const auto& resources = gameState.getTileResources(x, y);
            if (!resources.empty()) {
                mResourceSprite.setPosition(x * mBackgroundTexture.getSize().x, y * mBackgroundTexture.getSize().y);
                mWindow.draw(mResourceSprite);

                if (mResourceSprite.getGlobalBounds().contains(worldPosition)) {
                    drawResourceInfo(x, y, resources);
                }
            }
        }
    }

    const auto& players = gameState.getPlayers();
    for (const auto& pair : players) {
        const auto& player = pair.second;
        mPlayerSprite.setPosition(player.position.x * mBackgroundTexture.getSize().x, player.position.y * mBackgroundTexture.getSize().y);
        mWindow.draw(mPlayerSprite);
    }

    const auto& eggs = gameState.getEggs();
    for (const auto& pair : eggs) {
        const auto& egg = pair.second;
        mEggSprite.setPosition(egg.position.x * mBackgroundTexture.getSize().x, egg.position.y * mBackgroundTexture.getSize().y);
        mWindow.draw(mEggSprite);
    }

    mWindow.display();
}

void Renderer::drawResourceInfo(int x, int y, const std::vector<int>& resources) {
    std::string resourceInfo = "Resources:\n";
    for (size_t i = 0; i < resources.size(); ++i) {
        resourceInfo += "Resource " + std::to_string(i) + ": " + std::to_string(resources[i]) + "\n";
    }
    mResourceText.setString(resourceInfo);
    mResourceText.setPosition(-40, 0);
    mWindow.draw(mResourceText);
}
