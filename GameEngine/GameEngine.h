#ifndef WARZONE_GAMEENGINE_H
#define WARZONE_GAMEENGINE_H

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::ostream;

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
    GameEngine(); //default constructor
    GameEngine(const GameEngine &copy); //copy constructor
    GameEngine& operator=(const GameEngine& t); //assignment operator
    friend ostream& operator<<(ostream& os, const GameEngine& t);
    ~GameEngine(); //destructor

    // START OF ASSIGNMENT 2
    void mainGameLoop(); // loops through game phases until win condition is met
    void reinforcementPhase(); // called by mainGameLoop
    void issueOrdersPhase(); // called by mainGameLoop
    void executeOrdersPhase(); // called by mainGameLoop

};

#endif //WARZONE_GAMEENGINE_H
