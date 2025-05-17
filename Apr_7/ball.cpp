#include "ball.h"
#include <cmath>
#include <cstdlib>

Ball::Ball(float startX, float startY, float initialSpeed) : 
    position(startX, startY), speed(initialSpeed), startPosition(startX, startY) {
    
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(radius, radius);
    
    // Random initial direction
    float angle = (std::rand() % 90 + 45) * 3.14159f / 180.f;
    direction.x = std::cos(angle) * (std::rand() % 2 ? 1 : -1);
    direction.y = std::sin(angle) * -1;
}

sf::CircleShape Ball::getShape() const { return shape; }
sf::Vector2f Ball::getPosition() const { return position; }
float Ball::getSpeed() const { return speed; }
void Ball::setSpeed(float newSpeed) { speed = newSpeed; }

void Ball::bounceX() { direction.x = -direction.x; }
void Ball::bounceY() { direction.y = -direction.y; }

void Ball::reset() {
    position = startPosition;
    // New random direction
    float angle = (std::rand() % 90 + 45) * 3.14159f / 180.f;
    direction.x = std::cos(angle) * (std::rand() % 2 ? 1 : -1);
    direction.y = std::sin(angle) * -1;
}

void Ball::update(float deltaTime) {
    position += direction * speed * deltaTime;
    shape.setPosition(position);
}
