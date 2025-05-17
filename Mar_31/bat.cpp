#include "bat.h"
#include <SFML/Graphics.hpp>

Bat::Bat(float windowWidth, float windowHeight) {
    m_Position.x = windowWidth/2;
    m_Position.y = windowHeight - 30;
    
    m_Shape.setSize(sf::Vector2f(100.f, 15.f));
    m_Shape.setPosition(m_Position);
    m_Shape.setFillColor(sf::Color::White);
    m_Shape.setOrigin(50.f, 7.5f);
}

sf::FloatRect Bat::getPosition() {
    return m_Shape.getGlobalBounds();
}

sf::RectangleShape Bat::getShape() {
    return m_Shape;
}

void Bat::moveLeft() {
    m_MovingLeft = true;
}

void Bat::moveRight() {
    m_MovingRight = true;
}

void Bat::stopLeft() {
    m_MovingLeft = false;
}

void Bat::stopRight() {
    m_MovingRight = false;
}

void Bat::update(sf::Time dt) {
    if (m_MovingLeft) {
        m_Position.x -= m_Speed * dt.asSeconds();
    }
    if (m_MovingRight) {
        m_Position.x += m_Speed * dt.asSeconds();
    }
    
    // Keep the bat inside the window
    if (m_Position.x < 50.f) {
        m_Position.x = 50.f;
    }
    if (m_Position.x > 750.f) {  // WINDOW_WIDTH - 50
        m_Position.x = 750.f;
    }
    
    m_Shape.setPosition(m_Position);
}
