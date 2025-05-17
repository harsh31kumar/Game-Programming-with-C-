#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball {
private:
    sf::Vector2f m_Position;
    sf::CircleShape m_Shape;
    float m_Speed = 1000.0f;
    float m_DirectionX = 0.2f;
    float m_DirectionY = -0.2f;

public:
    Ball(float startX, float startY);
    sf::FloatRect getPosition();
    sf::CircleShape getShape();
    void reboundSides();
    void reboundTop();
    void update(sf::Time dt);
    bool isOutOfBounds(float windowHeight);
};

#endif // BALL_H
