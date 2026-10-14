#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Window.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>
#include "Bird.h"
#include "Pipe.h"
using namespace sf;
using namespace std;




int main() {
  const int windowWidth = 800;
  const int windowHeight =  Pipe::windowHeight;
  const int gapMargin = 100;

  RenderWindow window(VideoMode({windowWidth, windowHeight}), "Tappy-Bird!"); // set res
  window.setFramerateLimit(60);
  window.setKeyRepeatEnabled(false);
   const float spawninterval = 2.f;
  Bird bird;
  Clock clock;

  vector<Pipe> pipes;





  const auto onClose =
      [&window](
          const Event::Closed &) { // function expects argument of EVENT CLOSE
        window.close();
      };
  const auto onKeyPressed = [&window, &bird](const Event::KeyPressed &keyPressed) {
    if (keyPressed.scancode == Keyboard::Scancode::Escape)
      window.close();
    if (keyPressed.scancode == Keyboard::Scancode::Space) {
      bird.jump();
    }
  };


  float spawnTimer = 0.f;
  mt19937 rng(random_device{}());
  uniform_int_distribution<int> dice(gapMargin , windowHeight - gapMargin - Pipe::gap);

  while (window.isOpen()) {
    window.handleEvents(onClose, onKeyPressed);

    Time dt = clock.restart();
    float delta = dt.asSeconds();

    spawnTimer = spawnTimer + delta;
    if (spawnTimer >= spawninterval) {  
      int roll = dice(rng);
      pipes.push_back(Pipe(windowWidth,roll));
      spawnTimer = spawnTimer - spawninterval;
    }


    bird.update(delta);

    for (Pipe &pipe : pipes) {
      pipe.update(delta);
    }
    erase_if(pipes, [](const Pipe &p) {
      return p.isOffScreen();
    });
    window.clear();

    for (const Pipe &pipe : pipes) {
      pipe.draw(window);
    }



    bird.draw(window);
    window.display();
  }
}
