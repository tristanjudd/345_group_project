#ifndef WARZONE_GAMEENGINE_H
#define WARZONE_GAMEENGINE_H

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::cin;

//enum of phases
enum PHASE {
    START,
    MAP_LOADED,
    MAP_VALIDATED,
    PLAYERS_ADDED,
    ASSIGN_REINFORCEMENT,
    ISSUE_ORDERS,
    EXECUTE_ORDERS,
    WIN,
    END
};

class GameEngine {
private:
    int *winner; // id of the winner
public:
    PHASE start();
    PHASE loadMap();
    PHASE validateMap();
    PHASE addPlayers();
    PHASE assignReinforcements();
    PHASE issueOrders();
    PHASE executeOrders();
    PHASE win();
    void end();
};

#endif //WARZONE_GAMEENGINE_H
