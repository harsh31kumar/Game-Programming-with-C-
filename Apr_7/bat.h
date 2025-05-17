#pragma once
#include <SFML/Graphics.hpp>

class Bat {
public:
    Bat(float startX, float startY);
    
    sf::RectangleShape getShape() const;
    sf::Vector2f getPosition() const;
    float getWidth() const;
    float getHeight() const;
    
    void moveLeft();
    void moveRight();
    void stop();
    void update(float deltaTime);
    void shrink(float amount);
    void resetSize();

private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    float speed = 1000.f;
    float movement = 0.f;
    float width = 120.f;
    const float height = 20.f;
    const float initialWidth = 120.f;
};
