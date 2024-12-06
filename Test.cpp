#include <iostream>
#include <map>
#include <vector>
#include "House.h"

// Structure to track player properties
struct PlayerProperties
{
    std::vector<House *> properties;

    void addProperty(House *property)
    {
        properties.push_back(property);
    }

    int getTotalProperties() const
    {
        return properties.size();
    }

    int getTotalHouses() const
    {
        int total = 0;
        for (const auto &prop : properties)
        {
            total += prop->getNumHouses();
        }
        return total;
    }

    int getTotalRent() const
    {
        int total = 0;
        for (const auto &prop : properties)
        {
            total += prop->calculateRent();
        }
        return total;
    }
};

void printDivider()
{
    std::cout << "\n----------------------------------------\n";
}

void printStatus(const House &property)
{
    std::map<std::string, std::string> status = property.getPropertyStatus();
    std::cout << "\nProperty Status for " << property.getPropertyName() << ":" << std::endl;
    std::cout << "Current Owner: " << (property.getOwner().empty() ? "None" : property.getOwner()) << std::endl;
    for (const auto &item : status)
    {
        std::cout << item.first << ": " << item.second << std::endl;
    }
    printDivider();
}

void printPlayerPortfolio(const std::string &playerName, const PlayerProperties &portfolio)
{
    std::cout << "\nPlayer: " << playerName << std::endl;
    std::cout << "Total Properties Owned: " << portfolio.getTotalProperties() << std::endl;
    std::cout << "Total Houses Built: " << portfolio.getTotalHouses() << std::endl;
    std::cout << "Total Rent Collectible: $" << portfolio.getTotalRent() << std::endl;

    std::cout << "\nOwned Properties:" << std::endl;
    for (const auto &property : portfolio.properties)
    {
        std::cout << "\n"
                  << property->getPropertyName() << ":" << std::endl;
        std::cout << "Houses: " << property->getNumHouses() << std::endl;
        std::cout << "Has Hotel: " << (property->getHasHotel() ? "Yes" : "No") << std::endl;
        std::cout << "Current Rent: $" << property->calculateRent() << std::endl;
    }
    printDivider();
}

void testBasicOperations(House &property, const std::string &player, std::map<std::string, PlayerProperties> &portfolios)
{
    std::cout << "\nTesting Basic Operations for " << property.getPropertyName() << std::endl;

    // Purchase property
    auto result = property.purchase(player);
    std::cout << "Purchase by " << player << ": " << result.second << std::endl;
    if (result.first)
    {
        portfolios[player].addProperty(&property);
    }

    // Test rent at different house levels
    std::cout << "\nRent Calculations:" << std::endl;
    std::cout << "Base rent: $" << property.calculateRent() << std::endl;

    for (int i = 1; i <= 4; i++)
    {
        property.addHouse();
        std::cout << "Rent with " << i << " houses: $" << property.calculateRent() << std::endl;
    }
}

void testHotelOperations(House &property)
{
    std::cout << "\nTesting Hotel Operations for " << property.getPropertyName() << std::endl;

    auto result = property.addHotel();
    std::cout << "Hotel addition attempt: " << result.second << std::endl;

    if (result.first)
    {
        std::cout << "Rent with hotel: $" << property.calculateRent() << std::endl;

        auto houseResult = property.addHouse();
        std::cout << "Attempt to add house with hotel: " << houseResult.second << std::endl;

        auto removeResult = property.removeHotel();
        std::cout << "Hotel removal: " << removeResult.second << std::endl;
    }
}

void testEdgeCases(House &property)
{
    std::cout << "\nTesting Edge Cases for " << property.getPropertyName() << std::endl;

    auto result = property.addHouse();
    std::cout << "Adding extra house: " << result.second << std::endl;

    for (int i = 0; i < 6; i++)
    {
        result = property.removeHouse();
        std::cout << "Removing house attempt " << (i + 1) << ": " << result.second << std::endl;
    }

    result = property.addHotel();
    std::cout << "Adding hotel without houses: " << result.second << std::endl;
}

