/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Renderer.hpp
*/

#ifndef RENDERER_HPP
    #define RENDERER_HPP

    #include <SFML/Graphics.hpp>

    #include "GameState.hpp"

namespace Zappy::GUI {
    class Renderer {
    public:
        Renderer(sf::RenderWindow& window);

        void draw(const GameState& gameState);

    private:
        sf::RenderWindow& mWindow;
        sf::Texture mBackgroundTexture;
        sf::Sprite mBackgroundSprite;
        sf::Texture mPlayerTexture;
        sf::Sprite mPlayerSprite;
        sf::Texture mEggTexture;
        sf::Sprite mEggSprite;
        sf::Texture mResourceTexture;
        sf::Sprite mResourceSprite;
        sf::View mView;
        sf::Font mFont;
        sf::Text mResourceText;
        float mZoomLevel;

        void generateBackground(int width, int height);
        void drawResourceInfo(const Vector pos, const Inventory resources);
    };
}

#endif
