#include "bat.h"
#include <SFML/Graphics.hpp>

Bat::Bat(float x, float y) {
    m_Position.x = x;
    m_Position.y = y;
    
    m_Shape.setSize(sf::Vector2f(15.f, 100.f)); // Vertical paddle
    m_Shape.setPosition(m_Position);
    m_Shape.setFillColor(sf::Color::White);
    m_Shape.setOrigin(7.5f, 50.f);
}

sf::FloatRect Bat::getPosition() {
    return m_Shape.getGlobalBounds();
}

sf::RectangleShape Bat::getShape() {
    return m_Shape;
}

void Bat::moveUp() {
    m_MovingUp = true;
}

void Bat::moveDown() {
    m_MovingDown = true;
}

void Bat::stopUp() {
    m_MovingUp = false;
}

void Bat::stopDown() {
    m_MovingDown = false;
}

void Bat::update(sf::Time dt) {
    if (m_MovingUp) {
        m_Position.y -= m_Speed * dt.asSeconds();
    }
    if (m_MovingDown) {
        m_Position.y += m_Speed * dt.asSeconds();
    }
    
    // Keep paddle in window
    if (m_Position.y < 50.f) {
        m_Position.y = 50.f;
    }
    if (m_Position.y > 550.f) {
        m_Position.y = 550.f;
    }
    
    m_Shape.setPosition(m_Position);
}
