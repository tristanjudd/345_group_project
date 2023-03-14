#include <iostream>
#include "Map/MapDriver.h"
#include "Cards/CardsDriver.h"
#include "Orders/OrdersDriver.h"
#include "Player/PlayerDriver.h"
#include "GameEngine/GameEngineDriver.h"

int main() {
    std::cout << "Welcome to our bootleg Warzone!" << std::endl;

    //PART1
    //mapDriver();  // For now, just goes through the prompt, but we will have to return the map objects here eventually
    //cardDriver();
    //ordersDriver(); //DOES NOT WORK ANYMORE SINCE ORDER IS NOW AN ABSTRACT CLASS
    //playerDriver(); //DOES NOT WORK ANYMORE SINCE ORDER IS NOW AN ABSTRACT CLASS and issue order is not defined
    gameEngineDriver();

    //PART2

    return 0;
}
