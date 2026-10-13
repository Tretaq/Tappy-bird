#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Window.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;
class Bird {
  private:


    static constexpr float gravity = 900.f;
    static constexpr float jumpStrength = -350.f;
    float velocityY = 0.f;
    RectangleShape shape;
  public:
  void update( float delta) {
    velocityY = velocityY + gravity * delta;
    shape.move(Vector2f(0.f,velocityY * delta));
  }
  void jump() {
    velocityY = -350.f;
  }
  void draw(RenderTarget& target) {
    target.draw(shape);
  }
  FloatRect getBounds() {
    shape.getGlobalBounds();
  }
  Bird() {
    shape.setSize(Vector2f(40.f,40.f));
    shape.setFillColor(Color::Red);
    shape.setPosition(Vector2f(200.f,300.f));
  }

};
int main() {
  RenderWindow window(VideoMode({400, 600}), "Tappy-Bird!"); // set res
  window.setFramerateLimit(60);
  window.setKeyRepeatEnabled(false);
  float velocityY = 0.f;
  const auto onClose =
      [&window](
          const Event::Closed &) { // function expects argument of EVENT CLOSE
        window.close();
      };
  const auto onKeyPressed = [&window, &velocityY](const Event::KeyPressed &keyPressed) {
    if (keyPressed.scancode == Keyboard::Scancode::Escape)
      window.close();
    if (keyPressed.scancode == Keyboard::Scancode::Space) {
      velocityY = -350.f;
    }
  };

  float posX = 200.f;
  float posY = 400.f;

  RectangleShape shape(Vector2f(40.f, 40.f));
  shape.setFillColor(Color::Red);
  shape.setPosition(Vector2f(posX, posY));

  Clock clock;


  while (window.isOpen()) {
    window.handleEvents(onClose, onKeyPressed);

    Time dt = clock.restart();
    float delta = dt.asSeconds();

    velocityY = velocityY + (gravity * delta);
    posY = posY + (velocityY * delta);

    shape.setPosition(Vector2f(posX, posY));
    window.clear();
    window.draw(shape);
    window.display();
  }
}
