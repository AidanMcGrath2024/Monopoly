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
    int landlordID;
    bool owned;
    int markerPixelX;
    int markerPixelY;
public:
    // constructor, initializes all variables
    Property(int inputPrice, int inputRent, bool inputOwned, const std::string& inputName, int inputIndex, const std::string& inputType, int inputBoardPositionX, int inputBoardPositionY, int inputMarkerPixelX, int inputMarkerPixelY)
        : boardSpace(inputName, inputIndex, inputType, inputBoardPositionX, inputBoardPositionY), price(inputPrice), rent(inputRent), owned(inputOwned), landlord(""), markerPixelX(inputMarkerPixelX), markerPixelY(inputMarkerPixelY)  {}

    // setters
    void setOwned(bool inputOwned){
        owned = inputOwned;
        if (inputOwned == false) {
            std::cout << "Player " << (landlordID+1) << "'s property " << getSpaceName() << " is now available for ownership!" << std::endl;
        }
    }

    void setLandlord(std::string inputLandlord){
        landlord = inputLandlord;
    }

    void setLandlordID(int inputLandlordID) {
        landlordID = inputLandlordID;
    }

    void setPrice(int inputPrice) {
        price = inputPrice;
    }
    void setRent(int inputRent) {
        rent = inputRent;
    }

    // getters
    int getPrice() const {
        return price;
    }
    int getRent() const {
        return rent;
    }

    std::string getLandlord() const {
        return landlord;
    }

    int getLandlordID() const {
        return landlordID;
    }

    bool getOwned() const {
        return owned;
    }

    int getMarkerPixelX() const {
        return markerPixelX;
    }

    int getMarkerPixelY() const {
        return markerPixelY;
    }

};

// Property Marker class:
class PropertyMarker {
private:
    int propertyMarkerPlayerID;
    sf::Sprite propertyMarkerSprite;
    sf::Texture propertyMarkerTexture;
public:
    PropertyMarker(int inputPropertyMarkerPlayerID, const sf::Texture& inputPropertyMarkerTexture, int inputPropertymarkerPositionX, int inputPropertymarkerPositionY)
    : propertyMarkerPlayerID(inputPropertyMarkerPlayerID) {
        propertyMarkerTexture = inputPropertyMarkerTexture;
        propertyMarkerSprite.setTexture(propertyMarkerTexture);
        propertyMarkerSprite.setPosition(inputPropertymarkerPositionX, inputPropertymarkerPositionY);
    }

    // destructor
    ~PropertyMarker() {
        std::cout << "Player" << (propertyMarkerPlayerID+1) << "'s property marker destroyed!.\n";
    }

    // getters
    sf::Sprite getPropertyMarkerSprite() {
        return propertyMarkerSprite;
    }
    int getPropertyMarkerPlayerID(){
        return propertyMarkerPlayerID;
    }
};

// player class:
class Player {
private:
    std::string playerName;
    int playerMoney;
    int playerIndex;
    int playerID;
    sf::Sprite playerSprite;
    sf::Texture playerTexture;
    bool getOutOfJailFree;
    bool inJail;
public:
    Player(const std::string& inputName, int inputPlayerIndex, int inputPlayerID, int inputPositionX, int inputPositionY, int inputMoney, const sf::Texture& inputTexture, bool inputInJail)
    : playerName(inputName), playerIndex(inputPlayerIndex), playerID(inputPlayerID), playerMoney(inputMoney), inJail(inputInJail) {
        playerTexture = inputTexture;
        playerSprite.setTexture(playerTexture);
        playerSprite.setPosition(inputPositionX, inputPositionY);
    }

    // destructor
    ~Player() {
        std::cout << "Player " << playerName << " is no longer playing.\n";
    }

    // setters
    void setPosition(int inputXcoord, int inputYcoord) {
        playerSprite.setPosition(inputXcoord, inputYcoord);
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
    void setPlayerID(int inputID) {
        playerID = inputID;
    }
    void setPlayerName(std::string newPlayerName) {
        playerName = newPlayerName;
    }
    void setGetOutOfJailFree(bool inputGetOutOfJailFree) {
        getOutOfJailFree = inputGetOutOfJailFree;
    }
    void setInJail(bool inputInJail) {
        inJail = inputInJail;
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
    int getPlayerID(){
        return playerID;
    }
    std::string getPlayerName() {
        return playerName;
    }
    bool getGetOutOfJailFree() {
        return getOutOfJailFree;
    }
    bool getInJail() {
        return inJail;
    }
};

void playMonopoly();
#endif
