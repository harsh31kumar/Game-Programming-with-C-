#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>
#include <iostream>
#include <ctime>
#include "ball.h"
#include "bat.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();
    void spawnBall();
    void increaseDifficulty();
    void resetGame();
    
    sf::RenderWindow window;
    Bat bat;
    std::vector<Ball> balls;
    sf::Font font;
    sf::Text hudText;
    
    int score = 0;
    int lives = 3;
    float ballSpawnTimer = 0.f;
    const float ballSpawnInterval = 10.f; // Spawn new ball every 10 seconds
    const float initialBallSpeed = 400.f;
    float ballSpeedMultiplier = 1.f;
    
    const sf::Vector2f windowSize = {1000.f, 600.f};
    const sf::Vector2f paddleStartPos = {windowSize.x/2, windowSize.y - 30.f};
    const sf::Vector2f ballStartPos = {windowSize.x/2, windowSize.y/2};
};

Game::Game() : window(sf::VideoMode(windowSize.x, windowSize.y), 
               bat(paddleStartPos.x, paddleStartPos.y) {
    
    std::srand(std::time(0));
    window.setFramerateLimit(60);
    
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    
    hudText.setFont(font);
    hudText.setCharacterSize(24);
    hudText.setFillColor(sf::Color::White);
    hudText.setPosition(10.f, 10.f);
    
    spawnBall(); // Start with one ball
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left) bat.moveLeft();
            if (event.key.code == sf::Keyboard::Right) bat.moveRight();
            if (event.key.code == sf::Keyboard::R && lives <= 0) resetGame();
        }
        
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Left || 
                event.key.code == sf::Keyboard::Right) {
                bat.stop();
            }
        }
    }
}

void Game::update(float deltaTime) {
    bat.update(deltaTime);
    
    // Ball spawning logic
    ballSpawnTimer += deltaTime;
    if (ballSpawnTimer >= ballSpawnInterval) {
        spawnBall();
        ballSpawnTimer = 0.f;
    }
    
    // Game logic
    for (auto it = balls.begin(); it != balls.end(); ) {
        Ball& ball = *it;
        ball.update(deltaTime);
        
        // Wall collisions
        if (ball.getPosition().x <= 0 || ball.getPosition().x >= windowSize.x) {
            ball.bounceX();
        }
        if (ball.getPosition().y <= 0) {
            ball.bounceY();
        }
        
        // Paddle collision
        if (ball.getPosition().y +Bat 10 >= bat.getPosition().y - 10 &&
            ball.getPosition().x + 10 >= bat.getPosition().x - bat.getWidth()/2 &&
            ball.getPosition().x - 10 <= bat.getPosition().x + bat.getWidth()/2) {
            
            ball.bounceY();
            score++;
            
            // Increase difficulty every 5 points
            if (score % 5 == 0) {
                increaseDifficulty();
            }
        }
        
        // Ball out of bounds
        if (ball.getPosition().y > windowSize.y) {
            it = balls.erase(it);
            if (balls.empty()) {
                lives--;
                if (lives > 0) spawnBall();
            }
            continue;
        }
        ++it;
    }
    
    // Update HUD
    std::stringstream ss;
    ss << "Score: " << score << "\n"
       << "Lives: " << lives << "\n"
       << "Balls: " << balls.size() << "\n"
       << "Speed: " << initialBallSpeed * ballSpeedMultiplier;
    hudText.setString(ss.str());
}

void Game::render() {
    window.clear();
    
    window.draw(bat.getShape());
    for (const auto& ball : balls) {
        window.draw(ball.getShape());
    }
    
    window.draw(hudText);
    
    if (lives <= 0) {
        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("GAME OVER\nPress R to restart");
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(windowSize.x/2 - 150, windowSize.y/2 - 50);
        window.draw(gameOverText);
    }
    
    window.display();
}

void Game::spawnBall() {
    balls.emplace_back(ballStartPos.x, ballStartPos.y, initialBallSpeed * ballSpeedMultiplier);
}

void Game::increaseDifficulty() {
    // Increase speed by 20%
    ballSpeedMultiplier *= 1.2f;
    for (auto& ball : balls) {
        ball.setSpeed(initialBallSpeed * ballSpeedMultiplier);
    }
    
    // Shrink paddle every 15 points
    if (score % 15 == 0) {
        bat.shrink(15.f);
    }
}

void Game::resetGame() {
    score = 0;
    lives = 3;
    ballSpeedMultiplier = 1.f;
    balls.clear();
    bat.resetSize();
    spawnBall();
}

int main() {
    Game game;
    game.run();
    return 0;
}
