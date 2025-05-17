#include <SFML/Graphics.hpp>
#include <iostream>
#include "bat.h"
#include "ball.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Two-Player Pong");
    window.setFramerateLimit(60);

    // Create two bats
    Bat leftBat(50.f, WINDOW_HEIGHT/2.f);
    Bat rightBat(WINDOW_WIDTH - 50.f, WINDOW_HEIGHT/2.f);

    Ball ball(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f);

    // Scores
    int leftScore = 0;
    int rightScore = 0;

    // Font
    sf::Font font;
    if (!font.loadFromFile("/home/student/2241011135_HARSH/Sem_6/C++/Apr_3/font/arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    // Score text
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(WINDOW_WIDTH/2.f - 30.f, 10.f);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Player 1 controls (W/S)
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W) leftBat.moveUp();
                if (event.key.code == sf::Keyboard::S) leftBat.moveDown();
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::W) leftBat.stopUp();
                if (event.key.code == sf::Keyboard::S) leftBat.stopDown();
            }

            // Player 2 controls (Up/Down)
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) rightBat.moveUp();
                if (event.key.code == sf::Keyboard::Down) rightBat.moveDown();
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Up) rightBat.stopUp();
                if (event.key.code == sf::Keyboard::Down) rightBat.stopDown();
            }
        }

        // Update game objects
        leftBat.update(dt);
        rightBat.update(dt);
        ball.update(dt);

        // Ball collision with top and bottom
        if (ball.getPosition().top < 0) {
            ball.reboundTop();
        }
        if (ball.getPosition().top + ball.getPosition().height > WINDOW_HEIGHT) {
            ball.reboundTop();
        }

        // Ball collision with bats (fixed syntax)
        if (ball.getPosition().intersects(leftBat.getPosition())) {
            ball.reboundSides();
        }
        if (ball.getPosition().intersects(rightBat.getPosition())) {
            ball.reboundSides();
        }

        // Scoring
        if (ball.getPosition().left < 0) {
            rightScore++;
            ball = Ball(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f);
        }
        if (ball.getPosition().left + ball.getPosition().width > WINDOW_WIDTH) {
            leftScore++;
            ball = Ball(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f);
        }

        // Update score display
        scoreText.setString(std::to_string(leftScore) + " - " + std::to_string(rightScore));

        // Draw everything
        window.clear(sf::Color::Black);
        window.draw(leftBat.getShape());
        window.draw(rightBat.getShape());
        window.draw(ball.getShape());
        window.draw(scoreText);
        window.display();
    }

    return 0;
}
