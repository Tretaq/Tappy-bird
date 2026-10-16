#include "Bird.h"
#include "Pipe.h"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Window.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <X11/Xproto.h>


enum class State { Waiting, Playing, GameOver };
int main() {
  const int windowWidth = 800;
  const int windowHeight = Pipe::windowHeight;
  const int gapMargin = 100;
  State state = State::Waiting;
  sf::Font font("static/Inter_24pt-Black.ttf");
  sf::Text points(font);
  points.setString("0");
  points.setCharacterSize(24);
  points.setPosition(sf::Vector2f(400.f,50.f));
  points.setFillColor(sf::Color::White);
  sf::Text pressSpaceText(font);
  pressSpaceText.setCharacterSize(24);
  pressSpaceText.setPosition(sf::Vector2f(270.f,450.f));
  pressSpaceText.setFillColor(sf::Color::White);
  pressSpaceText.setString("Press space to restart!");

  sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}),
                          "Tappy-Bird!"); // set res
  window.setFramerateLimit(60);
  window.setKeyRepeatEnabled(false);
  const float spawnInterval = 2.f;
  int score = 0;
  Bird bird;
  sf::Clock clock;

  std::vector<Pipe> pipes;
  float spawnTimer = 0.f;
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dice(gapMargin,
                                          windowHeight - gapMargin - Pipe::gap);

  const auto onClose =
      [&window](
          const sf::Event::Closed &) { // function expects argument of EVENT CLOSE
        window.close();
      };
  const auto onKeyPressed = [&window,
                             &bird,&state,&pipes,&score,&spawnTimer](const sf::Event::KeyPressed &keyPressed) {
    if (keyPressed.scancode == sf::Keyboard::Scancode::Escape)
      window.close();
    if (keyPressed.scancode == sf::Keyboard::Scancode::Space) {
      if (state == State::Waiting) {
        state = State::Playing;
        bird.jump();
      }else if (state == State::GameOver) {
        pipes.clear();
        score = 0;
        spawnTimer = 0.f;
        bird.reset();
        state = State::Waiting;
      }else {
        bird.jump();
      }
    }
  };


  while (window.isOpen()) {
    window.handleEvents(onClose, onKeyPressed);

    sf::Time dt = clock.restart();
    float delta = dt.asSeconds();
    if (state == State::Playing) {
      spawnTimer = spawnTimer + delta;
      if (spawnTimer >= spawnInterval) { // roll mechanic
        int roll = dice(rng);
        pipes.push_back(Pipe(windowWidth, roll));
        spawnTimer = spawnTimer - spawnInterval;
      }

      bird.update(delta);

      for (Pipe &pipe : pipes) {
        pipe.update(delta);
        if (pipe.isPassed(bird.getBounds().position.x)) {
          score++;
        }
      }

      erase_if(pipes, [](const Pipe &p) { return p.isOffScreen(); });

      for (const Pipe &pipe : pipes) {
        if (pipe.collidesWith(bird.getBounds())) {
          state = State::GameOver;
        }
      }
      if (bird.isOutOfBounds(static_cast<float>(windowHeight))) {
        state = State::GameOver;
      }
    }

    points.setString(std::to_string(score));
    window.clear();

    for (const Pipe &pipe : pipes) {
      pipe.draw(window);
    }
    if (state == State::GameOver) {
      window.draw(pressSpaceText);
    }
    bird.draw(window);
    window.draw(points);
    window.display();
  }
}
