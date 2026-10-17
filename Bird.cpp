#include "SFML/Window/Event.hpp"
#include <SFML/Graphics.hpp>
#include "Bird.h"
Bird::Bird(const sf::Texture& texture): sprite(texture){

    shape.setSize(sf::Vector2f(48,36));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);
    sprite.setPosition(position);
    sprite.setScale({1.2f,1.2f});


}
void Bird::jump() {
    velocityY = jumpStrength;
}
void Bird::draw(sf::RenderTarget& target) const {
    target.draw(sprite);
}
void Bird::update( float delta) {
    velocityY = velocityY + gravity * delta;
    shape.move(sf::Vector2f(0.f,velocityY * delta));
    sprite.setPosition(shape.getPosition());
}

sf::FloatRect Bird::getBounds()const {
    return shape.getGlobalBounds();
}

bool Bird::isOutOfBounds(float windowHeight) const {
    sf::FloatRect bounds = shape.getGlobalBounds();
    return bounds.position.y < 0.f || bounds.position.y + bounds.size.y > windowHeight;
}

void Bird::reset() {
    shape.setPosition(position);
    velocityY = 0;
    sprite.setPosition(shape.getPosition());
}