void testOwnershipTransfer(House &property,
                           const std::string &initialOwner,
                           const std::string &invalidTransferrer,
                           const std::string &newOwner,
                           std::map<std::string, PlayerProperties> &portfolios)
{
    std::cout << "\nTesting Ownership for " << property.getPropertyName() << std::endl;

    std::cout << "Current Owner: " << (property.getOwner().empty() ? "None" : property.getOwner()) << std::endl;
    auto result = property.purchase(initialOwner);
    if (result.first)
    {
        portfolios[initialOwner].addProperty(&property);
    }
    std::cout << "Initial purchase by " << initialOwner << ": " << result.second << std::endl;

    // Test invalid transfer (by non-owner)
    result = property.transferOwnership(invalidTransferrer, newOwner);
    std::cout << "Invalid transfer attempt by " << invalidTransferrer << ": " << result.second << std::endl;

    // Test valid transfer
    result = property.transferOwnership(initialOwner, newOwner);
    if (result.first)
    {
        auto &initialOwnerProps = portfolios[initialOwner].properties;
        initialOwnerProps.erase(
            std::remove(initialOwnerProps.begin(), initialOwnerProps.end(), &property),
            initialOwnerProps.end());
        portfolios[newOwner].addProperty(&property);
    }
    std::cout << "Valid transfer from " << initialOwner << " to " << newOwner << ": " << result.second << std::endl;
}

int main()
{
    // Define player names - easy to modify here
    const std::string player1 = "Lyze";
    const std::string player2 = "Aiden";
    const std::string player3 = "Donovan";

    // Create properties
    House mediterraneanAve("Mediterranean Avenue", 60, 2);
    House balticAve("Baltic Avenue", 60, 4);
    House parkPlace("Park Place", 350, 35);
    House boardwalk("Boardwalk", 400, 50);
    House atlanticAve("Atlantic Avenue", 260, 22);

    // Create player property trackers
    std::map<std::string, PlayerProperties> playerPortfolios;

    // Test Case 1: Initial Property Status
    std::cout << "Test Case 1: Initial Property Status" << std::endl;
    printStatus(mediterraneanAve);
    printStatus(parkPlace);
    printStatus(boardwalk);

    // Test Case 2: Basic Operations and Ownership
    std::cout << "\nTest Case 2: Basic Operations and Ownership" << std::endl;
    testBasicOperations(mediterraneanAve, player1, playerPortfolios);
    testBasicOperations(parkPlace, player2, playerPortfolios);
    testBasicOperations(boardwalk, player3, playerPortfolios);

    // Test Case 3: Player Portfolios After Initial Purchases
    std::cout << "\nTest Case 3: Initial Player Portfolios" << std::endl;
    for (const auto &player : playerPortfolios)
    {
        printPlayerPortfolio(player.first, player.second);
    }

    // Test Case 4: Hotel Operations
    std::cout << "\nTest Case 4: Hotel Operations" << std::endl;
    testHotelOperations(mediterraneanAve);
    testHotelOperations(parkPlace);

    // Test Case 5: Edge Cases
    std::cout << "\nTest Case 5: Edge Cases" << std::endl;
    testEdgeCases(boardwalk);

    // Test Case 6: Ownership Transfers
    std::cout << "\nTest Case 6: Ownership Transfers" << std::endl;
    // Modified testOwnership function call
    testOwnershipTransfer(atlanticAve, player1, player2, player3, playerPortfolios);

    // Test Case 7: Final Portfolio Status
    std::cout << "\nTest Case 7: Final Portfolio Status" << std::endl;
    for (const auto &player : playerPortfolios)
    {
        printPlayerPortfolio(player.first, player.second);
    }

    // Test Case 8: Final Property Status
    std::cout << "\nTest Case 8: Final Property Status" << std::endl;
    printStatus(mediterraneanAve);
    printStatus(parkPlace);
    printStatus(boardwalk);
    printStatus(atlanticAve);

    return 0;
}