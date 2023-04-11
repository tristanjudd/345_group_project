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
#include "../GameLog/LoggingObserver.h"
#include "../PlayerStrategies/PlayerStrategies.h"

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
    CHECK_DRAW,
    DRAW,
    END
};

class GameEngine : public ILoggable, public Subject{
private:
    int *winner; // id of the winner
    Map *map; // the game map
    vector<Player *> *players; // list of players currently in the game, in order of turns
    PHASE *currentPhase;
    int *currentTurn;
    int *maxTurns;

    int loadTournament(string arguments);

public:
    GameEngine(LogObserver* observer); //default constructor
    GameEngine(const GameEngine &copy); //copy constructor
    GameEngine& operator=(const GameEngine& t); //assignment operator
    friend ostream& operator<<(ostream& os, const GameEngine& t);
    ~GameEngine(); //destructor

    // GETTERS AND SETTERS
    int *getWinner() const;
    void setWinner(int *winner);
    Map *getMap() const;
    void setMap(Map *map);
    vector<Player *> *getPlayers() const;
    void setPlayers(vector<Player *> *players);
    PHASE *getCurrentPhase() const;
    void setCurrentPhase(PHASE *currentPhase);
    int *getCurrentTurn() const;
    void setCurrentTurn(int *currentTurn);
    int *getMaxTurns() const;
    void setMaxTurns(int *maxTurns);

    // Startup
    void startupPhase(GameEngine *game, CommandProcessor *cp, Command *command, PHASE phase, LogObserver* observer);
    PHASE loadMap(GameEngine *game, PHASE phase, string mapFile);
    PHASE validateMap(GameEngine *game, PHASE phase);
    PHASE addPlayer(GameEngine *game, string playerName, int playerId, LogObserver* observer);
    PHASE gameStart(GameEngine *game);
    void distributeTerritories(GameEngine *game);
    void determinePlayerOrder(GameEngine *game);
    void giveInitialArmies(GameEngine *game);
    void drawCards(GameEngine *game);

    // Main Game Loop
    void mainGameLoop(GameEngine *game, PHASE phase, LogObserver* observer); // loops through game phases until win condition is met
    PHASE reinforcementPhase(GameEngine *game); // called by mainGameLoop
    PHASE issueOrdersPhase(GameEngine *game, LogObserver* observer); // called by mainGameLoop
    PHASE executeOrdersPhase(); // called by mainGameLoop
    PHASE checkWin(); // called by mainGameLoop
    PHASE checkDraw(GameEngine *game);
    void initGameDummy(LogObserver* observer); // driver method that creates map, players, etc. for dev purposes
    void initGameEndDummy(LogObserver* observer); // driver method that inits game with only one player to show win condition

    PHASE win();
    void end();
    void stringToLog();

    //MEMBERS USED IN ORDERS
    static Player* neutral; //neutral player
    static std::unordered_map<string, bool>* peaceStatus; //keeps track of peace status between players
    static vector<int>* conqStatus; //keeps track of conquest status
};

//int string_is_num_in_range(string str, int n, int m);
//void invalidInput();

#endif //WARZONE_GAMEENGINE_H