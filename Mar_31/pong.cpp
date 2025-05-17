#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "bat.h"
#include "ball.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int STARTING_LIVES = 3;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Single Paddle Pong");
    window.setFramerateLimit(60);

    Bat bat(WINDOW_WIDTH, WINDOW_HEIGHT);
    Ball ball(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

    int score = 0;
    int lives = STARTING_LIVES;
    bool gameOver = false;

    sf::Font font;
    if (!font.loadFromFile("/home/student/2241011135_HARSH/Sem_6/C++/Mar_31/font/arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    sf::Text hud;
    hud.setFont(font);
    hud.setCharacterSize(30);
    hud.setFillColor(sf::Color::White);
    hud.setPosition(20.f, 20.f);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left)
                    bat.moveLeft();
                if (event.key.code == sf::Keyboard::Right)
                    bat.moveRight();
                if (event.key.code == sf::Keyboard::R && gameOver) {
                    gameOver = false;
                    score = 0;
                    lives = STARTING_LIVES;
                    ball = Ball(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Left)
                    bat.stopLeft();
                if (event.key.code == sf::Keyboard::Right)
                    bat.stopRight();
            }
        }

        if (!gameOver) {
            bat.update(dt);
            ball.update(dt);

            // Ball collision with sides
            if (ball.getPosition().left < 0 || 
                ball.getPosition().left + ball.getPosition().width > WINDOW_WIDTH) {
                ball.reboundSides();
            }

            // Ball collision with top
            if (ball.getPosition().top < 0) {
                ball.reboundTop();
            }

            // Ball collision with bat
            if (ball.getPosition().intersects(bat.getPosition())) {
                ball.reboundTop();
                score++;
            }

            // Check if ball missed the bat
            if (ball.isOutOfBounds(WINDOW_HEIGHT)) {
                lives--;
                if (lives <= 0) {
                    gameOver = true;
                } else {
                    // Reset ball position but keep playing
                    ball = Ball(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
                }
            }
        }

        window.clear(sf::Color::Black);

        // Update HUD text
        std::stringstream ss;
        if (gameOver) {
            ss << "Game Over!\n\nFinal Score: " << score << "\n\nLives: " << lives << "\n\n\n\n\n\n\n\nPress R to restart";
        } else {
            ss << "Score: " << score << "                                                               Lives: " << lives;
        }
        hud.setString(ss.str());

        window.draw(bat.getShape());
        window.draw(ball.getShape());
        window.draw(hud);

        window.display();
    }

    return 0;
}
