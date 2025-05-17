#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mouse Interaction");

    // Shape toggle flag (true = circle, false = triangle)
    bool isCircle = true;

    // Circle Shape
    sf::CircleShape circle(50); // Radius 50
    circle.setFillColor(sf::Color::Blue);
    circle.setPosition(350, 275);

    // Triangle Shape
    sf::CircleShape triangle(50, 3); // 3 sides = Triangle
    triangle.setFillColor(sf::Color::Green);
    triangle.setPosition(350, 275);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Move the current shape to the mouse position
                    if (isCircle) {
                        circle.setPosition(event.mouseButton.x - 50, event.mouseButton.y - 50);
                    } else {
                        triangle.setPosition(event.mouseButton.x - 50, event.mouseButton.y - 50);
                    }
                }

                if (event.mouseButton.button == sf::Mouse::Right) {
                    // Toggle between circle and triangle
                    isCircle = !isCircle;
                }
            }
        }

        window.clear();

        // Draw the correct shape based on the flag
        if (isCircle) {
            window.draw(circle);
        } else {
            window.draw(triangle);
        }

        window.display();
    }

    return 0;
}

