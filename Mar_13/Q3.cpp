#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int main() {
    RenderWindow window(VideoMode(1920, 1080), "Smooth Movement with Collision");

    RectangleShape rectangle(Vector2f(100, 50));
    rectangle.setFillColor(Color::Red);
    rectangle.setPosition(350, 275);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }


        Vector2f pos = rectangle.getPosition();

        if (Keyboard::isKeyPressed(Keyboard::Left) && pos.x > 0)
            rectangle.move(-5.0f, 0);
        if (Keyboard::isKeyPressed(Keyboard::Right) && pos.x + rectangle.getSize().x < window.getSize().x)
            rectangle.move(5.0f, 0);
        if (Keyboard::isKeyPressed(Keyboard::Up) && pos.y > 0)
            rectangle.move(0, -5.0f);
        if (Keyboard::isKeyPressed(Keyboard::Down) && pos.y + rectangle.getSize().y < window.getSize().y)
            rectangle.move(0, 5.0f);

        cout << "Rectangle Position: (" << pos.x << ", " << pos.y << ")\n";

        window.clear();
        window.draw(rectangle);
        window.display();
    }
}
    return 0;
}

