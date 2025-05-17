#pragma once
#include <SFML/Graphics.hpp>

class Ball {
public:
    Ball(float startX, float startY, float initialSpeed);
    
    sf::CircleShape getShape() const;
    sf::Vector2f getPosition() const;
    float getSpeed() const;
    void setSpeed(float newSpeed);
    
    void bounceX();
    void bounceY();
    void reset();
    void update(float deltaTime);

private:
    sf::CircleShape shape;
    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;
    const float radius = 10.f;
    const sf::Vector2f startPosition;
};
