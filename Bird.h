#pragma once
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp";

class Bird {
private:
    static constexpr float gravity = 900.f;
    static constexpr float jumpStrength = -350.f;
    float velocityY = 0.f;
    sf::RectangleShape shape;

public:
    void update( float delta);
    void jump();
    void draw(sf::RenderTarget& target) const;
    sf::FloatRect getBounds()const;
    bool isOutOfBounds(float windowHeight) const;
    Bird();
};


