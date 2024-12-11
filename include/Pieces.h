#ifndef Pieces_H
#define Pieces_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <random>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>

// classes:
class boardSpace {
private: 
    std::string spaceName; 
    int spaceIndex;
    std::string spaceType;
    int boardPositionX;
    int boardPositionY;
public:
    // constructor, initializes all variables
    boardSpace(const std::string& inputName, int inputIndex, const std::string& inputType, int inputBoardPositionX, int inputBoardPositionY)
        : spaceName(inputName), spaceIndex(inputIndex), spaceType(inputType), boardPositionX(inputBoardPositionX), boardPositionY(inputBoardPositionY) {}

    virtual ~boardSpace() {} // destructor

    // setters
    void setSpaceIndex(int inputIndex) {
        spaceIndex = inputIndex;
    }
    void setSpaceType(std::string inputType) {
        spaceType = inputType;
    }
    void setBoardPositionX(int inputX) {
        boardPositionX = inputX;
    }
    void setBoardPositionY(int inputY) {
        boardPositionY = inputY;
    }

    // getters
    int getSpaceIndex() {
        return spaceIndex;
    }
    std::string getSpaceType() {
        return spaceType;
    }
    std::string getSpaceName() {
        return spaceName;
    }
    int getBoardPositionX() {
        return boardPositionX;
    }
    int getBoardPositionY() {
        return boardPositionY;
    }
};

// property class inherits the boardSpace class
class Property : public boardSpace {
private:
    int price; 
    int rent;
    std::string landlord;
    bool owned;
public:
    // constructor, initializes all variables
    Property(int inputPrice, int inputRent, bool inputOwned, const std::string& inputName, int inputIndex, const std::string& inputType, int inputBoardPositionX, int inputBoardPositionY)
        : boardSpace(inputName, inputIndex, inputType, inputBoardPositionX, inputBoardPositionY), price(inputPrice), rent(inputRent), owned(inputOwned), landlord("") {}

    // getters
    int getPrice() const {
        return price;
    }
    int getRent() const {
        return rent;
    }

    // setter
    std::string getLandlord() const {
        return landlord;
    }

    // purchase message
    void purchase(const std::string& inputLandlord) {
        landlord = inputLandlord;
        std::cout << landlord << " has purchased " << getSpaceName() << " for $" << price << "!" << std::endl;
    }
};

// player class:
class Player {
private:
    std::string playerName;
    int playerMoney;
    int playerIndex;
    int playerPositionX;
    int playerPositionY;
    std::string playerProperties;
    sf::Sprite playerSprite;
public:
    Player(const std::string& inputName, int playerIndex, int inputPositionX, int inputPositionY, int inputMoney, const sf::Texture& texture)
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
    void setTexture(const sf::Texture& texture) {
        playerSprite.setTexture(texture);
    }
    void setPlayerMoney(int newMoney) {
        playerMoney = newMoney;
    }
    void setPlayerIndex(int inputIndex) {
        playerIndex = inputIndex;
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
    int getPlayerIndex(){
        return playerIndex;
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

void playMonopoly();
#endif
