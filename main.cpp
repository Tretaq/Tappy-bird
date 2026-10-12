#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
int main() {
    RenderWindow window(VideoMode({500,300}), "Tappy-Bird!");//set res
    CircleShape shape(100.f);
    shape.setFillColor(Color::Red);
    while (window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
        }
        window.clear();
        window.draw(shape);
        window.display();
    }
// i dont know if the X works since linux dosnt know whats an X
}
