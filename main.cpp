#include <iostream>
#include "Map/MapDriver.h"
#include "Cards/CardsDriver.h"
#include "Orders/OrdersDriver.h"
#include "Player/PlayerDriver.h"
#include "GameLog/LoggingDriver.h"
#include "GameEngine/GameEngineDriver.h"

int main(int argc, char *argv[]) {
    std::cout << "Welcome to our bootleg Warzone!" << std::endl;

    //PART1
    //mapDriver();  // For now, just goes through the prompt, but we will have to return the map objects here eventually
    //cardDriver();
    //ordersDriver(); //DOES NOT WORK ANYMORE BECAUSE ORDER CLASS IS ABSTRACT
    //playerDriver(); //DOES NOT WORK ANYMORE BECAUSE ORDER CLASS IS ABSTRACT AND ISSUEORDER NOT DEFINE

    // -file /home/jay/Projects/345_group_project/CommandProcessing/test.cmd
    try {
        if (string(argv[1]) == "-console") {
            gameEngineDriver(GAME_MODE::console, "");
        } else if (string(argv[1]) == "-file"){
            gameEngineDriver(GAME_MODE::file, argv[2]);
        } else {
            throw std::runtime_error("Invalid command line arguments.");
        }
    } catch (const std::exception& e) {
        cout << "[ERROR]: " << e.what() << "... Exiting program.";
        return -1;
    }

    //PART2
    //logDriver(string(argv[1], string(argv[2]);
    return 0;
}
