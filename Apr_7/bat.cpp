#include "bat.h"
#include <algorithm> // For std::max

bat::bat(float startX, float startY) : position(startX, startY) {
    shape.setSize({width, height});
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(width / 2, height / 2);
    shape.setPosition(position);
}

sf::RectangleShape bat::getShape() const { 
    return shape; 
}

sf::Vector2f bat::getPosition() const { 
    return position; 
}

float bat::getWidth() const { 
    return width; 
}

float bat::getHeight() const { 
    return height; 
}

void bat::moveLeft() { 
    movement = -speed; 
}

void bat::moveRight() { 
    movement = speed; 
}

void bat::stop() { 
    movement = 0.f; 
}

void bat::update(float deltaTime) {
    position.x += movement * deltaTime;
    shape.setPosition(position);

    // Keep the bat within the window bounds
    if (position.x - width / 2 < 0) {
        position.x = width / 2; // Prevent going off the left side
    }
    if (position.x + width / 2 > 1000.f) { // Assuming window width is 1000.f
        position.x = 1000.f - width / 2; // Prevent going off the right side
    }
    shape.setPosition(position);
}

void bat::shrink(float amount) {
    // Reduce the width but ensure it doesn’t go below a minimum value (e.g., 40.f)
    width = std::max(40.f, width - amount);
    shape.setSize({width, height});
    shape.setOrigin(width / 2, height / 2);
}

void bat::resetSize() {
    // Reset the paddle width to its initial value
    width = initialWidth;
    shape.setSize({width, height});
    shape.setOrigin(width / 2, height / 2);
}

void bat::setPosition(float x, float y) {
    position = {x, y};
    shape.setPosition(position);
}

