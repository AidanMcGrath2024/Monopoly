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
    {718, 129}, {718, 192}, {718, 255}, {718, 318}, {718, 381}, {718, 444}, {718, 507}, {718, 570}, {718, 633}};

    // initializing all board spaces
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

    // initializing player objects into a vector with a for loop:
    std::vector<std::unique_ptr<Player>> players; // allocating a vector of smart pointers for the player objects
    for (int i = 0; i < 4; ++i) {
        int startingMoney = 1500; // default starting money for Monopoly
        int startingIndex = 0; // all players start on GO
        int startingXposition = boardSpaces[startingIndex].getBoardPositionX(); // extracting the x position of the GO space
        int startingYposition = boardSpaces[startingIndex].getBoardPositionY(); // extracting the y position of the GO space 
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
        players.push_back(std::make_unique<Player>(playerName, startingIndex, startingXposition, startingYposition, startingMoney, playerTexture));
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

        std::string userEntry;
        std::cout << currentPlayer.getPlayerName() << "'s turn. Press 'd' to roll the dice." << std::endl;

        int diceRoll = 0;
        bool validInput = false;
        while (validInput == false) {  
            std::cin >> userEntry;  

            if (userEntry == "d") {
                diceRoll = rollDiceSequence();  
                validInput = true;
            } else {
                std::cout << "Wrong key! Please press the 'd' key to roll the dice." << std::endl;
            }
        }

        // calculate the new player position based on their index and dice roll
        int newIndex = (currentPlayer.getPlayerIndex() + diceRoll) % 40; // 40 spaces on the board
        currentPlayer.setPosition(boardSpaces[newIndex].getBoardPositionX(), boardSpaces[newIndex].getBoardPositionY());
        currentPlayer.setPlayerIndex(newIndex);

        // alerting the terminal that the player moved
        std::cout << currentPlayer.getPlayerName() << " rolled a total of " << diceRoll << ", so they move to " << boardSpaces[newIndex].getSpaceName() << "." << std::endl;

        // displaying the player's status
        std::cout << currentPlayer.getPlayerName() << ": $" << currentPlayer.getPlayerMoney() << " remaining.\n";

        // check if the player should finish their turn and move to the next player
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();  // move to the next player

        // updating the window
        window.clear();
        window.draw(boardSprite);
        window.draw(players[0]->getSprite());
        window.draw(players[1]->getSprite());
        window.draw(players[2]->getSprite());
        window.draw(players[3]->getSprite());
        window.display();
    }
}
