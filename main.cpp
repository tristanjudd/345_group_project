#include <iostream>
#include "Map/MapDriver.h"
#include "Cards/CardsDriver.h"
#include "Orders/OrdersDriver.h"
#include "Player/PlayerDriver.h"

int main() {
    std::cout << "Welcome to our bootleg Warzone!" << std::endl;

    // Call the map driver
    mapDriver();  // For now, just goes through the prompt, but we will have to return the map objects here eventually
    cardDriver();
    ordersDriver();
    playerDriver();
 

    return 0;
}
