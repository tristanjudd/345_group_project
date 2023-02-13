#include <iostream>
#include "Map/MapDriver.h"
#include "Cards/CardsDriver.h"
#include "Orders/OrdersDriver.h"
#include "Player/PlayerDriver.h"
#include "GameEngine/GameEngineDriver.h"

int main() {
    std::cout << "Welcome to our bootleg Warzone!" << std::endl;

    mapDriver();  // For now, just goes through the prompt, but we will have to return the map objects here eventually
    cardDriver();
    ordersDriver();
    playerDriver();
    gameEngineDriver();

    return 0;
}
