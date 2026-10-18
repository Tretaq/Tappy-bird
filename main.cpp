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

// TO DO y is wrong and need to do smae indent for it
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
  sf::Texture birdTextur("assets/bird_frame_1.png");
  sf::Texture pipeTexture("assets/pipe_60x500.png");
  sf::Texture background_texture("assets/background_1600x600_scrolling.png");
  background_texture.setRepeated(true);
  background_texture.setSmooth(false);
  birdTextur.setSmooth(false);
  pipeTexture.setSmooth(false);
  sf::Sprite background(background_texture);


  sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}),
                          "Tappy-Bird!"); // set res
  window.setFramerateLimit(60);
  window.setKeyRepeatEnabled(false);
  const float spawnInterval = 2.f;
  int score = 0;
  Bird bird(birdTextur);
  sf::Clock clock;

  std::vector<Pipe> pipes;
  float bgOffset = 0.f;
  const float bgSpeed = 30.f;
  background.setTextureRect(sf::IntRect({0,0},{windowWidth,windowHeight}));
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
        pipes.push_back(Pipe(windowWidth, roll,pipeTexture));
        spawnTimer = spawnTimer - spawnInterval;
      }

      bird.update(delta);

      bgOffset += bgSpeed * delta;
      bgOffset = std::fmod(bgOffset, static_cast<float>(background_texture.getSize().x));

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
    background.setTextureRect((sf::IntRect({static_cast<int>(bgOffset),0},{windowWidth,windowHeight})));
    window.clear();
    window.draw(background);
    for (const Pipe &pipe : pipes) {
      pipe.draw(window);
    }
    if (state == State::GameOver) {
      sf::FloatRect textBounds = pressSpaceText.getLocalBounds();
      pressSpaceText.setOrigin({textBounds.position.x + textBounds.size.x / 2.0f, textBounds.position.y + textBounds.size.y / 2.0f});
      pressSpaceText.setPosition({window.getSize().x / 2.0f, window.getSize().y / 2.0f});
      window.draw(pressSpaceText);
    }
    bird.draw(window);
    window.draw(points);
    window.display();
  }
}
