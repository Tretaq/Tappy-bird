#include <fstream>

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
#include <sys/stat.h>
#include <X11/Xproto.h>

enum class State { Waiting, Playing, GameOver };

int loadNumber(const std::string& path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    return 0;
  }
  int value = 0;
  file >> value;
  if (file.fail()) {
    return 0;
  }
  return value;
}
void saveNumber(const std::string& path, int value) {
  std::ofstream file(path);
  if (!file.is_open()) {
    return;
  }
  file << value;
}
int main() {
  const int windowWidth = 800;
  const int windowHeight = Pipe::windowHeight;
  const int gapMargin = 100;
  int best = loadNumber("highscore.txt");
  std::vector<sf::Texture> bird_vector;
  bird_vector.reserve(3);
  for (int i = 1; i <= 3  ; ++i) {
    sf::Texture tex;
    if (!tex.loadFromFile("assets/bird_frame_" + std::to_string(i) + ".png")) {
      return 1;
    }
    tex.setSmooth(false);
    bird_vector.push_back((std::move(tex)));
  }
  State state = State::Waiting;
  sf::Font font("static/PixelifySans-Medium.ttf");
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
  sf::Text highest_points(font);
  highest_points.setString("Your highest score is "+ std::to_string(best));
  highest_points.setCharacterSize(24);
  highest_points.setPosition(sf::Vector2f(270.f,450.f));
  highest_points.setFillColor(sf::Color::White);

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
  Bird bird(bird_vector);
  sf::Clock clock;

  int birdTextureCounter = 0;

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
    State previous = state;
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
    if (state != State::GameOver) {
      bird.animate(delta);
    }

    points.setString(std::to_string(score));
    background.setTextureRect((sf::IntRect({static_cast<int>(bgOffset),0},{windowWidth,windowHeight})));
    if (previous == State::Playing && state == State::GameOver) {
      if (score > best) {
        best = score;
        saveNumber("highscore.txt",best);
      }
    }
    window.clear();
    window.draw(background);
    for (const Pipe &pipe : pipes) {
      pipe.draw(window);
    }
    if (state == State::Waiting) {
      highest_points.setPosition({window.getSize().x / 2.0f, window.getSize().y / 2.0f});
      window.draw(highest_points);
    }
    if (state == State::GameOver) {
      best = loadNumber("highscore.txt");
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
