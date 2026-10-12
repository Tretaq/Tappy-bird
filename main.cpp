#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

int main() {
  RenderWindow window(VideoMode({400, 600}), "Tappy-Bird!"); // set res
  window.setFramerateLimit(60);
  RectangleShape shape(Vector2f(200.f,111.f));
  shape.setFillColor(Color::Red);
  shape.setPosition(Vector2f(100.f,200.f));
  const auto onClose = [&window] (const Event::Closed&) {// function expects argument of EVENT CLOSE
    window.close();
  };
  const auto onKeyPressed = [&window](const Event::KeyPressed& keyPressed) {
    if (keyPressed.scancode == Keyboard::Scancode::Escape)
      window.close();
  };

  while (window.isOpen()) {
    window.handleEvents(onClose,onKeyPressed);

    window.clear();
    window.draw(shape);
    window.display();
  }
  // i dont know if the X works since linux dosnt know whats an X
}
