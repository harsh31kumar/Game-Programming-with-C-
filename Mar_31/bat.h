#ifndef BAT_H
#define BAT_H

#include <SFML/Graphics.hpp>

class Bat {
private:
    sf::Vector2f m_Position;
    sf::RectangleShape m_Shape;
    float m_Speed = 500.0f;
    bool m_MovingLeft = false;
    bool m_MovingRight = false;

public:
    Bat(float windowWidth, float windowHeight);
    
    sf::FloatRect getPosition();
    sf::RectangleShape getShape();
    
    void moveLeft();
    void moveRight();
    void stopLeft();
    void stopRight();
    
    void update(sf::Time dt);
};

#endif // BAT_H
