#include "Pieces.h"

// functions:

 // dice rolling functions:
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

void playMonopoly() {
    // creating a vector listing out all board space names
    std::vector<std::string> boardSpaceNames = {"GO","MEDITERRANEAN AVENUE","COMMUNITY CHEST","BALTIC AVENUE","INCOME TAX","READING RAILROAD","ORIENTAL AVENUE","CHANCE","VERMONT AVENUE","CONNECTICUT AVENUE",
        "JUST VISITING", "ST. CHARLES PLACE","ELECTRIC COMPANY","STATES AVENUE","VIRGINIA AVENUE","PENNSYLVANIA RAILROAD","ST. JAMES PLACE","COMMUNITY CHEST","TENNESSEE AVENUE","NEW YORK AVENUE","FREE PARKING","KENTUCKY AVENUE","CHANCE",
        "INDIANA AVENUE","ILLINOIS AVENUE","B&O RAILROAD","ATLANTIC AVENUE","VENTNOR AVENUE","WATER WORKS","MARVIN GARDENS","GO TO JAIL","PACIFIC AVENUE","NORTH CAROLINA AVENUE","COMMUNITY CHEST",
        "PENNSYLVANIA AVENUE","SHORT LINE RAILROAD","CHANCE","PARK PLACE","LUXURY TAX","BOARDWALK"}; // 1x40 vector storing all board space names 

    // creating a 2x40 vector listing out all board space pixel locations (x,y)
    std::vector<std::pair<int, int>> pixelLocations = {
    {718, 718}, {633, 718}, {570, 718}, {507, 718}, {444, 718}, {381, 718}, {318, 718}, {255, 718}, {192, 718}, {129, 718}, {42, 718},
    {42, 633}, {42, 570}, {42, 507}, {42, 444}, {42, 381}, {42, 318}, {42, 255}, {42, 192}, {42, 129}, {42, 42},
    {129, 42}, {192, 42}, {255, 42}, {318, 42}, {381, 42}, {444, 42}, {507, 42}, {570, 42}, {633, 42}, {718, 42},
    {718, 129}, {718, 192}, {718, 255}, {718, 318}, {718, 381}, {718, 444}, {718, 507}, {718, 570}, {718, 633}, {66, 704}};

    // initializing all board spaces
    std::vector<std::unique_ptr<boardSpace>> boardSpaces; // initializing a vector of pointers to hold all 40 board space objects to support polymorphism
    boardSpaces.clear();  // clearing the vector and destroys all boardSpace objects

    for (int i = 0; i < 41; ++i) { // loop to create the 40 board spaces + the JAIL square
    std::string name = boardSpaceNames[i]; 
    int inputXPixel = pixelLocations[i].first;
    int inputYPixel = pixelLocations[i].second;
    // if statement structure to assign proper space type
    std::string type = "";
        if (name == "GO" || name == "COMMUNITY CHEST" || name == "CHANCE" || name == "INCOME TAX" || name == "LUXURY TAX" || 
            name == "FREE PARKING" || name == "JUST VISITING" || name == "GO TO JAIL" || name == "JAIL") {
            type = name; // Special board spaces are of their namesake type
            // creating a boardSpace object and pushing it into the boardSpaces vector:
            boardSpaces.push_back(std::make_unique<boardSpace>(name, i, type, inputXPixel, inputYPixel));
        } else {
            type = "PROPERTY"; // otherwise, its a property type
            // add the property to the boardSpaces vector:
            int price = 100;
            int rent = 50;
            bool owned = false;
            boardSpaces.push_back(std::make_unique<Property>(price, rent, owned, name, i, type, inputXPixel, inputYPixel));
        }
    }

    // creating a vector listing out the names of the character files
    std::vector<std::string> playerCharacterFiles = {"Images/Battleship.png","Images/Boot.png","Images/Car.png","Images/Dog.png",
    "Images/HorseRider.png","Images/Iron.png","Images/Thimble.png","Images/Tophat.png","Images/Wheelbarrow.png"};

    // initializing player objects into a vector with a for loop:
    std::vector<std::unique_ptr<Player>> players; // allocating a vector of smart pointers for the player objects
    players.clear();      // clearing the vector and destroys all Player objects
    for (int i = 0; i < 4; ++i) {
        int startingMoney = 1500; // default starting money for Monopoly
        int startingIndex = 0; // all players start on GO
        int startingXposition = boardSpaces[startingIndex]->getBoardPositionX(); // extracting the x position of the GO space
        int startingYposition = boardSpaces[startingIndex]->getBoardPositionY(); // extracting the y position of the GO space 
        bool jailStatus = false; // all players start out of jail (innocent until proven guilty!)
        std::string playerName; // making a player name variable
        std::cout << "Enter Player " << (i + 1) << "'s name: " << std::endl; // prompting the terminal for the player's name
        std::cin >> playerName; // player name input
        int playerCharacter; // making a player character indicator
        std::cout << "Which character would you like to be? \n Press: \n1 for Battleship\n2 for Boot\n3 for Car\n4 for Dog\n5 for Horse Rider\n6 for Iron\n7 for Thimble\n8 for Tophat\n9 for Wheelbarrow\n" << std::endl; // a menu for the user to choose their character from
        std::cin >> playerCharacter; // player character indicator input 
        sf::Texture playerTexture; // making a player character texture for their chosen board piece
        std::cout << "The chosen file is: " << playerCharacterFiles[(playerCharacter-1)] << std::endl;
        if (!playerTexture.loadFromFile(playerCharacterFiles[(playerCharacter-1)])) {
            std::cerr << "Error loading player image!" << std::endl;
        }
        players.push_back(std::make_unique<Player>(playerName, startingIndex, startingXposition, startingYposition, startingMoney, playerTexture, jailStatus));
    }
    // graphics
    sf::Texture boardTexture; // creating a texture for the board
    if (!boardTexture.loadFromFile("Images/Monopoly_Board.png")) { // loading the board
        std::cerr << "Error loading board image!" << std::endl; // error message if the board image doesn't load
    }
    sf::Sprite boardSprite(boardTexture); // turning the board into a sprite

    sf::Vector2u boardSize = boardTexture.getSize(); // extracting the size of the board

    sf::RenderWindow window(sf::VideoMode(boardSize.x, boardSize.y), "Monopoly Game"); // making a window

    // initial rendering of the window
    window.clear();
    window.draw(boardSprite);
    window.draw(players[0]->getSprite());
    window.draw(players[1]->getSprite());
    window.draw(players[2]->getSprite());
    window.draw(players[3]->getSprite());
    window.display();

    int currentPlayerIndex = 0;  // starts with the first player
    // game loop:
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // game logic for the current player's turn:
        Player& currentPlayer = *players[currentPlayerIndex];  // get the current player's object from the players vector

        // if player is in jail: 
        if (currentPlayer.getInJail() == true)
        {
                // if the player is in jail and has more money than bail
            if (currentPlayer.getPlayerMoney() > 50){
                std::cout << currentPlayer.getPlayerName() << " is in jail, you have these options:" << std::endl;
                // player has a get out of jail free card
                if (currentPlayer.getGetOutOfJailFree() == true){
                    // options for player
                    std::cout << "Press:\n" << 1 << ": use your Get Out of Jail Free card to be free \n"
                    << 2 << ": Pay $50 to be free\n" << 3 << ": try to roll doubles to be free" << std::endl;
                    std::string userEntry; // for jail choice
                    bool validInput = false; // input verification
                    while (validInput == false) {
                        std::cin >> userEntry;  
                        if (userEntry == "1") {
                            currentPlayer.setGetOutOfJailFree(false);
                            std::cout << currentPlayer.getPlayerName() << " used their Get out of Jail Free Card! They can now continue their turn:" << std::endl;
                            currentPlayer.setInJail(false);
                            validInput = true;
                        }
                        else if (userEntry == "2") {
                            currentPlayer.setPlayerMoney(currentPlayer.getPlayerMoney() - 50);
                            std::cout << currentPlayer.getPlayerName() << " paid $50 to get out of jail! They can now continue their turn:" << std::endl;
                            currentPlayer.setInJail(false);
                            validInput = true;
                        }
                        else if (userEntry == "3") {
                            std::cout << currentPlayer.getPlayerName() << " wants to roll the dice for freedom! Press the 'd' key to roll the dice:" << std::endl;
                            // dice rolling:
                            int diceRoll = 0;
                            bool validInput = false; // input verification
                            int die1;
                            int die2;
                            while (validInput == false) {  
                                std::cin >> userEntry;

                                if (userEntry == "d") {
                                    die1 = rollDice(rand());
                                    die2 = rollDice(rand());
                                    std::cout << "First die: " << die1 << std::endl;
                                    std::cout << "Second die: " << die2 << std::endl;
                                    validInput = true;
                                    if (die1 == die2) {
                                        std::cout << "Congratulations you rolled doubles! You are free to continue your turn: " << std::endl;
                                        currentPlayer.setInJail(false);
                                    }
                                    else {
                                        std::cout << "You did not roll doubles! You must stay in jail. Your turn is skipped." << std::endl;
                                        currentPlayer.setInJail(true);
                                    }
                                } 
                                else {
                                    std::cout << "Wrong key! Please press the 'd' key to roll the dice." << std::endl << std::endl;
                                }
                            }
                        }
                        else {
                            std::cout << "Wrong key! Please press the '1', '2', or '3' keys to make a choice." << std::endl << std::endl;
                        }
                    }
                }
                // if the player is in jail, does not have a get out of jail free card, and has more than bail
                else if (currentPlayer.getGetOutOfJailFree() == false){
                    std::cout << "Press:\n" << 1 << ": Pay $50 to be free" << 2 << ": try to roll doubles to be free" << std::endl;
                    std::string userEntry; // for jail choice
                    bool validInput = false; // input verification
                    while (validInput == false) {
                        std::cin >> userEntry;  
                        if (userEntry == "1") {
                            currentPlayer.setPlayerMoney(currentPlayer.getPlayerMoney() - 50);
                            std::cout << currentPlayer.getPlayerName() << " paid $50 to get out of jail! They can now continue their turn:" << std::endl;
                            currentPlayer.setInJail(false);
                            validInput = true;
                        } 
                        else if (userEntry == "2") {
                            std::cout << currentPlayer.getPlayerName() << " wants to roll the dice for freedom! Press the 'd' key to roll the dice:" << std::endl;
                            // dice rolling:
                            int diceRoll = 0;
                            bool validInput = false; // input verification
                            int die1;
                            int die2;
                            while (validInput == false) {  
                                std::cin >> userEntry;

                                if (userEntry == "d") {
                                    die1 = rollDice(rand());
                                    die2 = rollDice(rand());
                                    std::cout << "First die: " << die1 << std::endl;
                                    std::cout << "Second die: " << die2 << std::endl;
                                    validInput = true;
                                    if (die1 == die2) {
                                        std::cout << "Congratulations, you rolled doubles! You are free to continue your turn: " << std::endl;
                                        currentPlayer.setInJail(false);
                                    }
                                    else {
                                        std::cout << "You did not roll doubles! You must stay in jail. Your turn is skipped." << std::endl;
                                        currentPlayer.setInJail(true);
                                    }
                                } 
                                else {
                                    std::cout << "Wrong key! Please press the 'd' key to roll the dice." << std::endl << std::endl;
                                }
                            }
                        }
                        else {
                            std::cout << "Wrong key! Please press the '1' or '2' key to make a choice." << std::endl << std::endl;
                        }
                    }
                }
            }
            // if the player has a get out of jail free card, and has less money than bail
            else if (currentPlayer.getGetOutOfJailFree() == true && currentPlayer.getPlayerMoney() < 50){
                std::cout << "Press:\n" << 1 << ": use your Get Out of Jail Free card to be free \n"
                << 2 << ": try to roll doubles to be free" << std::endl;
                std::string userEntry; // for jail choice
                bool validInput = false; // input verification
                while (validInput == false) {
                    std::cin >> userEntry;
                    if (userEntry == "1") {
                        currentPlayer.setGetOutOfJailFree(false);
                        std::cout << currentPlayer.getPlayerName() << " used their Get out of Jail Free Card! They can now continue their turn:" << std::endl;
                        currentPlayer.setInJail(false);
                        validInput = true;
                    }
                    else if (userEntry == "2") {
                        std::cout << currentPlayer.getPlayerName() << " wants to roll the dice for freedom! Press the 'd' key to roll the dice:" << std::endl;
                        // dice rolling:
                        int diceRoll = 0;
                        bool validInput = false; // input verification
                        int die1;
                        int die2;
                        while (validInput == false) {  
                            std::cin >> userEntry;

                            if (userEntry == "d") {
                                die1 = rollDice(rand());
                                die2 = rollDice(rand());
                                std::cout << "First die: " << die1 << std::endl;
                                std::cout << "Second die: " << die2 << std::endl;
                                validInput = true;
                                if (die1 == die2) {
                                    std::cout << "Congratulations, you rolled doubles! You are free to continue your turn: " << std::endl;
                                    currentPlayer.setInJail(false);
                                }
                                else {
                                    std::cout << "You did not roll doubles! You must stay in jail. Your turn is skipped." << std::endl;
                                    currentPlayer.setInJail(true);
                                }
                            } 
                            else {
                                std::cout << "Wrong key! Please press the 'd' key to roll the dice." << std::endl << std::endl;
                            }
                        }
                    }
                    else {
                        std::cout << "Wrong key! Please press the '1' or '2' key to make a choice." << std::endl << std::endl;
                    }
                }
            }
            // otherwise, the player's only option is to try to roll doubles
            else {
                std::string userEntry; // for jail choice
                bool validInput = false; // input verification
                std::cout << "Your only option is to attempt to roll doubles!" << std::endl;
                std::cout << "Press the 'd' key to roll the dice:" << std::endl;
                // dice rolling:
                int diceRoll = 0;
                bool rollInput = false; // input verification
                int die1;
                int die2;
                while (rollInput == false) {  
                    std::cin >> userEntry;

                    if (userEntry == "d") {
                        die1 = rollDice(rand());
                        die2 = rollDice(rand());
                        std::cout << "First die: " << die1 << std::endl;
                        std::cout << "Second die: " << die2 << std::endl;
                        rollInput = true;
                        if (die1 == die2) {
                            std::cout << "Congratulations, you rolled doubles! You are free to continue your turn: " << std::endl;
                            currentPlayer.setInJail(false);
                        }
                        else {
                            std::cout << "You did not roll doubles! You must stay in jail. Your turn is skipped." << std::endl;
                            currentPlayer.setInJail(true);
                        }
                    } 
                    else {
                        std::cout << "Wrong key! Please press the 'd' key to roll the dice." << std::endl << std::endl;
                    }
                }
            }
        }

        // if player is not in jail, their turn continues:
        if (currentPlayer.getInJail()==false) {
            std::string userEntry; // for dice rolling
            std::cout << currentPlayer.getPlayerName() << "'s turn. Press 'd' to roll the dice." << std::endl << std::endl;

            // dice rolling:
            int diceRoll = 0;
            bool validInput = false; // input verification
            while (validInput == false) {  
                std::cin >> userEntry;

                if (userEntry == "d") {
                    diceRoll = rollDiceSequence();
                    validInput = true;
                } else {
                    std::cout << "Wrong key! Please press the 'd' key to roll the dice." << std::endl << std::endl;
                }
            }

            // if player is on or passing GO: (must be handled before player's index is manipulated)
            if ((currentPlayer.getPlayerIndex() + diceRoll) > 40){
                std::cout << currentPlayer.getPlayerName() << " passed GO, they collect $200!" << std::endl << std::endl;
                currentPlayer.setPlayerMoney(currentPlayer.getPlayerMoney() + 200);
            }

            // calculate the new player position based on their index and dice roll
            int newIndex = (currentPlayer.getPlayerIndex() + diceRoll) % 40; // 40 spaces on the board
            currentPlayer.setPosition(boardSpaces[newIndex]->getBoardPositionX(), boardSpaces[newIndex]->getBoardPositionY());
            currentPlayer.setPlayerIndex(newIndex);

            // alerting the terminal that the player moved
            std::cout << currentPlayer.getPlayerName() << " rolled a total of " << diceRoll << ", so they move to " << boardSpaces[newIndex]->getSpaceName() << "." << std::endl << std::endl;

            // updating the window
            window.clear();
            window.draw(boardSprite);
            window.draw(players[0]->getSprite());
            window.draw(players[1]->getSprite());
            window.draw(players[2]->getSprite());
            window.draw(players[3]->getSprite());
            window.display();

            // player options based on space they landed on

            // if player landed on a property:
            if (boardSpaces[newIndex]->getSpaceType() == "PROPERTY") {
                Property* propertySpace = dynamic_cast<Property*>(boardSpaces[newIndex].get()); // cast to boardSpaces vector to see if the board space is a property, then make that boardSpaces instance a pointer to the property object
                // if the property is unowned and the player can afford it:
                if (propertySpace->getOwned() == false && currentPlayer.getPlayerMoney() >= propertySpace->getPrice()) {
                    std::cout << currentPlayer.getPlayerName() << " has landed on the property " << boardSpaces[newIndex]->getSpaceName() <<
                    " which has a price of $" << propertySpace->getPrice() << ", and is able to afford it - would you like to purchase it?\nPress:\ny for YES\nn for NO" << std::endl << std::endl;
                    bool validInput = false;
                    while (validInput == false) {  
                        std::cin >> userEntry;
                        if (userEntry == "y") {
                            std::cout << "You've decided to purchase " << boardSpaces[newIndex]->getSpaceName() << "!" << std::endl << std::endl;
                            propertySpace->setOwned(true); // property is now set to owned
                            propertySpace->setLandlordID(currentPlayerIndex); // setting the property owner's ID to the current player
                            propertySpace->setLandlord(currentPlayer.getPlayerName()); // setting the property owner's landlord name to the current player's name
                            currentPlayer.setPlayerMoney(currentPlayer.getPlayerMoney()-propertySpace->getPrice()); // subtracting the price of the property from the player's wallet
                            validInput = true; // input was valid
                            // ** ADD MARKER ON BOARD **
                        }
                        else if (userEntry == "n") {
                            std::cout << "You've decided not to purchase " << boardSpaces[newIndex]->getSpaceName() << "!" << std::endl << std::endl;
                            validInput = true; // input was valid
                        }
                        else {
                            std::cout << "Wrong key! Please press the 'y' or 'n' key to choose." << std::endl << std::endl;
                        }
                    }
                }
                // if the player cannot afford the property:
                else if (propertySpace->getPrice() > currentPlayer.getPlayerMoney()) {
                    // alerting the terminal the current player cannot afford the property:
                    std::cout << currentPlayer.getPlayerName() << " has landed on the property " << boardSpaces[newIndex]->getSpaceName() <<
                    " which has a price of $" << propertySpace->getPrice() << " which " << currentPlayer.getPlayerName() << " cannot afford!" << std::endl << std::endl;
                }
                // if the property is already owned:
                else if (propertySpace->getOwned() == true) {
                    // alerting the terminal the current player was charged:
                    std::cout << currentPlayer.getPlayerName() << " has landed on the property " << boardSpaces[newIndex]->getSpaceName() <<
                    " which is owned by " << propertySpace->getLandlord() << ", you must pay their rent of $" << propertySpace->getRent() << "!" << std::endl << std::endl;
                    // subtracting the rent of the property from the player's wallet:
                    currentPlayer.setPlayerMoney(currentPlayer.getPlayerMoney()-propertySpace->getRent());
                    // adding the rent charge of the property to the owner's wallet:
                    players[propertySpace->getLandlordID()]->setPlayerMoney(players[propertySpace->getLandlordID()]->getPlayerMoney() + propertySpace->getRent());
                    // alerting the terminal the current player was charged:
                    std::cout << propertySpace->getLandlord() << " collected $" << propertySpace->getRent() << ", raising their wallet to " <<
                    players[propertySpace->getLandlordID()]->getPlayerMoney() << "!" << std::endl << std::endl;
                }
            }

            // if player landed on a chance card:
            if (boardSpaces[newIndex]->getSpaceType() == "CHANCE") {
                int cardIndex = rollDice(0);
                if (cardIndex == 6) { // get out of jail free card
                    if (currentPlayer.getGetOutOfJailFree()==true){
                        std::cout << currentPlayer.getPlayerName() << " already had a get out of jail free card, amd drew another get out of jail free card! They only keep one however." << std::endl << std::endl;
                    }
                    else{
                        currentPlayer.setGetOutOfJailFree(true);
                        std::cout << currentPlayer.getPlayerName() << " drew a get out of jail free card!" << std::endl << std::endl;
                    }
                    
                }
                else {
                    std::cout << currentPlayer.getPlayerName() << " receives a random monetary value between -100 and 100..." << std::endl << std::endl;
                    int min = -100, max = 100;
                    std::mt19937 gen(time(0));
                    std::uniform_int_distribution<> distrib(min, max);
                    int cardMoney = distrib(gen);
                    currentPlayer.setPlayerMoney(currentPlayer.getPlayerMoney() + cardMoney);
                    std::cout << "The cards have granted you $" << cardMoney << "!\n";
                }
            }

            // if player landed on Community Chest:
            if (boardSpaces[newIndex]->getSpaceType() == "COMMUNITY CHEST") {
                std::cout << currentPlayer.getPlayerName() << " landed on " << boardSpaces[newIndex]->getSpaceName() << ", they receive a random monetary value of -150 to 150..." << std::endl << std::endl;
                int min = -150, max = 150;
                std::mt19937 gen(time(0));
                std::uniform_int_distribution<> distrib(min, max);
                int cardMoney = distrib(gen);
                currentPlayer.setPlayerMoney(currentPlayer.getPlayerMoney() + cardMoney);
                std::cout << "The cards have granted you $" << cardMoney << "!\n";
            }

            // if player landed on Go To Jail:
            if (boardSpaces[newIndex]->getSpaceType() == "GO TO JAIL") {
                std::cout << "Oh no! " << currentPlayer.getPlayerName() << " landed on " << boardSpaces[newIndex]->getSpaceName() << "!" << std::endl;
                if (currentPlayer.getGetOutOfJailFree() == true){
                    std::cout << currentPlayer.getPlayerName() << " has a Get Out of Jail Free Card! Would you like to use it?\nPress:\ny for YES\nn for NO" << std::endl;
                    bool validInput = false;
                    while (validInput == false) {  
                        std::cin >> userEntry;
                        if (userEntry == "y") {
                            std::cout << "You've decided use your get out of jail free card!" << std::endl;
                            currentPlayer.setGetOutOfJailFree(false); // subtracting the price of the property from the player's wallet
                            validInput = true; // input was valid
                        }
                        else if (userEntry == "n") {
                            std::cout << "You've decided not to use your card ... curious. To jail you go! " << std::endl;
                            currentPlayer.setPosition(boardSpaces[40]->getBoardPositionX(), boardSpaces[40]->getBoardPositionY()); // manually setting the player's position to the JAIL square
                            currentPlayer.setPlayerIndex(10); // manually setting the player's index to be the same as the JUST VISITING square
                            currentPlayer.setInJail(true); // player's jail status updated to true
                            validInput = true; // input was valid
                        }
                        else {
                            std::cout << "Wrong key! Please press the 'y' or 'n' key to choose." << std::endl << std::endl;
                        }
                    }
                }
                // if player doesn't have a get out of jail free card:
                else {
                    std::cout << "To jail you go!" << std::endl;
                    currentPlayer.setPosition(boardSpaces[40]->getBoardPositionX(), boardSpaces[40]->getBoardPositionY()); // manually setting the player's position to the JAIL square
                    currentPlayer.setPlayerIndex(10); // manually setting the player's index to be the same as the JUST VISITING square
                    currentPlayer.setInJail(true); // player's jail status updated to false
                }
            }

            // if player landed on a tax card:
            if (boardSpaces[newIndex]->getSpaceType() == "LUXURY TAX" || boardSpaces[newIndex]->getSpaceType() == "INCOME TAX") {
                std::cout << currentPlayer.getPlayerName() << " landed on " << boardSpaces[newIndex]->getSpaceName() << " - meaning $200 is deducted from their wallet!" << std::endl << std::endl;
                currentPlayer.setPlayerMoney(currentPlayer.getPlayerMoney() - 200);
            }

            // if player landed on GO:
            if (boardSpaces[newIndex]->getSpaceType() == "GO") {
                std::cout << currentPlayer.getPlayerName() << " landed on " << boardSpaces[newIndex]->getSpaceName() << ", they collect $200!" << std::endl << std::endl;
                currentPlayer.setPlayerMoney(currentPlayer.getPlayerMoney() + 200);
            }

            // if player landed on Free Parking:
            if (boardSpaces[newIndex]->getSpaceType() == "FREE PARKING" || boardSpaces[newIndex]->getSpaceType() == "JUST VISITING" ) {
                std::cout << currentPlayer.getPlayerName() << " landed on " << boardSpaces[newIndex]->getSpaceName() << ", nothing happens!" << std::endl << std::endl;
            }
            // displaying the player's status
            std::cout << currentPlayer.getPlayerName() << ": $" << currentPlayer.getPlayerMoney() << " remaining.\n\n\n";

            // breaking up the terminal between turns:
            std::cout << "--------------------------------------------------------" << std::endl;

            // check if the player should finish their turn and move to the next player
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();  // move to the next player
        }

        // player is in jail, turn is skipped!
        else {
            std::cout << currentPlayer.getPlayerName() << " remains in Jail! Turn is skipped." << std::endl;

            // displaying the player's status
            std::cout << currentPlayer.getPlayerName() << ": $" << currentPlayer.getPlayerMoney() << " remaining.\n\n\n";

            // breaking up the terminal between turns:
            std::cout << "--------------------------------------------------------" << std::endl;

            // check if the player should finish their turn and move to the next player
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();  // move to the next player
        }
    }
}
