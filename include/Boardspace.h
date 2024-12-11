#ifndef Boardspace_H
#define Boardspace_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

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

#endif
