#pragma once

#include "SFML/Graphics.hpp"
class Pipe {
    private:

        static constexpr float gap = 150.f;
        static constexpr float width = 60.f;
        static constexpr float windowHeight = 600.f;
        sf::RectangleShape topShape;
        sf::RectangleShape botShape;
    public:
        void draw(sf::RenderTarget& target) const;
        Pipe(float x, float gapTop);

};