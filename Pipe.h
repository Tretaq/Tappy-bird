#pragma once

#include "SFML/Graphics.hpp"
class Pipe {
private:
  static constexpr float width = 60.f;
  static constexpr float speed = 150.f;
  static constexpr float hitboxInset = 10.f;
  sf::RectangleShape topShape;
  sf::RectangleShape botShape;
  bool scored = false;


public:
  static constexpr float windowHeight = 600.f;
  static constexpr float gap = 150.f;
  void draw(sf::RenderTarget &target) const;
  void update(float delta);
  bool isOffScreen() const;
  bool collidesWith(const sf::FloatRect &bounds) const;
  bool isPassed(float birdx);
  void markScored();
  Pipe(float x, float gapTop, const sf::Texture& texture);
  sf::Sprite topSprite;
  sf::Sprite botSprite;
};
