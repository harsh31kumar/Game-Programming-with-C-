#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main() {
    RenderWindow window(VideoMode(800, 600), "Mouse Interaction");

    RectangleShape rectangle(Vector2f(100, 50));
    rectangle.setFillColor(Color::Red);
    rectangle.setPosition(350, 275);

    const float moveSpeed = 1.5f; // Slower movement speed

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        // Get current position
        Vector2f pos = rectangle.getPosition();

        // Move while keeping within bounds
        if (Keyboard::isKeyPressed(Keyboard::Left) && pos.x > 0)
            rectangle.move(-moveSpeed, 0);
        if (Keyboard::isKeyPressed(Keyboard::Right) && pos.x + rectangle.getSize().x < window.getSize().x)
            rectangle.move(moveSpeed, 0);
        if (Keyboard::isKeyPressed(Keyboard::Up) && pos.y > 0)
            rectangle.move(0, -moveSpeed);
        if (Keyboard::isKeyPressed(Keyboard::Down) && pos.y + rectangle.getSize().y < window.getSize().y)
            rectangle.move(0, moveSpeed);

        // Print position only when it changes
        static Vector2f lastPos = rectangle.getPosition();
        Vector2f currentPos = rectangle.getPosition();
        if (currentPos != lastPos) {
            cout << "Rectangle Position: (" << currentPos.x << ", " << currentPos.y << ")\n";
            lastPos = currentPos;
        }

        window.clear();
        window.draw(rectangle);
        window.display();
    }

    return 0;
}

