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
using std::find;

#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"

class Command; //forward declaration
class CommandProcessor; //forward declaration
class Map; //forward declaration

//enum of phases
enum PHASE {
    START,
    LOAD_MAP,
    MAP_LOADED,
    MAP_VALIDATED,
    PLAYERS_ADDED,
    PLAY,
    ASSIGN_REINFORCEMENT,
    ISSUE_ORDERS,
    EXECUTE_ORDERS,
    WIN,
    ENDSTARTUP
};

class GameEngine {
private:
    int *winner; // id of the winner
    vector<Player *> *players; // list of players currently in the game, in order of turns
    Map* map; // the game map
    vector<Player *> *playersStartup = new vector<Player *>();

public:
    void startupPhase(GameEngine *game, CommandProcessor *cp, Command *command, PHASE phase, Map *map);
    PHASE start();
    PHASE loadMap(GameEngine *game, PHASE phase, string mapFile);
    PHASE validateMap(GameEngine *game, PHASE phase);
    PHASE addPlayers();
    PHASE addPlayer(GameEngine *game, vector<Player *> *playersStartup, string playerName, int playerId);
    PHASE gameStart(GameEngine *game);
    void distributeTerritories(Map *map);
    void determineOrder(GameEngine *game);
    void giveInitialArmies();
    void drawCards();
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

    // GETTERS AND SETTERS
    vector<Player *> *getPlayersStartup() const;
    void setPlayersStartup(vector<Player *> *playersStartup);

    Map *getMap() const;
    void setMap(Map *map);

    // START OF ASSIGNMENT 2
    PHASE mainGameLoop(); // loops through game phases until win condition is met
    PHASE reinforcementPhase(); // called by mainGameLoop
    PHASE issueOrdersPhase(); // called by mainGameLoop
    PHASE executeOrdersPhase(); // called by mainGameLoop
    void initGameDummy(); // driver method that creates map, players, etc. for dev purposes
    void initGameEndDummy(); // driver method that inits game with only one player to show win condition

    //MEMBERS USED IN ORDERS
    static Player* neutral; //neutral player
    static std::unordered_map<string, bool>* peaceStatus; //keeps track of peace status between players
    static vector<int>* conqStatus; //keeps track of conquest status
};

//int string_is_num_in_range(string str, int n, int m);
//void invalidInput();

#endif //WARZONE_GAMEENGINE_H