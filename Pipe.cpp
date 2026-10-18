#include "Bird.h"
#include "Pipe.h"
#include "SFML/Window/Event.hpp"
#include <SFML/Graphics.hpp>

Pipe::Pipe(float x, float gapTop , const sf::Texture& texture): topSprite(texture),botSprite(texture) {
  topShape.setSize({width -2 * hitboxInset, gapTop - hitboxYInset});
  topShape.setPosition(sf::Vector2f(x+ hitboxInset, 0.f));
  botShape.setSize(sf::Vector2f(width - 2 * hitboxInset, windowHeight - gapTop - gap - hitboxYInset));
  botShape.setPosition(sf::Vector2f(x + hitboxInset, gapTop + gap + hitboxYInset));

  topShape.setFillColor(sf::Color::Green);
  botShape.setFillColor(sf::Color::Green);
  int texW = texture.getSize().x;
  int texH = texture.getSize().y;
  int topH = static_cast<int>(gapTop);
  int botH = static_cast<int>(windowHeight - gapTop - gap);
  topSprite.setTextureRect(sf::IntRect({0,texH - topH}, {texW,topH}));//
  botSprite.setTextureRect(sf::IntRect({0,0}, {texW,botH}));
  topSprite.setPosition(topShape.getPosition());
  botSprite.setPosition(botShape.getPosition());
}
void Pipe::update(float delta) {
  topShape.move(sf::Vector2f(-speed * delta, 0.f));
  botShape.move(sf::Vector2f(-speed * delta, 0.f));
  topSprite.setPosition({topShape.getPosition().x - hitboxInset, 0.f});
  botSprite.setPosition({botShape.getPosition() .x - hitboxInset, botShape.getPosition().y - hitboxYInset});
  syncSprite();
}

void Pipe::syncSprite() {
    float x = topShape.getPosition().x - hitboxInset;
  topSprite.setPosition({x,0.f});
  botSprite.setPosition({x,botShape.getPosition().y - hitboxYInset});
}

void Pipe::draw(sf::RenderTarget &target) const {
  target.draw(topSprite);
  target.draw(botSprite);
}

bool Pipe::isOffScreen() const {
  if (topShape.getPosition().x < -width) {
    return true;
  } else {
    return false;
  }
}
void Pipe::markScored() {
  Pipe::scored = true;
  return;
}
bool Pipe::isPassed(float birdx) {
  if (birdx > Pipe::topShape.getPosition().x + topShape.getSize().x && Pipe::scored == false) {
    Pipe::markScored();
    return true;
  }
  return false;
}

bool Pipe::collidesWith(const sf::FloatRect &bounds) const {
  return topShape.getGlobalBounds().findIntersection(bounds).has_value() ||
         botShape.getGlobalBounds().findIntersection(bounds).has_value();
}
