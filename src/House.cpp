#include "House.h"

House::House(std::string propertyName, int purchasePrice, int rentAmount)
    : propertyName(propertyName),
      purchasePrice(purchasePrice),
      rentAmount(rentAmount),
      numHouses(0),
      hasHotel(false),
      maxHouses(4),
      isOwned(false)
{
    houseCost = purchasePrice / 2;
    hotelCost = houseCost * 5;
}

std::pair<bool, std::string> House::addHouse()
{
    if (hasHotel)
    {
        return std::make_pair(false, "Property already has a hotel");
    }
    if (numHouses >= maxHouses)
    {
        return std::make_pair(false, "Maximum number of houses reached");
    }
    numHouses++;
    return std::make_pair(true, "House added. Now has " + std::to_string(numHouses) + " houses");
}

std::pair<bool, std::string> House::removeHouse()
{
    if (hasHotel)
    {
        return std::make_pair(false, "Cannot remove houses while hotel exists");
    }
    if (numHouses <= 0)
    {
        return std::make_pair(false, "No houses to remove");
    }
    numHouses--;
    return std::make_pair(true, "House removed. Now has " + std::to_string(numHouses) + " houses");
}

std::pair<bool, std::string> House::addHotel()
{
    if (hasHotel)
    {
        return std::make_pair(false, "Hotel already exists");
    }
    if (numHouses < maxHouses)
    {
        return std::make_pair(false, "Need " + std::to_string(maxHouses) + " houses before adding hotel");
    }
    hasHotel = true;
    numHouses = 0;
    return std::make_pair(true, "Hotel added successfully");
}

std::pair<bool, std::string> House::removeHotel()
{
    if (!hasHotel)
    {
        return std::make_pair(false, "No hotel to remove");
    }
    hasHotel = false;
    return std::make_pair(true, "Hotel removed successfully");
}

int House::calculateRent() const
{
    if (hasHotel)
    {
        return rentAmount * 5;
    }
    return rentAmount * (numHouses + 1);
}

std::pair<bool, std::string> House::purchase(const std::string &player)
{
    if (isOwned)
    {
        return std::make_pair(false, "Property already owned");
    }
    owner = player;
    isOwned = true;
    return std::make_pair(true, "Property purchased by " + player);
}

std::pair<bool, std::string> House::transferOwnership(const std::string &currentOwner, const std::string &newOwner)
{
    if (!isOwned)
    {
        return std::make_pair(false, "Property not owned, cannot transfer");
    }
    if (owner != currentOwner)
    {
        return std::make_pair(false, "Only the current owner can transfer the property");
    }
    owner = newOwner;
    return std::make_pair(true, "Property transferred from " + currentOwner + " to " + newOwner);
}

std::map<std::string, std::string> House::getPropertyStatus() const
{
    std::map<std::string, std::string> status;
    status["property_name"] = propertyName;
    status["owner"] = owner;
    status["houses"] = std::to_string(numHouses);
    status["has_hotel"] = hasHotel ? "true" : "false";
    status["current_rent"] = std::to_string(calculateRent());
    status["house_cost"] = std::to_string(houseCost);
    status["hotel_cost"] = std::to_string(hotelCost);
    return status;
}
