/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Renderer.cpp
*/

#include <sstream>

#include <SFML/Graphics.hpp>

#include "GameState.hpp"

#include "Renderer.hpp"

using namespace Zappy::GUI;

Renderer::Renderer(sf::RenderWindow& window)
    : mWindow(window), mView(window.getDefaultView())
{
    if (!mBackgroundTexture.loadFromFile("assets/background2.png"))
        throw std::runtime_error("Can't load background texture.");
    mBackgroundSprite.setTexture(mBackgroundTexture);

    if (!mPlayerTexture.loadFromFile("assets/player2.png"))
        throw std::runtime_error("Can't load player texture.");
    mPlayerSprite.setTexture(mPlayerTexture);

    if (!mEggTexture.loadFromFile("assets/egg2.png"))
        throw std::runtime_error("Can't load egg texture.");
    mEggSprite.setTexture(mEggTexture);

    if (!mResourceTexture.loadFromFile("assets/resource2.png"))
        throw std::runtime_error("Can't load resource texture.");
    mResourceSprite.setTexture(mResourceTexture);

    if (!mFont.loadFromFile("assets/arial.ttf"))
        throw std::runtime_error("Can't load font.");
    mResourceText.setFont(mFont);
    mResourceText.setCharacterSize(5);
    mResourceText.setFillColor(sf::Color::Red);
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

    Vector tilePos{};
    Inventory resources{};

    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x) {
            mBackgroundSprite.setPosition(x * mBackgroundTexture.getSize().x, y * mBackgroundTexture.getSize().y);
            mWindow.draw(mBackgroundSprite);

            const auto& displayedContents = gameState.getTileResources({x, y});
            mResourceSprite.setPosition(x * mBackgroundTexture.getSize().x, y * mBackgroundTexture.getSize().y);
            mWindow.draw(mResourceSprite);

            if (mResourceSprite.getGlobalBounds().contains(worldPosition)) {
                tilePos = {x, y};
                resources = displayedContents;
            }
        }

    drawResourceInfo(tilePos, resources);

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

static const char * const resourcesNames[7] = {
    "Food",
    "Linemate",
    "Deraumere",
    "Sibur",
    "Mendiane",
    "Phiras",
    "Thystame"
};

void Renderer::drawResourceInfo(const Vector pos, const Inventory resources) {
    std::ostringstream resourceInfo;
    resourceInfo << "Tile " << pos << ":\n";
    for (size_t i = 0; i < 7; ++i)
        resourceInfo << resourcesNames[i] << ": " << resources[i] << '\n';
    mResourceText.setString(resourceInfo.str());
    mResourceText.setPosition(-40, 0);
    mWindow.draw(mResourceText);
}
