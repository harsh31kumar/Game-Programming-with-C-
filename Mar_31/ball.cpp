#include "ball.h"
#include <SFML/Graphics.hpp>

Ball::Ball(float startX, float startY) {
    m_Position.x = startX;
    m_Position.y = startY;
    
    m_Shape.setRadius(10.f);
    m_Shape.setPosition(m_Position);
    m_Shape.setFillColor(sf::Color::White);
    m_Shape.setOrigin(10.f, 10.f);
}

sf::FloatRect Ball::getPosition() {
    return m_Shape.getGlobalBounds();
}

sf::CircleShape Ball::getShape() {
    return m_Shape;
}

void Ball::reboundSides() {
    m_DirectionX = -m_DirectionX;
}

void Ball::reboundTop() {
    m_DirectionY = -m_DirectionY;
}

void Ball::update(sf::Time dt) {
    m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();
    m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
    m_Shape.setPosition(m_Position);
}

bool Ball::isOutOfBounds(float windowHeight) {
    return m_Position.y > windowHeight;
}
