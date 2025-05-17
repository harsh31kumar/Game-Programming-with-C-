#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mouse Interaction");

    sf::Texture texture;
    if (!texture.loadFromFile("/home/student/2241011135_HARSH/Sem_6/C++/Mar_13/images.png")) {  
        std::cerr << "Error: Could not load image!" << std::endl;
        return -1; 
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(200, 150);  

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sprite.setPosition(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }

        window.clear();
        window.draw(sprite);    
        window.display();
    }

    return 0;
}

