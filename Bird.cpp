#include "SFML/Window/Event.hpp"
#include <SFML/Graphics.hpp>
#include "Bird.h"
void Bird::jump() {
    velocityY = jumpStrength;
}
void Bird::draw(sf::RenderTarget& target) const {
    target.draw(shape);
}
void Bird::update( float delta) {
    velocityY = velocityY + gravity * delta;
    shape.move(sf::Vector2f(0.f,velocityY * delta));
}

sf::FloatRect Bird::getBounds()const {
    return shape.getGlobalBounds();
}

bool Bird::isOutOfBounds(float windowHeight) const {
    sf::FloatRect bounds = shape.getGlobalBounds();
    return bounds.position.y < 0.f || bounds.position.y + bounds.size.y > windowHeight;
}

Bird::Bird() {
    shape.setSize(sf::Vector2f(40.f,40.f));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(sf::Vector2f(200.f,300.f));
}
