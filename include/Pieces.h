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

    // default print statement for any board space
    virtual void landedOnSpace(){ 
        std::cout << getSpaceName() << " which is a " << getSpaceType() << " type space." << std::endl;
    }

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
    std::string getSpaceName() const {
        return spaceName;
    }
    int getBoardPositionX() {
        return boardPositionX;
    }
    int getBoardPositionY() {
        return boardPositionY;
    }

    // overloading the operator << to output the name of the board space when called in the main code
    friend std::ostream& operator<<(std::ostream& os, const boardSpace& space) {
        os << space.getSpaceName(); // outputs the space's name
        return os;
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

    // specific print statement for property space
    virtual void landedOnSpace() override {
        if (getOwned() == true){
            std::cout << getSpaceName() << " which is a " << getSpaceType() << " type space." << std::endl;
            std::cout << "Property " << getSpaceName() << " is owned!" << std::endl;
        }
        else {
            std::cout << getSpaceName() << " which is a " << getSpaceType() << " type space." << std::endl;
            std::cout << "Property " << getSpaceName() << " is unowned!" << std::endl;
        }
    }

    // print statement when a property is purchased
    virtual void propertyPurchased(){
        std::cout << "You've decided to purchase " << getSpaceName() << "!" << std::endl;
    }

    // print statement when a property is reopened
    virtual void propertyOpened() {
        std::cout << "Player " << (landlordID+1) << "'s property " << getSpaceName() << " is now available for ownership!" << std::endl;
    }

    // setters
    void setOwned(bool inputOwned){
        owned = inputOwned;
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

    // overloading the assignment operator (=) for price setting
    Property& operator=(int newPrice) {
        setPrice(newPrice);  // calling the setter function
        return *this;
    }

    void setRent(int inputRent) {
        rent = inputRent;
    }
    
    // overloading the assignment operator (+) for rent setting
    Property& operator+(int newRent) {
        setRent(newRent);  // calling the setter function
        return *this;
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
class PropertyMarker : public Property {
private:
    int propertyMarkerPlayerID;
    std::string propertyMarkerPlayerName;
    sf::Sprite propertyMarkerSprite;
    sf::Texture propertyMarkerTexture;
public:
    // constructor for PropertyMarker, associating it with a Property
    PropertyMarker(int inputPropertyMarkerPlayerID, std::string inputPropertyMarkerPlayerName, const sf::Texture& inputPropertyMarkerTexture, int inputPropertymarkerPositionX, int inputPropertymarkerPositionY,
                   int inputPrice, int inputRent, bool inputOwned, const std::string& inputName, int inputIndex, const std::string& inputType, 
                   int inputBoardPositionX, int inputBoardPositionY, int inputMarkerPixelX, int inputMarkerPixelY)
        : Property(inputPrice, inputRent, inputOwned, inputName, inputIndex, inputType, inputBoardPositionX, inputBoardPositionY, inputMarkerPixelX, inputMarkerPixelY), 
          propertyMarkerPlayerName(inputPropertyMarkerPlayerName) {
        
        propertyMarkerPlayerID = inputPropertyMarkerPlayerID;
        propertyMarkerTexture = inputPropertyMarkerTexture;
        propertyMarkerSprite.setTexture(propertyMarkerTexture);
        propertyMarkerSprite.setPosition(inputPropertymarkerPositionX, inputPropertymarkerPositionY);
    }

    // destructor
    ~PropertyMarker() {}

    // specific print statement for the property marker
    virtual void propertyPurchased() override {
        std::cout << "Property marker placed on " << getSpaceName() << " for " << propertyMarkerPlayerName << "!" << std::endl;
    }

    // print statement when a property is reopened
    virtual void propertyOpened() override {
        std::cout << "Property marker removed on " << getSpaceName() << " for " << propertyMarkerPlayerName << "!" << std::endl;
    }

    // getters
    sf::Sprite getPropertyMarkerSprite() {
        return propertyMarkerSprite;
    }
    std::string getPropertyMarkerPlayerName(){
        return propertyMarkerPlayerName;
    }
    int getPropertyMarkerPlayerID(){
        return propertyMarkerPlayerID;
    }
};

// player class:
class Player {
private:
    std::string playerName;
    signed long playerMoney;
    int playerIndex;
    int playerID;
    sf::Sprite playerSprite;
    sf::Texture playerTexture;
    bool getOutOfJailFree;
    bool inJail;
public:
    // constructor: initializes all objects
    Player(const std::string& inputName, int inputPlayerIndex, int inputPlayerID, int inputPositionX, int inputPositionY, int inputMoney, const sf::Texture& inputTexture, bool inputInJail)
    : playerName(inputName), playerIndex(inputPlayerIndex), playerID(inputPlayerID), playerMoney(inputMoney), inJail(inputInJail) {
        playerTexture = inputTexture;
        playerSprite.setTexture(playerTexture);
        playerSprite.setPosition(inputPositionX, inputPositionY);
    }

    // destructor: destroys the class' instatiation
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
    void setPlayerMoney(signed long newMoney) {
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
