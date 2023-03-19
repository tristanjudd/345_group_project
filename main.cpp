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
    //ordersDriver(); //DOES NOT WORK ANYMORE BECAUSE ORDER CLASS IS ABSTRACT
    //playerDriver(); //DOES NOT WORK ANYMORE BECAUSE ORDER CLASS IS ABSTRACT AND ISSUEORDER NOT DEFINE
    //gameEngineDriver();

    //PART2
    ordersDriver();
    
    return 0;
}
