#include "SFML/Window/Event.hpp"
#include <SFML/Graphics.hpp>
#include "Bird.h"
Bird::Bird(const std::vector<sf::Texture>& tex): textures(&tex) , sprite(tex[0]){

    shape.setSize(sf::Vector2f(48,36));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);
    sprite.setPosition(position);
    sprite.setScale({1.2f,1.2f});
    sf::Vector2u texSize = (*textures)[0].getSize();
    sprite.setOrigin({texSize.x / 2.f,texSize.y / 2.f});// set origin to center not top left
    syncSprite();
}

void Bird::syncSprite() {
    sprite.setPosition(shape.getPosition() + shape.getSize() / 2.f);
    float angle = std::clamp(velocityY * tiltFactor, maxUp,maxDown);
    sprite.setRotation(sf::degrees(angle));
}

void Bird::animate(float delta) {
    animTimer += delta;
    if (animTimer >= frameTime) {
        animTimer -= frameTime;
        frame = (frame + 1) % textures->size(); // this % when it goes to 3 sets it to 0
        sprite.setTexture((*textures)[frame]);
    }
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
    syncSprite();
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
    frame = 0;
    animTimer = 0.f;
    sprite.setTexture((*textures)[0]);
    syncSprite();
}


