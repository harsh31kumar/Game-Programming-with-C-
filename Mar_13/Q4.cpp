#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

int main() {
    // Create window
    RenderWindow window(VideoMode(800, 600), "Image Animation");

    // Load texture
    Texture texture;
    if (!texture.loadFromFile("/home/student/2241011135_HARSH/Sem_6/C++/Mar_13/images.png")) {
        return -1; 
    }   

    Sprite sprite(texture);
    sprite.setPosition(100, 300);

    float speed = 5.0f; // Movement speed

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        Vector2f pos = sprite.getPosition();
        Vector2u textureSize = texture.getSize(); // Get sprite texture size
        Vector2u windowSize = window.getSize();   // Get window size

        if (Keyboard::isKeyPressed(Keyboard::Left) && pos.x > 0)
            sprite.move(-speed, 0);
        if (Keyboard::isKeyPressed(Keyboard::Right) && pos.x + textureSize.x < windowSize.x)
            sprite.move(speed, 0);
        if (Keyboard::isKeyPressed(Keyboard::Up) && pos.y > 0)
            sprite.move(0, -speed);
        if (Keyboard::isKeyPressed(Keyboard::Down) && pos.y + textureSize.y < windowSize.y)
            sprite.move(0, speed);

        // Render
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}

