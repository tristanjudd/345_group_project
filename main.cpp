#include <iostream>
#include "Map/MapDriver.h"
#include "Cards/CardsDriver.h"
#include "Orders/OrdersDriver.h"
#include "Player/PlayerDriver.h"
#include "GameLog/LoggingDriver.h"
#include "GameEngine/GameEngineDriver.h"
#include "PlayerStrategies/NeutralDriver.h"
#include "PlayerStrategies/CheaterDriver.h"

int main(int argc, char *argv[]) {
    // -file /home/jay/Projects/345_group_project/CommandProcessing/test.cmd
    //C:\Users\Kojo\OneDrive\Documents\compsci\345\345_group_project\Map\canada.map
    try {
        if (string(argv[1]) == "-console") {
            gameEngineDriver(GAME_MODE::console, "");
        } else if (string(argv[1]) == "-file") {
            gameEngineDriver(GAME_MODE::file, argv[2]);
        } else {
            throw std::runtime_error("Invalid command line arguments.");
        }
    } catch (const std::exception &e) {
        cout << "[ERROR]: " << e.what() << "... Exiting program.";
        return -1;
    }


    //PART2
    //ordersDriver();
    //logDriver(argc, argv);

    //PART3
    //neutralDriver();
    //cheaterDriver();


    return 0;
}
