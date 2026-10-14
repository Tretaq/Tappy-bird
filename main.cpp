#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Window.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bird.h"
#include "Pipe.h"
using namespace sf;
using namespace std;



int main() {
  RenderWindow window(VideoMode({400, 600}), "Tappy-Bird!"); // set res
  window.setFramerateLimit(60);
  window.setKeyRepeatEnabled(false);
  float velocityY = 0.f;
  Bird bird;
  Pipe pipe(200,200);
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


  Clock clock;


  while (window.isOpen()) {
    window.handleEvents(onClose, onKeyPressed);

    Time dt = clock.restart();
    float delta = dt.asSeconds();

    bird.update(delta);


    window.clear();
    pipe.draw(window);
    bird.draw(window);
    window.display();
    cout << window.getSize().x << " " << window.getSize().y << "\n";
  }
}
