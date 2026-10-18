#pragma once
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp";
#include <SFML/Graphics.hpp>
class Bird {
private:
    static constexpr float gravity = 900.f;
    static constexpr float jumpStrength = -350.f;
    float velocityY = 0.f;
    sf::RectangleShape shape;
    sf::Vector2f position = {200.f, 300.f};
    const std::vector<sf::Texture>* textures;
    sf::Sprite sprite;
    float animTimer = 0.f;
    std::size_t frame = 0;
    static constexpr float frameTime = 0.1f;


public:
    Bird(const std::vector<sf::Texture>& textures);
    void animate(float delta);
    void update( float delta);
    void jump();
    void draw(sf::RenderTarget& target) const;
    sf::FloatRect getBounds()const;
    bool isOutOfBounds(float windowHeight) const;
    void reset();

};


