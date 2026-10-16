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
using namespace sf;
using namespace std;

int main() {
  const int windowWidth = 800;
  const int windowHeight = Pipe::windowHeight;
  const int gapMargin = 100;
  bool gameOver = false;
  Font font("static/Inter_24pt-Black.ttf");
  Text text(font);
  text.setString("0");
  text.setCharacterSize(24);
  text.setFillColor(Color::White);

  RenderWindow window(VideoMode({windowWidth, windowHeight}),
                      "Tappy-Bird!"); // set res
  window.setFramerateLimit(60);
  window.setKeyRepeatEnabled(false);
  const float spawnInterval = 2.f;
  int score = 0;
  Bird bird;
  Clock clock;

  vector<Pipe> pipes;

  const auto onClose =
      [&window](
          const Event::Closed &) { // function expects argument of EVENT CLOSE
        window.close();
      };
  const auto onKeyPressed = [&window,
                             &bird](const Event::KeyPressed &keyPressed) {
    if (keyPressed.scancode == Keyboard::Scancode::Escape)
      window.close();
    if (keyPressed.scancode == Keyboard::Scancode::Space) {
      bird.jump();
    }
  };

  float spawnTimer = 0.f;
  mt19937 rng(random_device{}());
  uniform_int_distribution<int> dice(gapMargin,
                                     windowHeight - gapMargin - Pipe::gap);

  while (window.isOpen()) {
    window.handleEvents(onClose, onKeyPressed);

    Time dt = clock.restart();
    float delta = dt.asSeconds();
    if (!gameOver) {
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
      cout << score << "\n";
      erase_if(pipes, [](const Pipe &p) { return p.isOffScreen(); });

      for (const Pipe &pipe : pipes) {
        if (pipe.collidesWith(bird.getBounds())) {
          gameOver = true;
        }
      }
      if (bird.isOutOfBounds(static_cast<float>(windowHeight))) {
        gameOver = true;
      }
    }
    text.setString(to_string(score));
    window.clear();
    for (const Pipe &pipe : pipes) {
      pipe.draw(window);
    }
    bird.draw(window);
    window.draw(text);
    window.display();
  }
}
