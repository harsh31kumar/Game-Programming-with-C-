#include <SFML/Graphics.hpp>

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Image Display");
    sf::Texture texture;

    if (!texture.loadFromFile("/home/student/Desktop/imag.jpeg")) { 
        return -1; 

    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(200, 150);  
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(sprite);
        window.display();

    }
    return 0;
}
