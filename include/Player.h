#ifndef Player_H
#define Player_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class Player {
private:
    std::string playerName;
    int playerMoney;
    int playerPositionX;
    int playerPositionY;
    std::string playerProperties;
    sf::Sprite playerSprite;
public:
    Player(const std::string& inputName, int inputPositionX, int inputPositionY, int inputMoney, const sf::Texture& texture)
    : playerName(inputName), playerPositionX(inputPositionX), playerPositionY(inputPositionY), playerMoney(inputMoney), playerProperties("") {
        playerSprite.setTexture(texture);
        playerSprite.setPosition(inputPositionX, inputPositionY);
    }

    // destructor
    ~Player() {
        std::cout << "Player " << playerName << " is no longer playing.\n";
    }

    // setters
    void setPosition(int x, int y) {
        playerPositionX = x;
        playerPositionY = y;
        playerSprite.setPosition(x, y);
    }

    void setPlayerMoney(int newMoney) {
        playerMoney = newMoney;
   }
    void setPositionX(int inputPositionX) {
        playerPositionX = inputPositionX;
    }
    void setPositionY(int inputPositionY) {
        playerPositionY = inputPositionY;
    }
    void setPlayerName(std::string newPlayerName) {
        playerName = newPlayerName;
    }
    void getPlayerProperties(std::string newPlayerProperty) {
        // NEED TO IMPLEMENT THE ADDING OF PROPERTY TO A VECTOR
        playerProperties = newPlayerProperty; //horzcat? 
    }

    // getters
    sf::Sprite getSprite() {
        return playerSprite;
    }

    int getPlayerMoney(){
        return playerMoney;
    }
    int getPlayerPositionX() {
        return playerPositionX;
    }
    int getPlayerPositionY() {
        return playerPositionY;
    }
    std::string getPlayerName() {
        return playerName;
    }
    std::string getPlayerProperties() {
        return playerProperties;
    }
};
#endif
