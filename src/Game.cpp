#include "Game.hpp"
#include "Config.hpp"
#include <thread>
#include <chrono>

Game::Game(const sf::VideoMode& videoMode, const std::string& windowName, const std::string& mapFile) :
    map(mapFile)
{
    window.create(videoMode, windowName, sf::Style::Close); 
}

std::string Game::getInfoString(const std::shared_ptr<GameObject> gameObject) {
    return "Health: " + std::to_string(gameObject->getHealth()) + " | " +
        "Damage: " + std::to_string(gameObject->getDamage());
}

WindowState Game::startGame() {
    GameState gameState = GameState::Game;

    auto mapVec = map.getMap();
    //player in [0]
    auto objects = map.getObjects();
    auto player = objects[0];
    auto princess = map.getPrincess();

    auto windowSize = window.getSize();
    int mapWidth = mapVec[0].length() * SPRITE_SIZE;
    int mapHeight = mapVec.size() * SPRITE_SIZE;
    sf::View camera;
    camera.reset(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
    sf::View hud;
    hud.reset(sf::FloatRect(0, 0, windowSize.x, windowSize.y));

    sf::Font font;
    font.loadFromFile("../res/font.ttf");
    sf::Text healthText("", font, 16);
    healthText.setColor(sf::Color::White);
    healthText.setPosition(5, 0);
    healthText.setString(getInfoString(player));

    sf::Text endText("", font, 100);
    endText.setColor(sf::Color::Red);

    auto playerPos = player->getPosition();

    while(window.isOpen()) {
        sf::Event event;

        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return WindowState::Close;
            }
            
            if (gameState == GameState::Win || gameState == GameState::Lose) {
                window.close();
                return WindowState::Restart;
            }
            
            Point offset = {0, 0};
            bool isMove = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                offset = Point{-1, 0};
                isMove = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                offset = Point{1, 0};
                isMove = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                offset = Point{0, -1};
                isMove = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                offset = Point{0, 1};
                isMove = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                isMove = true;
            }

            if (isMove) {
                player->move(offset, objects, mapVec);
                playerPos = player->getPosition();
                
                for (int i = 1; i < objects.size(); ++i) {
                    objects[i]->move(playerPos, objects, mapVec);
                }
                
                int i = 0;
                while (i < objects.size()) {
                    if (objects[i]->getHealth() <= 0) {
                        objects.erase(objects.begin() + i);
                        continue;
                    }
                    ++i;
                }

                healthText.setString(getInfoString(player));
                
                if (player->getHealth() <= 0) {
                    gameState = GameState::Lose;
                    endText.setString("DEAD");
                }
                else if (princess->getHealth() <= 0) {
                    gameState = GameState::Win;
                    endText.setString("Win!!!");
                }
            }
        }

        int camX = playerPos.x * SPRITE_SIZE, camY = playerPos.y * SPRITE_SIZE;
        auto cameraSize = camera.getSize();

        if (camX - cameraSize.x / 2 < 0)
            camX = cameraSize.x / 2; 
        else if (camX + cameraSize.x / 2 > mapWidth)
            camX = mapWidth - cameraSize.x / 2;

        if (camY - cameraSize.y / 2 < 0)
            camY = cameraSize.y / 2; 
        else if (camY + cameraSize.y / 2 > mapHeight)
            camY = mapHeight - cameraSize.y / 2;
        
        camera.setCenter(camX, camY);
        window.setView(camera);

        window.clear(sf::Color::Black);

        window.setView(camera);
        map.draw(window);
        for (int i = 0; i < objects.size(); ++i)
            objects[i]->draw(window);

        window.setView(hud);
        window.draw(healthText);
        if (gameState == GameState::Win || gameState == GameState::Lose) {
            auto bounds = endText.getLocalBounds();
            endText.setPosition(windowSize.x / 2 - bounds.width / 2, windowSize.y / 2 - bounds.height / 2);
            window.draw(endText);
        }
        
        window.display();

        if (gameState == GameState::Win || gameState == GameState::Lose)
            sf::sleep(sf::seconds(1));
            
    }
}
