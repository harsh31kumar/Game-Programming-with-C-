#ifndef BAT_H
#define BAT_H

#include <SFML/Graphics.hpp>

class Bat {
private:
    sf::Vector2f m_Position;
    sf::RectangleShape m_Shape;
    float m_Speed = 500.0f;
    bool m_MovingUp = false;
    bool m_MovingDown = false;

public:
    Bat(float x, float y);
    
    sf::FloatRect getPosition();
    sf::RectangleShape getShape();
    
    void moveUp();
    void moveDown();
    void stopUp();
    void stopDown();
    
    void update(sf::Time dt);
};

#endif // BAT_H
