#include "Bird.h"
#include "Pipe.h"
#include "SFML/Window/Event.hpp"
#include <SFML/Graphics.hpp>

#include "SFML/Audio/Listener.hpp"

Pipe::Pipe(float x, float gapTop) {
  topShape.setSize(sf::Vector2f(width, gapTop));
  topShape.setPosition(sf::Vector2f(x, 0));
  botShape.setSize(sf::Vector2f(width, windowHeight - gapTop - gap));
  botShape.setPosition(sf::Vector2f(x, gapTop + gap));
  topShape.setFillColor(sf::Color::Green);
  botShape.setFillColor(sf::Color::Green);
}
void Pipe::update(float delta) {
  topShape.move(sf::Vector2f(-speed * delta, 0.f));
  botShape.move(sf::Vector2f(-speed * delta, 0.f));
}
void Pipe::draw(sf::RenderTarget &target) const {
  target.draw(topShape);
  target.draw(botShape);
}

bool Pipe::isOffScreen() const {
  if (topShape.getPosition().x < -60.f) {
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
  if (birdx > Pipe::topShape.getPosition().x && Pipe::scored == false) {
    Pipe::markScored();
    return true;
  }
  return false;
}

bool Pipe::collidesWith(const sf::FloatRect &bounds) const {
  return topShape.getGlobalBounds().findIntersection(bounds).has_value() ||
         botShape.getGlobalBounds().findIntersection(bounds).has_value();
}
