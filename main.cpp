#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Window.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

int main() {
  RenderWindow window(VideoMode({400, 600}), "Tappy-Bird!"); // set res
  window.setFramerateLimit(60);
  const auto onClose =
      [&window](
          const Event::Closed &) { // function expects argument of EVENT CLOSE
        window.close();
      };
  const auto onKeyPressed = [&window](const Event::KeyPressed &keyPressed) {
    if (keyPressed.scancode == Keyboard::Scancode::Escape)
      window.close();
  };

  float posX = 200.f;
  float posY = 400.f;
  RectangleShape shape(Vector2f(40.f, 40.f));
  shape.setFillColor(Color::Red);
  shape.setPosition(Vector2f(posX, posY));

  Clock clock;

  float gravity = 10.f;
  float velocityY = 1.f;
  while (window.isOpen()) {
    window.handleEvents(onClose, onKeyPressed);

    Time dt = clock.restart();
    float delta = dt.asSeconds();
    if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
      velocityY = -300.f;
    }
    velocityY = velocityY + gravity;
    posY = posY + (velocityY * delta);

    shape.setPosition(Vector2f(posX, posY));
    window.clear();
    window.draw(shape);
    window.display();
  }
}
