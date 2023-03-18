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
    MAP_LOADED,
    MAP_VALIDATED,
    PLAYERS_ADDED,
    PLAY,
    ASSIGN_REINFORCEMENT,
    ISSUE_ORDERS,
    EXECUTE_ORDERS,
    CHECK_WIN,
    WIN,
    END
};

class GameEngine {
private:
    int *winner; // id of the winner
    Map* map; // the game map
    vector<Player *> *players; // list of players currently in the game, in order of turns

public:
    void startupPhase(GameEngine *game, CommandProcessor *cp, Command *command, PHASE phase);
    PHASE loadMap(GameEngine *game, PHASE phase, string mapFile);
    PHASE validateMap(GameEngine *game, PHASE phase);

    // Startup
    PHASE addPlayer(GameEngine *game, vector<Player *> *players, string playerName, int playerId);
    PHASE gameStart(GameEngine *game);
    void distributeTerritories(Map *map);
    void determineOrder(GameEngine *game);
    void giveInitialArmies();
    void drawCards();

    // Main Game Loop
    PHASE addPlayers();
    void mainGameLoop(GameEngine *game, PHASE phase); // loops through game phases until win condition is met
    PHASE reinforcementPhase(); // called by mainGameLoop
    PHASE issueOrdersPhase(); // called by mainGameLoop
    PHASE executeOrdersPhase(); // called by mainGameLoop
    PHASE checkWin(); // called by mainGameLoop
    void initGameDummy(); // driver method that creates map, players, etc. for dev purposes
    void initGameEndDummy(); // driver method that inits game with only one player to show win condition

    PHASE win();
    void end();
    GameEngine(); //default constructor
    GameEngine(const GameEngine &copy); //copy constructor
    GameEngine& operator=(const GameEngine& t); //assignment operator
    friend ostream& operator<<(ostream& os, const GameEngine& t);
    ~GameEngine(); //destructor

    // GETTERS AND SETTERS
    vector<Player *> *getPlayers() const;
    void setPlayers(vector<Player *> *players);

    Map *getMap() const;
    void setMap(Map *map);

    //MEMBERS USED IN ORDERS
    static Player* neutral; //neutral player
    static std::unordered_map<string, bool>* peaceStatus; //keeps track of peace status between players
    static vector<int>* conqStatus; //keeps track of conquest status
};

//int string_is_num_in_range(string str, int n, int m);
//void invalidInput();

#endif //WARZONE_GAMEENGINE_H