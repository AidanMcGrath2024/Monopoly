#include "Pieces.h"

// functions:
int rollDice(int dif) {
    int min = 1, max = 6;
    std::mt19937 gen(time(0) + dif);
    std::uniform_int_distribution<> distrib(min, max);
    int dieRoll = distrib(gen);
    return dieRoll;
}

int rollDiceSequence() {
    int die1 = rollDice(rand());
    return die1;
}

// overloading rollDiceSequence function for rolling two dice
int rollDiceSequence(bool rollTwoDice) {
    int die1 = rollDice(rand());
    int die2 = rollDice(rand());
    int roll = die1 + die2;
    std::cout << "Die 1: " << die1 << "\nDie 2: " << die2 << "\nRoll: " << roll << "\n";
    return roll;
}

void playMonopoly() {
    // creating an array listing out all board space names
    const std::string boardSpaceNames[40] = {
    "GO", "MEDITERRANEAN AVENUE", "COMMUNITY CHEST", "BALTIC AVENUE", "INCOME TAX", "READING RAILROAD", 
    "ORIENTAL AVENUE", "CHANCE", "VERMONT AVENUE", "CONNECTICUT AVENUE", "JUST VISITING", "ST. CHARLES PLACE", 
    "ELECTRIC COMPANY", "STATES AVENUE", "VIRGINIA AVENUE", "PENNSYLVANIA RAILROAD", "ST. JAMES PLACE", 
    "COMMUNITY CHEST", "TENNESSEE AVENUE", "NEW YORK AVENUE", "FREE PARKING", "KENTUCKY AVENUE", "CHANCE", 
    "INDIANA AVENUE", "ILLINOIS AVENUE", "B&O RAILROAD", "ATLANTIC AVENUE", "VENTNOR AVENUE", "WATER WORKS", 
    "MARVIN GARDENS", "GO TO JAIL", "PACIFIC AVENUE", "NORTH CAROLINA AVENUE", "COMMUNITY CHEST", 
    "PENNSYLVANIA AVENUE", "SHORT LINE RAILROAD", "CHANCE", "PARK PLACE", "LUXURY TAX", "BOARDWALK"};

    // creating a 2x40 deque listing out all board space pixel locations (x,y) for the player icons
    std::deque<std::pair<int, int>> playerPixelLocations = {
    {718, 718}, {633, 718}, {570, 718}, {507, 718}, {444, 718}, {381, 718}, {318, 718}, {255, 718}, {192, 718}, {129, 718}, {42, 718},
    {42, 633}, {42, 570}, {42, 507}, {42, 444}, {42, 381}, {42, 318}, {42, 255}, {42, 192}, {42, 129}, {42, 42},
    {129, 42}, {192, 42}, {255, 42}, {318, 42}, {381, 42}, {444, 42}, {507, 42}, {570, 42}, {633, 42}, {718, 42},
    {718, 129}, {718, 192}, {718, 255}, {718, 318}, {718, 381}, {718, 444}, {718, 507}, {718, 570}, {718, 633}, {66, 704}};

    // creating a 2x40 vector listing out all board space pixel locations (x,y) for the player property markers
    std::vector<std::pair<int, int>> markerPixelLocations = {
    {729, 776}, {643, 683}, {580, 683}, {517, 683}, {454, 683}, {391, 683},{328, 683}, {265, 683}, {202, 683}, {139, 683}, {53, 776},
    {95, 643}, {95, 580}, {95, 517}, {95, 454}, {95, 391}, {95, 328}, {95, 265}, {95, 202}, {95, 139}, {53, 100},
    {140, 95}, {203, 95}, {266, 95}, {329, 95}, {392, 95}, {455, 95}, {518, 95}, {581, 95}, {644, 95}, {729, 100},
    {684, 139}, {684, 202}, {684, 265}, {684, 328}, {684, 391}, {684, 454}, {684, 517}, {684, 580}, {684, 643}, {77, 762}};

    // creating a 1x40 vector listing our all board space rents
    std::vector<int> spaceRents = {
    0, 15, 0, 15, 0, 25, 15, 0, 15, 15, 0, 15, 15, 15, 15, 25, 15, 0, 15, 15, 0, 15, 0, 15, 15, 25, 15, 15, 15, 35, 0, 15, 15, 0, 42, 25, 0, 50, 0, 100 };

    // initializing all board spaces
    std::vector<std::unique_ptr<boardSpace>> boardSpaces; // initializing a vector of pointers to hold all 40 board space objects to support polymorphism
    boardSpaces.clear();  // clearing the vector and destroys all boardSpace objects

    // before starting: asking the user for how fast they would like the game to be
    int gameSpeed;
    std::string gameSpeedInput;
    std::cout << "How fast would you like the game to be?\nInput an integer from 1 to 20, with 1 being the slowest game and 10 being very fast: \n (a reference - a game speed of 16 ends in about 2 cycles of the board)" << std::endl;
    bool validInput = false;
    while (validInput == false) {
        std::cin >> gameSpeedInput;
        if (gameSpeedInput == "1" || gameSpeedInput == "2" || gameSpeedInput == "3" || gameSpeedInput == "4" || gameSpeedInput == "5" || gameSpeedInput == "6" || gameSpeedInput == "7" || gameSpeedInput == "8" || gameSpeedInput == "9" || gameSpeedInput == "10"
        || gameSpeedInput == "11" || gameSpeedInput == "12" || gameSpeedInput == "13" || gameSpeedInput == "14" || gameSpeedInput == "15" || gameSpeedInput == "16" || gameSpeedInput == "17" || gameSpeedInput == "18" || gameSpeedInput == "19" || gameSpeedInput == "20") {
            std::cout << "You've decided to have a game speed of " << gameSpeedInput << "!" << std::endl << std::endl;
            gameSpeed = std::stoi(gameSpeedInput);
            validInput = true;
        }
        else {
            std::cout << "Wrong key! Please press 1-20 to choose." << std::endl << std::endl;
        }
    }

    for (int i = 0; i < 41; ++i) { // loop to create the 40 board spaces + the JAIL square
    std::string name = boardSpaceNames[i]; 
    int inputXPixel = playerPixelLocations[i].first;
    int inputYPixel = playerPixelLocations[i].second;
    int markerInputXPixel = markerPixelLocations[i].first;
    int markerInputYPixel = markerPixelLocations[i].second;
    // if statement structure to assign proper space type
    std::string type = "";
        // if a special space:
        if (name == "GO" || name == "COMMUNITY CHEST" || name == "CHANCE" || name == "INCOME TAX" || name == "LUXURY TAX" || 
            name == "FREE PARKING" || name == "JUST VISITING" || name == "GO TO JAIL" || name == "JAIL") {
            type = name; // Special board spaces are of their namesake type
            // creating a boardSpace object and pushing it into the boardSpaces vector:
            boardSpaces.push_back(std::make_unique<boardSpace>(name, i, type, inputXPixel, inputYPixel)); // pushing the board space into the boardSpaces vector
        // if a property:
        } else {
            type = "PROPERTY";
            // add the property to the boardSpaces vector:
            int rent = gameSpeed*spaceRents[i]; // rent is the ith element in the spaceRents vector, times the game speed
            int price = 2*rent; // each property's price is set to 2 times the rent
            bool owned = false; // no one owns the property 
            boardSpaces.push_back(std::make_unique<Property>(price, rent, owned, name, i, type, inputXPixel, inputYPixel, markerInputXPixel, markerInputYPixel)); // pushing the property into the boardSpaces vector
        }
    }

    // creating a vector listing out the names of the character files
    std::vector<std::string> playerCharacterFiles = {"Images/Battleship.png","Images/Boot.png","Images/Car.png","Images/Dog.png",
    "Images/HorseRider.png","Images/Iron.png","Images/Thimble.png","Images/Tophat.png","Images/Wheelbarrow.png"};

    // initializing player objects into a vector with a for loop:
    std::vector<std::unique_ptr<Player>> players; // allocating a vector of smart pointers for the player objects
    std::string player1CharacterSelection; // so other player's dont pick player 1's character
    std::string player2CharacterSelection; // so other player's dont pick player 2's character
    std::string player3CharacterSelection; // player 4 doesnt pick player 3, 2 or 1's character
    for (int playerIterator = 0; playerIterator < 4; ++playerIterator) {
        int startingMoney = 1500; // default starting money for Monopoly
        int startingIndex = 0; // all players start on GO
        int playerID = playerIterator;
        int startingXposition = boardSpaces[startingIndex]->getBoardPositionX(); // extracting the x position of the GO space
        int startingYposition = boardSpaces[startingIndex]->getBoardPositionY(); // extracting the y position of the GO space 
        bool jailStatus = false; // all players start out of jail (innocent until proven guilty!)
        std::string playerName; // making a player name variable
        std::cout << "Enter Player " << (playerIterator + 1) << "'s name: " << std::endl; // prompting the terminal for the player's name
        std::cin >> playerName; // player name input
        std::string playerCharacter; // making a player character indicator
        sf::Texture playerTexture; // making a player character texture for their chosen board piece
        std::cout << "Which character would you like to be? \n Press: \n1 for Battleship\n2 for Boot\n3 for Car\n4 for Dog\n5 for Horse Rider\n6 for Iron\n7 for Thimble\n8 for Tophat\n9 for Wheelbarrow\n" << std::endl; // a menu for the user to choose their character from
        bool playerCharacterValidInput = false;
        while (playerCharacterValidInput == false) {
            std::cin >> playerCharacter;
            if (playerCharacter != player1CharacterSelection && playerCharacter != player2CharacterSelection && playerCharacter != player3CharacterSelection
            && (playerCharacter == "1" || playerCharacter == "2" || playerCharacter == "3" || playerCharacter == "4" || playerCharacter == "5" || playerCharacter == "6"
            || playerCharacter == "7" || playerCharacter == "8" || playerCharacter == "9")) {
                int playerPick = std::stoi(playerCharacter);
                if (!playerTexture.loadFromFile(playerCharacterFiles[(playerPick-1)])) {
                    std::cerr << "Error loading player image!" << std::endl;
                }
                playerCharacterValidInput = true;
            }
            else {
                std::cout << "Wrong key or previously chosen character! Please choose another from 1-9." << std::endl << std::endl;
            }
        }
        if (playerIterator == 0) {
            player1CharacterSelection = playerCharacter;
        }
        else if (playerIterator == 1) {
            player2CharacterSelection = playerCharacter;
        }
        else if (playerIterator == 2) {
            player3CharacterSelection = playerCharacter;
        }
        players.push_back(std::make_unique<Player>(playerName, startingIndex, playerID, startingXposition, startingYposition, startingMoney, playerTexture, jailStatus));
    }


    // graphics

    // creating each player marker texture
    sf::Texture player1MarkerTexture, player2MarkerTexture, player3MarkerTexture, player4MarkerTexture;
    if (!player1MarkerTexture.loadFromFile("Images/Player1Marker.png")) { // loading Player1Marker.png
        std::cerr << "Error loading board image!" << std::endl; // error message if the board image doesn't load
    }
    if (!player2MarkerTexture.loadFromFile("Images/Player2Marker.png")) { // loading Player2Marker.png
        std::cerr << "Error loading board image!" << std::endl; // error message if the board image doesn't load
    }
    if (!player3MarkerTexture.loadFromFile("Images/Player3Marker.png")) { // loading Player3Marker.png
        std::cerr << "Error loading board image!" << std::endl; // error message if the board image doesn't load
    }
    if (!player4MarkerTexture.loadFromFile("Images/Player4Marker.png")) { // loading Player4Marker.png
        std::cerr << "Error loading board image!" << std::endl; // error message if the board image doesn't load
    }

    // creating a vector to store all player property markers
    std::vector<std::unique_ptr<PropertyMarker>> playerPropertyMarkers;

    // generating the board for the window
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
    for (int playerIterator = 0; playerIterator < players.size(); playerIterator++) {
        window.draw(players[playerIterator]->getSprite());
    }
    window.display();

    // game loop counters
    int turnCounter = 0; // starts at 0
    int currentPlayerIndex = 0;  // starts with the first player
    // game loop, which initiates as long as the window is open and there are more than 1 players remaining:
    while (window.isOpen() && players.size() > 1) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // accelerating game play over board cycles, favoring property owners
        if (turnCounter == 32) { // eight turn cycles
            for (int allSpaces = 0; allSpaces < 40; allSpaces++){
                if (boardSpaces[allSpaces]) { // ensures the board space is a valid pointer
                    Property* propertySpace = dynamic_cast<Property*>(boardSpaces[allSpaces].get());
                    if (propertySpace) { // ensures the pointer points to a property space
                        *propertySpace = (propertySpace->getPrice()*2); // multiplying price by 4, using the overloaded = operator
                        *propertySpace+(propertySpace->getRent()*4); // multiplying rent by 2, using the overloaded + operator
                    }
                }
            }
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "This game is taking a little long, property rents are doubled, and property prices are quadrupled!" << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;
        }
        else if (turnCounter == 64) { // 16 turn cycles
            for (int allSpaces = 0; allSpaces < 40; allSpaces++){
                if (boardSpaces[allSpaces]) { // ensures the board space is a valid pointer
                    Property* propertySpace = dynamic_cast<Property*>(boardSpaces[allSpaces].get());
                    if (propertySpace) { // ensures the pointer points to a property space
                        *propertySpace = (propertySpace->getPrice()*2); // multiplying price by 4, using the overloaded = operator
                        *propertySpace+(propertySpace->getRent()*4); // multiplying rent by 2, using the overloaded + operator
                    }
                }
            }
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "This game is getting long now, property rents are doubled and property prices are quadrupled again!" << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;
        }
        // if the game isn't over by now, I would fall asleep
        else if (turnCounter == 80) { // 20 turn cycles
            for (int allSpaces = 0; allSpaces < 40; allSpaces++){
                if (boardSpaces[allSpaces]) { // ensures the board space is a valid pointer
                    Property* propertySpace = dynamic_cast<Property*>(boardSpaces[allSpaces].get());
                    if (propertySpace) { // ensures the pointer points to a property space
                        *propertySpace = (propertySpace->getPrice()*8); // multiplying price by 36, using the overloaded = operator
                        *propertySpace+(propertySpace->getRent()*16); // multiplying rent by 72, using the overloaded + operator
                    }
                }
            }
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "Alright, time to touch grass now! Property rents are multiplied by 8, and property prices are multiplied by 16!" << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;
        }

        // game logic for the current player's turn:
        Player& currentPlayer = *players[currentPlayerIndex];  // get the current player's object from the players vector

        // if player is in jail: 
        if (currentPlayer.getInJail() == true)
        {
            // if the player is in jail and has more money than bail:
            if (currentPlayer.getPlayerMoney() > 50){
                std::cout << currentPlayer.getPlayerName() << " is in jail, you have these options:" << std::endl;
                // player has a get out of jail free card:
                if (currentPlayer.getGetOutOfJailFree() == true){
                    // options for player:
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
                            // pay $50:
                            currentPlayer.setPlayerMoney(currentPlayer.getPlayerMoney() - 50); // using the overloaded operator + to subtract $50 from their playerMoney object
                            std::cout << currentPlayer.getPlayerName() << " paid $50 to get out of jail! They can now continue their turn:" << std::endl;
                            currentPlayer.setInJail(false);
                            validInput = true;
                        }
                        else if (userEntry == "3") {
                            // rolling for doubles:
                            std::cout << currentPlayer.getPlayerName() << " wants to roll the dice for freedom! Press the 'd' key to roll the dice:" << std::endl;
                            // dice rolling:
                            int diceRoll = 0;
                            std::string rollChoice;
                            bool rollInput = false; // input verification for the roll
                            while (rollInput == false) {  
                                std::cin >> rollChoice;
                                if (rollChoice == "d") {
                                    int die1 = rollDiceSequence(); // using the roll dice sequence for just one die
                                    int die2 = rollDiceSequence(); // using the roll dice sequence for just one die
                                    std::cout << "First die: " << die1 << std::endl;
                                    std::cout << "Second die: " << die2 << std::endl;
                                    if (die1 == die2) {
                                        std::cout << "Congratulations you rolled doubles! You are free to continue your turn: " << std::endl;
                                        currentPlayer.setInJail(false);
                                    }
                                    else {
                                        std::cout << "You did not roll doubles! You must stay in jail. Your turn is skipped." << std::endl;
                                    }
                                    rollInput = true; // kicks out of the dice roll loop
                                    validInput = true; // kick out of hte menu choice loop
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
                    std::cout << "Press:\n" << 1 << ": Pay $50 to be free\n" << 2 << ": try to roll doubles to be free" << std::endl;
                    std::string userEntry; // for jail choice
                    bool validInput = false; // input verification
                    while (validInput == false) {
                        std::cin >> userEntry;  
                        if (userEntry == "1") {
                            currentPlayer.setPlayerMoney(currentPlayer.getPlayerMoney() - 50); // using the overloaded operator + to subtract $50 from their playerMoney object
                            std::cout << currentPlayer.getPlayerName() << " paid $50 to get out of jail! They can now continue their turn:" << std::endl;
                            currentPlayer.setInJail(false);
                            validInput = true;
                        } 
                        else if (userEntry == "2") {
                            std::cout << currentPlayer.getPlayerName() << " wants to roll the dice for freedom! Press the 'd' key to roll the dice:" << std::endl;
                            // dice rolling:
                            bool rollInput = false; // input verification
                            std::string rollChoice;
                            while (rollInput == false) {  
                                std::cin >> rollChoice;
                                if (rollChoice == "d") {
                                    int die1 = rollDiceSequence(); // using the roll dice sequence for just one die
                                    int die2 = rollDiceSequence(); // using the roll dice sequence for just one die
                                    std::cout << "First die: " << die1 << std::endl;
                                    std::cout << "Second die: " << die2 << std::endl;
                                    if (die1 == die2) {
                                        std::cout << "Congratulations, you rolled doubles! You are free to continue your turn: " << std::endl;
                                        currentPlayer.setInJail(false);
                                    }
                                    else {
                                        std::cout << "You did not roll doubles! You must stay in jail. Your turn is skipped." << std::endl;
                                    }
                                    validInput = true;
                                    rollInput = true;
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
                        bool rollInput = false; // input verification
                        std::string rollChoice;
                        while (rollInput == false) {  
                            std::cin >> rollChoice;
                            if (rollChoice == "d") {
                                int die1 = rollDiceSequence(); // using the roll dice sequence for just one die
                                int die2 = rollDiceSequence(); // using the roll dice sequence for just one die
                                std::cout << "First die: " << die1 << std::endl;
                                std::cout << "Second die: " << die2 << std::endl;
                                if (die1 == die2) {
                                    std::cout << "Congratulations, you rolled doubles! You are free to continue your turn: " << std::endl;
                                    currentPlayer.setInJail(false);
                                }
                                else {
                                    std::cout << "You did not roll doubles! You must stay in jail. Your turn is skipped." << std::endl;
                                }
                                validInput = true;
                                rollInput = true;
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
                std::cout << "Your only option is to attempt to roll doubles!" << std::endl;
                std::cout << "Press the 'd' key to roll the dice:" << std::endl;
                // dice rolling:
                std::string userEntry; // for jail choice
                bool rollInput = false; // input verification
                while (rollInput == false) {  
                    std::cin >> userEntry;
                    if (userEntry == "d") {
                        int die1 = rollDiceSequence(); // using the roll dice sequence for just one die
                        int die2 = rollDiceSequence(); // using the roll dice sequence for just one die
                        std::cout << "First die: " << die1 << std::endl;
                        std::cout << "Second die: " << die2 << std::endl;
                        if (die1 == die2) {
                            std::cout << "Congratulations, you rolled doubles! You are free to continue your turn: " << std::endl;
                            currentPlayer.setInJail(false);
                        }
                        else {
                            std::cout << "You did not roll doubles! You must stay in jail. Your turn is skipped." << std::endl;
                        }
                        rollInput = true;
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
                    // overloaded function rollDiceSequence accepts boolean input true to indicate two dice should be rolled
                    bool twoDiceRolled = true;
                    diceRoll = rollDiceSequence(twoDiceRolled);
                    validInput = true;
                } else {
                    std::cout << "Wrong key! Please press the 'd' key to roll the dice." << std::endl << std::endl;
                }
            }

            // if player is on or passing GO: (must be handled before player's index is manipulated)
            if ((currentPlayer.getPlayerIndex() + diceRoll) > 40){
                std::cout << currentPlayer.getPlayerName() << " passed GO, they collect $200!" << std::endl << std::endl;
                currentPlayer.setPlayerMoney(currentPlayer.getPlayerMoney() + 200); // using the overloaded operator + to add $200 to their playerMoney object
            }

            // calculate the new player position based on their index and dice roll
            int newIndex = (currentPlayer.getPlayerIndex() + diceRoll) % 40; // 40 spaces on the board - creating a new index to wrap around the board
            currentPlayer.setPosition(boardSpaces[newIndex]->getBoardPositionX(), boardSpaces[newIndex]->getBoardPositionY());
            currentPlayer.setPlayerIndex(newIndex);
            Property* propertySpace = dynamic_cast<Property*>(boardSpaces[newIndex].get()); // cast to boardSpaces vector to see if the board space is a property, then make that boardSpaces instance a pointer to the property object

            // alerting the terminal that the player moved
            std::cout << currentPlayer.getPlayerName() << " rolled a total of " << diceRoll << ", so they move to ";
            boardSpaces[newIndex]->landedOnSpace();

            // updating the window
            window.clear();
            window.draw(boardSprite);
            for (int playerIterator = 0; playerIterator < players.size(); playerIterator++) {
                window.draw(players[playerIterator]->getSprite());
            }
            for (int markerIterator = 0; markerIterator < size(playerPropertyMarkers); markerIterator++) {
                window.draw(playerPropertyMarkers[markerIterator]->getPropertyMarkerSprite());
            }
            window.display();

            // player options based on space they landed on

            // if player landed on a property:
            if (boardSpaces[newIndex]->getSpaceType() == "PROPERTY") {
                // if the property is already owned:
                if (propertySpace->getOwned() == true) {
                    // ... and the player already owns it
                    if (propertySpace->getLandlord() == currentPlayer.getPlayerName()){
                        std::cout << currentPlayer.getPlayerName() << " already owns " << *boardSpaces[newIndex] << ", nothing happens!" << std::endl << std::endl;
                    }
                    // otherwise, the player does not own it and is charged rent
                    else {
                    // alerting the terminal the current player was charged:
                    std::cout <<  *boardSpaces[newIndex] << " is owned by " << propertySpace->getLandlord() << ", you must pay their rent of $" << propertySpace->getRent() << "!" << std::endl << std::endl;
                    // subtracting the rent of the property from the player's wallet:
                    currentPlayer.setPlayerMoney(currentPlayer.getPlayerMoney()-propertySpace->getRent()); // using the overloaded operator + to subtract rent from their playerMoney object
                    // adding the rent charge of the property to the owner's wallet:
                    players[propertySpace->getLandlordID()]->setPlayerMoney(players[propertySpace->getLandlordID()]->getPlayerMoney() + propertySpace->getRent());
                    // alerting the terminal the current player was charged:
                    std::cout << propertySpace->getLandlord() << " collected $" << propertySpace->getRent() << ", raising their wallet to " <<
                    players[propertySpace->getLandlordID()]->getPlayerMoney() << "!" << std::endl << std::endl;
                    }
                }
                // if the property is unowned and the player can afford it:
                else if (propertySpace->getOwned() == false && currentPlayer.getPlayerMoney() >= propertySpace->getPrice()) {
                    std::cout << *boardSpaces[newIndex] << " has a price of $" << propertySpace->getPrice() << ", and is able to afford it - would you like to purchase it?\nPress:\ny for YES\nn for NO" << std::endl << std::endl;
                    bool validInput = false;
                    while (validInput == false) {  
                        std::cin >> userEntry;
                        if (userEntry == "y") {
                            propertySpace->propertyPurchased(); //
                            // manipulating player a property variables:
                            propertySpace->setOwned(true); // property is now set to owned
                            propertySpace->setLandlordID(currentPlayerIndex); // setting the property owner's ID to the current player
                            propertySpace->setLandlord(currentPlayer.getPlayerName()); // setting the property owner's landlord name to the current player's name
                            currentPlayer.setPlayerMoney(currentPlayer.getPlayerMoney()-propertySpace->getPrice()); // subtracting the price of the property from the player's wallet
                            // saving a player marker sprite to be drawn on the board, based on the current player's ID:
                            sf::Sprite playerMarker;
                            if (currentPlayer.getPlayerID() == 0){
                                playerPropertyMarkers.push_back(std::make_unique<PropertyMarker>(currentPlayer.getPlayerID(), currentPlayer.getPlayerName(), player1MarkerTexture, propertySpace->getMarkerPixelX(), propertySpace->getMarkerPixelY(), propertySpace->getPrice(),
                                propertySpace->getRent(),propertySpace->getOwned(),boardSpaces[newIndex]->getSpaceName(),boardSpaces[newIndex]->getSpaceIndex(),boardSpaces[newIndex]->getSpaceType(),boardSpaces[newIndex]->getBoardPositionX(),
                                boardSpaces[newIndex]->getBoardPositionY(),propertySpace->getMarkerPixelX(),propertySpace->getMarkerPixelY())); // long-winded declaration of a new Player Property Marker
                            }
                            else if (currentPlayer.getPlayerID() == 1){
                                playerPropertyMarkers.push_back(std::make_unique<PropertyMarker>(currentPlayer.getPlayerID(), currentPlayer.getPlayerName(), player2MarkerTexture, propertySpace->getMarkerPixelX(), propertySpace->getMarkerPixelY(), propertySpace->getPrice(),
                                propertySpace->getRent(),propertySpace->getOwned(),boardSpaces[newIndex]->getSpaceName(),boardSpaces[newIndex]->getSpaceIndex(),boardSpaces[newIndex]->getSpaceType(),boardSpaces[newIndex]->getBoardPositionX(),
                                boardSpaces[newIndex]->getBoardPositionY(),propertySpace->getMarkerPixelX(),propertySpace->getMarkerPixelY())); // long-winded declaration of a new Player Property Marker
                            }
                            else if (currentPlayer.getPlayerID() == 2){
                                playerPropertyMarkers.push_back(std::make_unique<PropertyMarker>(currentPlayer.getPlayerID(), currentPlayer.getPlayerName(), player3MarkerTexture, propertySpace->getMarkerPixelX(), propertySpace->getMarkerPixelY(), propertySpace->getPrice(),
                                propertySpace->getRent(),propertySpace->getOwned(),boardSpaces[newIndex]->getSpaceName(),boardSpaces[newIndex]->getSpaceIndex(),boardSpaces[newIndex]->getSpaceType(),boardSpaces[newIndex]->getBoardPositionX(),
                                boardSpaces[newIndex]->getBoardPositionY(),propertySpace->getMarkerPixelX(),propertySpace->getMarkerPixelY())); // long-winded declaration of a new Player Property Marker
                            }
                            else if (currentPlayer.getPlayerID() == 3){
                                playerPropertyMarkers.push_back(std::make_unique<PropertyMarker>(currentPlayer.getPlayerID(), currentPlayer.getPlayerName(), player4MarkerTexture, propertySpace->getMarkerPixelX(), propertySpace->getMarkerPixelY(), propertySpace->getPrice(),
                                propertySpace->getRent(),propertySpace->getOwned(),boardSpaces[newIndex]->getSpaceName(),boardSpaces[newIndex]->getSpaceIndex(),boardSpaces[newIndex]->getSpaceType(),boardSpaces[newIndex]->getBoardPositionX(),
                                boardSpaces[newIndex]->getBoardPositionY(),propertySpace->getMarkerPixelX(),propertySpace->getMarkerPixelY())); // long-winded declaration of a new Player Property Marker
                            }
                            playerPropertyMarkers.back()->propertyPurchased();
                            validInput = true; // input was valid
                        }
                        else if (userEntry == "n") {
                            std::cout << "You've decided not to purchase " << *boardSpaces[newIndex] << "!" << std::endl << std::endl;
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
                    std::cout << *boardSpaces[newIndex] << " has a price of $" << propertySpace->getPrice() << " which " << currentPlayer.getPlayerName() << " cannot afford!" << std::endl << std::endl;
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
                std::cout << currentPlayer.getPlayerName() << " landed on " << *boardSpaces[newIndex] << ", they receive a random monetary value of -150 to 150..." << std::endl << std::endl;
                int min = -150, max = 150;
                std::mt19937 gen(time(0));
                std::uniform_int_distribution<> distrib(min, max);
                int cardMoney = distrib(gen);
                currentPlayer.setPlayerMoney(currentPlayer.getPlayerMoney() + cardMoney);
                std::cout << "The cards have granted you $" << cardMoney << "!\n";
            }

            // if player landed on Go To Jail:
            if (boardSpaces[newIndex]->getSpaceType() == "GO TO JAIL") {
                std::cout << "Oh no! " << currentPlayer.getPlayerName() << " landed on " << *boardSpaces[newIndex] << "!" << std::endl;
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
                std::cout << currentPlayer.getPlayerName() << " landed on " << *boardSpaces[newIndex] << " - meaning $200 is deducted from their wallet!" << std::endl << std::endl;
                currentPlayer.setPlayerMoney(currentPlayer.getPlayerMoney() - 200);
            }

            // if player landed on GO:
            if (boardSpaces[newIndex]->getSpaceType() == "GO") {
                std::cout << currentPlayer.getPlayerName() << " landed on " << *boardSpaces[newIndex] << ", they collect $200!" << std::endl << std::endl;
                currentPlayer.setPlayerMoney(currentPlayer.getPlayerMoney() + 200);
            }

            // if player landed on Free Parking:
            if (boardSpaces[newIndex]->getSpaceType() == "FREE PARKING" || boardSpaces[newIndex]->getSpaceType() == "JUST VISITING" ) {
                std::cout << currentPlayer.getPlayerName() << " landed on " << *boardSpaces[newIndex] << ", nothing happens!" << std::endl << std::endl;
            }
            // displaying the player's status
            std::cout << currentPlayer.getPlayerName() << ": $" << currentPlayer.getPlayerMoney() << " remaining.\n\n\n";

            // checking if the player is broke 
            if (currentPlayer.getPlayerMoney() <= 0) {
                std::cout << "--------------------------------------------------------" << std::endl;
                std::cout << "Oh no, " << currentPlayer.getPlayerName() << " has run out of money! You lose!" << std::endl;
                std::cout << "--------------------------------------------------------" << std::endl;
                for (int propertyMarkerIterator = 0; propertyMarkerIterator < playerPropertyMarkers.size(); propertyMarkerIterator++) {
                    if (currentPlayer.getPlayerID() == playerPropertyMarkers[propertyMarkerIterator]->getPropertyMarkerPlayerID()){ // if the player owned properties
                        playerPropertyMarkers[propertyMarkerIterator]->propertyOpened(); // alerting the terminal the player marker has been removed from the property space
                        playerPropertyMarkers.erase(playerPropertyMarkers.begin() + propertyMarkerIterator); // removing the player's property marker icons
                    }
                }
                for (int allSpaces = 0; allSpaces < 40; allSpaces++){
                    if (boardSpaces[allSpaces]) { // ensures the board space is a valid pointer
                        Property* propertySpace = dynamic_cast<Property*>(boardSpaces[allSpaces].get());
                        if (propertySpace) { // ensures the pointer points to a property space
                            if (currentPlayer.getPlayerID() == propertySpace->getLandlordID()){
                                propertySpace->setOwned(false); // setting the property space to unowned, now that the player is no longer playing
                                propertySpace->propertyOpened(); // alerting the terminal the property is now available for ownership
                                propertySpace->setLandlord(""); // setting the landlord to be no one
                                propertySpace->setLandlordID(-1); // setting the landlord ID to be no one
                            }
                        }
                    }
                }
                players.erase(players.begin() + currentPlayerIndex); // removing the player from the players vector
                currentPlayerIndex = currentPlayerIndex - 1; // because player was removed, this manipulation keeps the turn counter consistent
            }

            // breaking up the terminal between turns:
            std::cout << "--------------------------------------------------------" << std::endl;

            // check if the player should finish their turn and move to the next player
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();  // move to the next player
            turnCounter = turnCounter + 1; // add to the turn counter
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
            turnCounter = turnCounter + 1; // add to the turn counter
        }
    }
    // end game message:
    Player& lastPlayer = *players.back();
    std::cout << "The game is over, " << lastPlayer.getPlayerName() << " is the last player standing!" << std::endl;
    std::cout << "Congratulations, " << lastPlayer.getPlayerName() << " you won!" << std::endl;
    window.close();
    players.clear(); // removing the player from the players vector
    boardSpaces.clear();  // clearing the vector and destroys all boardSpace objects - double checking!
}
