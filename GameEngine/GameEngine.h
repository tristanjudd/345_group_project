#ifndef WARZONE_GAMEENGINE_H
#define WARZONE_GAMEENGINE_H

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::ostream;

#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"

//enum of phases
enum PHASE {
    START,
    MAP_LOADED,
    MAP_VALIDATED,
    PLAYERS_ADDED,
    PLAY,
    ASSIGN_REINFORCEMENT,
    ISSUE_ORDERS,
    EXECUTE_ORDERS,
    WIN,
    END
};

class GameEngine {
private:
    int *winner; // id of the winner
    vector<Player *> *players; // list of players currently in the game, in order of turns
    int* currentPlayer; // keeps track of the current player

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
    PHASE mainGameLoop(); // loops through game phases until win condition is met
    PHASE reinforcementPhase(); // called by mainGameLoop
    PHASE issueOrdersPhase(); // called by mainGameLoop
    PHASE executeOrdersPhase(); // called by mainGameLoop

    //MEMBERS USED IN ORDERS
    static Player* neutral; //neutral player
    static std::unordered_map<string, bool>* peaceStatus; //keeps track of peace status between players
    static vector<int>* conqStatus; //keeps track of conquest status
};

int string_is_num_in_range(string str, int n, int m);

#endif //WARZONE_GAMEENGINE_H