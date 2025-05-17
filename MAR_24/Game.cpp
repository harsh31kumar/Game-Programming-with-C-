#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <unistd.h>
#include <vector>

using namespace sf;

void updateBranches(int seed);

const int NUM_BRANCHES = 6;
const int NUM_RAINDROPS = 150;
Sprite branches[NUM_BRANCHES];
Sprite raindrops[NUM_RAINDROPS];
bool isRaining = false;

enum class side {
    LEFT,
    RIGHT,
    NONE
};
side branchPositions[NUM_BRANCHES];

int main() {
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber!!", Style::Fullscreen);
    View view(FloatRect(0, 0, 1920, 1080));
    window.setView(view);

    // Load textures
    Texture textureBackground;
    textureBackground.loadFromFile("/home/student/2241011135_HARSH/Sem_6/C++/MAR_24/graphics/background.png");
    Texture textureTree;
    textureTree.loadFromFile("/home/student/2241011135_HARSH/Sem_6/C++/MAR_24/graphics/tree.png");
    Texture textureBee;
    textureBee.loadFromFile("/home/student/2241011135_HARSH/Sem_6/C++/MAR_24/graphics/bee.png");
    Texture textureCloud;
    textureCloud.loadFromFile("/home/student/2241011135_HARSH/Sem_6/C++/MAR_24/graphics/cloud.png");
    Texture texturePlayer;
    texturePlayer.loadFromFile("/home/student/2241011135_HARSH/Sem_6/C++/MAR_24/graphics/player.png");
    Texture textureAxe;
    textureAxe.loadFromFile("/home/student/2241011135_HARSH/Sem_6/C++/MAR_24/graphics/axe.png");
    Texture textureLog;
    textureLog.loadFromFile("/home/student/2241011135_HARSH/Sem_6/C++/MAR_24/graphics/log.png");
    Texture textureRIP;
    textureRIP.loadFromFile("/home/student/2241011135_HARSH/Sem_6/C++/MAR_24/graphics/rip.png");
    Texture textureFire;
    textureFire.loadFromFile("/home/student/2241011135_HARSH/Sem_6/C++/MAR_24/graphics/fire.png");
    Texture textureBranch;
    textureBranch.loadFromFile("/home/student/2241011135_HARSH/Sem_6/C++/MAR_24/graphics/branch.png");
    Texture textureRaindrop;
    textureRaindrop.loadFromFile("/home/student/2241011135_HARSH/Sem_6/C++/MAR_24/graphics/raindrop.png");

    // Initialize sprites
    Sprite spriteBackground(textureBackground);
    Sprite spriteTree(textureTree);
    spriteTree.setPosition(810, 0);
    
    Sprite spriteBee(textureBee);
    spriteBee.setPosition(0, 800);
    float beeSpeed = 0.0f;
    bool beeActive = false;

    Sprite spriteCloud1(textureCloud);
    Sprite spriteCloud2(textureCloud);
    Sprite spriteCloud3(textureCloud);
    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 250);
    spriteCloud3.setPosition(0, 350);
    spriteCloud3.setScale(0.5f, 0.5f);
    float cloudSpeed1 = 100.0f;
    float cloudSpeed2 = -75.0f;
    float cloudSpeed3 = 120.0f;

    Sprite spritePlayer(texturePlayer);
    spritePlayer.setPosition(580, 720);
    side playerSide = side::LEFT;

    Sprite spriteAxe(textureAxe);
    spriteAxe.setPosition(580, 720);
    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    Sprite spriteLog(textureLog);
    spriteLog.setPosition(810, 720);
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;
    bool acceptInput = false;

    Sprite spriteRIP(textureRIP);
    spriteRIP.setPosition(600, 860);
    Sprite spriteFire(textureFire);
    spriteFire.setPosition(600, 860);

    // Initialize raindrops - start them all off-screen
    for (int i = 0; i < NUM_RAINDROPS; i++) {
        raindrops[i].setTexture(textureRaindrop);
        raindrops[i].setPosition(-1000, -1000);
        raindrops[i].setScale(0.3f, 0.3f);
    }

    // Game timing
    Clock clock;
    Time dt;
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    bool paused = true;
    int score = 0;
    Text messageText;
    Text scoreText;

    Font font;
    font.loadFromFile("/home/student/2241011135_HARSH/Sem_6/C++/MAR_24/font/KOMIKAP_.ttf");
    messageText.setFont(font);
    scoreText.setFont(font);
    messageText.setString("Press Enter to start!");
    scoreText.setString("Score = 0");
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);
    messageText.setFillColor(Color::Green);
    scoreText.setFillColor(Color::Red);

    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
    scoreText.setPosition(20, 20);

    // Initialize branches
    for (int i = 0; i < NUM_BRANCHES; i++) {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);
        branches[i].setOrigin(220, 20);
    }

    // Load sounds
    SoundBuffer chopBuffer, deathBuffer, ootBuffer;
    chopBuffer.loadFromFile("/home/student/2241011135_HARSH/Sem_6/C++/MAR_24/sound/chop.wav");
    deathBuffer.loadFromFile("/home/student/2241011135_HARSH/Sem_6/C++/MAR_24/sound/death.wav");
    ootBuffer.loadFromFile("/home/student/2241011135_HARSH/Sem_6/C++/MAR_24/sound/out of time.wav");
    Sound chop, death, outOfTime;
    chop.setBuffer(chopBuffer);
    death.setBuffer(deathBuffer);
    outOfTime.setBuffer(ootBuffer);

    // Initialize branches
    updateBranches(1);
    updateBranches(2);
    updateBranches(3);
    updateBranches(4);
    updateBranches(5);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased && !paused) {
                acceptInput = true;
                spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
            }
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = false;
            score = 0;
            timeRemaining = 6;
            isRaining = false;
            spriteCloud1.setColor(Color::White);
            spriteCloud2.setColor(Color::White);
            spriteCloud3.setColor(Color::White);
            
            for (int i = 1; i < NUM_BRANCHES; i++) {
                branchPositions[i] = side::NONE;
            }
            
            spriteRIP.setPosition(675, 2000);
            spriteFire.setPosition(675, 2000);
            spritePlayer.setPosition(580, 720);
            acceptInput = true;
        }

        if (acceptInput) {
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                playerSide = side::RIGHT;
                score++;
                timeRemaining += (2.0f / score) + 0.15;
                spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
                spritePlayer.setPosition(1200, 720);
                updateBranches(score);
                spriteLog.setPosition(810, 720);
                logSpeedX = -5000.0f;
                logActive = true;
                acceptInput = false;
                chop.play();
            }
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                playerSide = side::LEFT;
                score++;
                timeRemaining += (2.0f / score) + 0.15f;
                spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
                spritePlayer.setPosition(580, 720);
                updateBranches(score);
                spriteLog.setPosition(810, 720);
                logSpeedX = 5000.0f;
                logActive = true;
                acceptInput = false;
                chop.play();
            }
        }

        if (!paused) {
            dt = clock.restart();
            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
            
            if (timeRemaining <= 0.0f) {
                paused = true;
                messageText.setString("Out of Time!");
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
                outOfTime.play();
            }
        }

        // Update bee
        if (!beeActive) {
            srand((int)time(0));
            beeSpeed = (rand() % 200) + 200;
            float height = (rand() % 500) + 500;
            spriteBee.setPosition(2000, height);
            beeActive = true;
        } else {
            spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);
            if (spriteBee.getPosition().x < -100) {
                beeActive = false;
            }
        }

        // Update clouds
        spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloudSpeed1 * dt.asSeconds()), spriteCloud1.getPosition().y);
        spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloudSpeed2 * dt.asSeconds()), spriteCloud2.getPosition().y);
        spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloudSpeed3 * dt.asSeconds()), spriteCloud3.getPosition().y);

        if (spriteCloud1.getPosition().x > 1920) spriteCloud1.setPosition(-200, (rand() % 150));
        if (spriteCloud2.getPosition().x > 1920) spriteCloud2.setPosition(-200, (rand() % 150) + 150);
        if (spriteCloud3.getPosition().x > 1920) spriteCloud3.setPosition(-200, (rand() % 150) + 300);

        // Update score display
        std::stringstream ss;
        ss << "Score = " << score;
        scoreText.setString(ss.str());

        // Update branches
        for (int i = 0; i < NUM_BRANCHES; i++) {
            float height = i * 150;
            if (branchPositions[i] == side::LEFT) {
                branches[i].setPosition(610, height);
                branches[i].setRotation(180);
            } else if (branchPositions[i] == side::RIGHT) {
                branches[i].setPosition(1330, height);
                branches[i].setRotation(0);
            } else {
                branches[i].setPosition(3000, height);
            }
        }

        // Update log
        if (logActive) {
            spriteLog.setPosition(
                spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
                spriteLog.getPosition().y + (logSpeedY * dt.asSeconds())
            );
            if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000) {
                logActive = false;
                spriteLog.setPosition(810, 720);
            }
        }

        // Check for death
        if (branchPositions[5] == playerSide) {
            paused = true;
            acceptInput = false;
            spriteRIP.setPosition(spritePlayer.getPosition());
            spriteFire.setPosition(spritePlayer.getPosition());
            spritePlayer.setPosition(2000, 660);
            
            // Activate rain
            isRaining = true;
            spriteCloud1.setColor(Color(100, 100, 100, 200));
            spriteCloud2.setColor(Color(100, 100, 100, 200));
            spriteCloud3.setColor(Color(100, 100, 100, 200));
            cloudSpeed1 = 50.0f;
            cloudSpeed2 = -40.0f;
            cloudSpeed3 = 60.0f;
            
            messageText.setString("SQUISHED!!");
            FloatRect textRect = messageText.getLocalBounds();
            messageText.setOrigin(
                textRect.left + textRect.width / 2.0f,
                textRect.top + textRect.height / 2.0f
            );
            messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
            
            death.play();
        }

        // Update rain - only from visible clouds and not in front of trees
        if (isRaining) {
            // Check each cloud's position to see if it's on screen
            bool cloud1Visible = (spriteCloud1.getPosition().x > -300 && spriteCloud1.getPosition().x < 1920);
            bool cloud2Visible = (spriteCloud2.getPosition().x > -300 && spriteCloud2.getPosition().x < 1920);
            bool cloud3Visible = (spriteCloud3.getPosition().x > -300 && spriteCloud3.getPosition().x < 1920);

            for (int i = 0; i < NUM_RAINDROPS; i++) {
                // Only move raindrops that are active (positioned under clouds)
                if (raindrops[i].getPosition().y > 0) {
                    raindrops[i].move(0, 800 * dt.asSeconds());
                    if (raindrops[i].getPosition().y > 1080) {
                        raindrops[i].setPosition(-1000, -1000); // Move off-screen when they fall below
                    }
                }
                // Activate new raindrops under visible clouds
                else if ((rand() % 100) < 5) { // 5% chance each frame to spawn a new raindrop
                    // Choose a random visible cloud to spawn under
                    std::vector<Sprite*> visibleClouds;
                    if (cloud1Visible) visibleClouds.push_back(&spriteCloud1);
                    if (cloud2Visible) visibleClouds.push_back(&spriteCloud2);
                    if (cloud3Visible) visibleClouds.push_back(&spriteCloud3);

                    if (!visibleClouds.empty()) {
                        Sprite* chosenCloud = visibleClouds[rand() % visibleClouds.size()];
                        float cloudLeft = chosenCloud->getPosition().x;
                        float cloudRight = cloudLeft + chosenCloud->getGlobalBounds().width;
                        float cloudBottom = chosenCloud->getPosition().y + chosenCloud->getGlobalBounds().height;
                        
                        // Position raindrop within cloud's horizontal bounds and just below it
                        // But avoid the tree area (x between 810 and 810+treeWidth)
                        float treeLeft = 810;
                        float treeRight = 810 + spriteTree.getGlobalBounds().width;
                        float dropX = cloudLeft + (rand() % static_cast<int>(chosenCloud->getGlobalBounds().width));
                        
                        // If drop would be in front of tree, adjust it
                        if (dropX > treeLeft && dropX < treeRight) {
                            // Move to left or right of tree randomly
                            dropX = (rand() % 2) ? treeLeft - 10 : treeRight + 10;
                        }
                        
                        raindrops[i].setPosition(dropX, cloudBottom);
                    }
                }
            }
        }

        // Draw everything with proper layering
        window.clear();
        
        // Background first
        window.draw(spriteBackground);
        
        // Clouds next (behind trees)
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        
        // Raindrops behind trees
        if (isRaining) {
            for (int i = 0; i < NUM_RAINDROPS; i++) {
                if (raindrops[i].getPosition().y > 0) { // Only draw visible raindrops
                    window.draw(raindrops[i]);
                }
            }
        }
        
        // Trees in front of clouds and raindrops
        window.draw(spriteTree);
        
        // Branches (part of the tree)
        for (int i = 0; i < NUM_BRANCHES; i++) {
            window.draw(branches[i]);
        }
        
        // Game objects in front of trees
        window.draw(spritePlayer);
        window.draw(spriteAxe);
        window.draw(spriteLog);
        window.draw(spriteRIP);
        window.draw(spriteFire);
        window.draw(spriteBee);
        
        // UI elements on top
        window.draw(scoreText);
        window.draw(timeBar);

        if (paused) {
            window.draw(messageText);
        }

        window.display();
    }

    return 0;
}

void updateBranches(int seed) {
    for (int j = NUM_BRANCHES - 1; j > 0; j--) {
        branchPositions[j] = branchPositions[j - 1];
    }

    srand((int)time(0) + seed);
    int r = (rand() % 5);
    switch (r) {
        case 0:
            branchPositions[0] = side::LEFT;
            break;
        case 1:
            branchPositions[0] = side::RIGHT;
            break;
        default:
            branchPositions[0] = side::NONE;
            break;
    }
}
