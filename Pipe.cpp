#include "Pipe.h"
#include "SFML/Window/Event.hpp"
#include <SFML/Graphics.hpp>


Pipe::Pipe(float x, float gapTop) {
    topShape.setSize(sf::Vector2f(width,gapTop));
    topShape.setPosition(sf::Vector2f(x,0));
    botShape.setSize(sf::Vector2f(width,windowHeight-gapTop-gap));
    botShape.setPosition(sf::Vector2f(x,gapTop+gap));
    topShape.setFillColor(sf::Color::Green);
    botShape.setFillColor(sf::Color::Green);
}

void Pipe::draw(sf::RenderTarget &target) const {
    target.draw(topShape);
    target.draw(botShape);
}
