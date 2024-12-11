#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <atomic>
#include <cstdlib>
#include <random>
#include <ctime>
#include <vector>
#include "Boardspace.h"
#include "House.h"
#include "Player.h"



int rollDice(int dif) {
    int min = 1, max = 6;
    std::mt19937 gen(time(0) + dif);
    std::uniform_int_distribution<> distrib(min, max);
    int dieRoll = distrib(gen);
    return dieRoll;
}

int rollDiceSequence() {

    int die1 = rollDice(rand());
    int die2 = rollDice(rand());
    int roll = die1 + die2;
    std::cout << "Die 1: " << die1 << "\nDie 2: " << die2 << "\nRoll: " << roll << "\n";
    return roll; 
    
}

int main() {
    // creating a vector listing out all board space names
    std::vector<std::string> boardSpaceNames = {"GO","MEDITERRANEAN AVENUE","COMMUNITY CHEST","BALTIC AVENUE","INCOME TAX","ORIENTAL AVENUE","CHANCE","VERMONT AVENUE","CONNECTICUT AVENUE","ST. CHARLES PLACE",
        "ELECTRIC COMPANY","STATES AVENUE","VIRGINIA AVENUE","PENNSYLVANIA RAILROAD","ST. JAMES PLACE","COMMUNITY CHEST","TENNESSEE AVENUE","NEW YORK AVENUE","FREE PARKING","KENTUCKY AVENUE","CHANCE",
        "INDIANA AVENUE","ILLINOIS AVENUE","B&O RAILROAD","ATLANTIC AVENUE","VENTNOR AVENUE","WATER WORKS","MARVIN GARDENS","GO TO JAIL","PACIFIC AVENUE","NORTH CAROLINA AVENUE","COMMUNITY CHEST",
        "PENNSYLVANIA AVENUE","SHORT LINE RAILROAD","CHANCE","PARK PLACE","LUXURY TAX","BOARDWALK"}; // 1x40 vector storing all board space names 

    // creating a 2x40 vector listing out all board space pixel locations (x,y)
    std::vector<std::pair<int, int>> pixelLocations = {
        {738, 738}, {653, 738}, {590, 738}, {527, 738}, {464, 738}, {401, 738}, {338, 738}, {275, 738}, {212, 738}, {149, 738}, {62, 738},
        {62, 653}, {62, 590}, {62, 527}, {62, 464}, {62, 401}, {62, 338}, {62, 275}, {62, 212}, {62, 149}, {62, 62},
        {149, 62}, {212, 62}, {275, 62}, {338, 62}, {401, 62}, {464, 62}, {527, 62}, {590, 62}, {653, 62}, {738, 62},
        {738, 149}, {738, 212}, {738, 275}, {738, 338}, {738, 401}, {738, 464}, {738, 527}, {738, 590}, {738, 653}
        };

    std::vector<boardSpace> boardSpaces; // initializing a vector to hold all 40 board space objects

    for (int i = 0; i < 40; ++i) { // loop to create the 40 board spaces
        std::string name = boardSpaceNames[i]; 
        int inputXPixel = pixelLocations[i].first;
        int inputYPixel = pixelLocations[i].second;

        std::string type = "blank"; // temporarily setting spaceType as "blank"

        boardSpaces.push_back(boardSpace(name, i, type, inputXPixel, inputYPixel)); // creating a boardSpace object and pushing it into the boardSpaces vector
    }
    
    // creating a vector listing out the names of the character files
    std::vector<std::string> playerCharacterFiles = {"Images/Battleship.png","Images/Boot.png","Images/Car.png","Images/Dog.png",
    "Images/HorseRider.png","Images/Iron.png","Images/Thimble.png","Images/Tophat.png","Images/Wheelbarrow.png"};

    // Initializing player objects into a vector with a for loop:
    int startingMoney = 1500; // default starting money for Monopoly
    int startingXposition = boardSpaces[0].getBoardPositionX(); // extracting the x position of the GO space
    int startingYposition = boardSpaces[0].getBoardPositionY(); // extracting the y position of the GO space 
    std::vector<Player> players;
    for (int i = 0; i < 4; ++i) {
        std::string playerName;
        std::cout << "Enter Player " << (i + 1) << "'s name: " << std::endl;
        std::cin >> playerName;
        int playerCharacter;
        std::cout << "Which character would you like to be? \n Press: 1 for Battleship\n2 for Boot\n3 for Car\n4 Dog\n5 for Horse Rider\n6 for Iron\n7 for Thimble\n8 for Tophat\n9 for Wheelbarrow\n" << std::endl;
        std::cin >> playerCharacter;
        sf::Texture playerTexture;
        if (!playerTexture.loadFromFile(playerCharacterFiles[playerCharacter-1])) {
            std::cerr << "Error loading player image!" << std::endl;
            return -1;
        }
        players.push_back(Player(playerName, startingXposition, startingYposition, startingMoney, playerTexture));
    }

    // graphics
    sf::Texture boardTexture; // creating a texture for the board
    if (!boardTexture.loadFromFile("Images/Monopoly_Board.png")) { // loading the board
        std::cerr << "Error loading board image!" << std::endl; // error message if the board image doesn't load
        return -1;
    }
    sf::Sprite boardSprite(boardTexture); // turning the board into a sprite

    sf::Vector2u boardSize = boardTexture.getSize(); // extracting the size of the board

    sf::RenderWindow window(sf::VideoMode(boardSize.x, boardSize.y), "Monopoly Game"); // making a window

    int currentPlayerIndex = 0;  // starts with the first player

    // game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Game Logic for the current player's turn
        Player& currentPlayer = players[currentPlayerIndex];  // Get the current player

        std::cout << currentPlayer.getPlayerName() << "'s turn. Press Enter to roll the dice." << std::endl;
        std::cin.ignore();  // Wait for the player to press Enter
        int diceRoll = rollDiceSequence();

        // Calculate the new position
        int newIndex = (currentPlayer.getPlayerPositionX() + diceRoll) % 40; // 40 spaces on the board
        currentPlayer.setPosition(boardSpaces[newIndex].getBoardPositionX(), boardSpaces[newIndex].getBoardPositionY());

        // Display player movement
        std::cout << currentPlayer.getPlayerName() << " rolled a total of " << diceRoll << ", so they move to " << boardSpaces[newIndex].getSpaceName() << "." << std::endl;

        // Display player status
        std::cout << currentPlayer.getPlayerName() << ": $" << currentPlayer.getPlayerMoney() << " remaining.\n";

        // Check if the player should finish their turn and move to the next player
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();  // Move to the next player

        // Render the game
        window.clear();
        window.draw(boardSprite);
        window.draw(currentPlayer.getSprite());
        window.display();
    }
    return 0;
}
