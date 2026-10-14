#pragma once

#include "SFML/Graphics.hpp"
class Pipe {
    private:


        static constexpr float width = 60.f;
        static constexpr float speed = 150.f;
        sf::RectangleShape topShape;
        sf::RectangleShape botShape;
    public:
        static constexpr float windowHeight = 600.f;
        static constexpr float gap = 150.f;
        void draw(sf::RenderTarget& target) const;
        void update(float delta);
        bool isOffScreen() const;
        Pipe(float x, float gapTop);
};