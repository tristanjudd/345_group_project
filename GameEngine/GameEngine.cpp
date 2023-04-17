#include "GameEngine.h"
#include "../CommandProcessing/CommandProcessing.h"

#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;
using std::ofstream;
using std::stringstream;

Player *GameEngine::neutral = new Player(-1); //CREATING THE STATIC NEUTRAL PLAYER ID = -1
std::unordered_map<string, bool> *GameEngine::peaceStatus = new std::unordered_map<string, bool>(); //CREATING THE STATIC PEACE STATUS MAP
vector<int> *GameEngine::conqStatus = new vector<int>(); //CREATING THE STATIC CONQUERED STATUS VECTOR

//default constructor
GameEngine::GameEngine(LogObserver *observer) : Subject(observer) {
    cout << "GameEngine default constructor called" << endl;
    winner = new int(-1);
    map = new Map();
    players = new vector<Player *>;
    currentTurn = new int(0);
    maxTurns = new int(50); //default max turns is 50
}

//copy constructor
GameEngine::GameEngine(const GameEngine &gameEngine) {
    cout << "GameEngine copy constructor called" << endl;
    winner = new int(*gameEngine.winner);
    map = gameEngine.map;
    players = gameEngine.players;
    currentTurn = gameEngine.currentTurn;
    maxTurns = gameEngine.maxTurns;
}

//assignment operator
GameEngine &GameEngine::operator=(const GameEngine &gameEngine) {
    cout << "GameEngine assignment operator called" << endl;
    if (this != &gameEngine) {
        delete this->winner;
        this->winner = new int(*gameEngine.winner);
        this->map = gameEngine.map;
        this->players = gameEngine.players;
        this->currentTurn = gameEngine.currentTurn;
        this->maxTurns = gameEngine.maxTurns;
    }
    return *this;
}

//ostream operator
ostream &operator<<(ostream &out, const GameEngine &gameEngine) {
    out << "GameEngine: " << endl;
    out << "Winner: " << *gameEngine.winner << endl;
    out << "Map: " << *gameEngine.map << endl;
    out << "Players: " << endl;
    for (auto &player: *gameEngine.players) {
        out << *player << endl;
    }
    out << "Current turn: " << *gameEngine.currentTurn << endl;
    out << "Max turns" << gameEngine.maxTurns << endl;
    return out;
}

//destructor
GameEngine::~GameEngine() {
    cout << "GameEngine destructor called" << endl;
    winner = nullptr;
    map = nullptr;
    players = nullptr;
    currentTurn = nullptr;
    maxTurns = nullptr;
    delete winner;
    delete map;
    delete players;
    delete currentTurn;
    delete maxTurns;

    delete neutral;
    delete peaceStatus;
    delete conqStatus;
}

//Getters and setters
int *GameEngine::getWinner() const {
    return winner;
}

void GameEngine::setWinner(int *winner) {
    GameEngine::winner = winner;
}

Map *GameEngine::getMap() const {
    return map;
}

void GameEngine::setMap(Map *map) {
    GameEngine::map = map;
}

vector<Player *> *GameEngine::getPlayers() const {
    return players;
}

void GameEngine::setPlayers(vector<Player *> *players) {
    GameEngine::players = players;
}

PHASE *GameEngine::getCurrentPhase() const {
    return currentPhase;
}

void GameEngine::setCurrentPhase(PHASE *currentPhase) {
    GameEngine::currentPhase = currentPhase;
}

int *GameEngine::getCurrentTurn() const {
    return currentTurn;
}

void GameEngine::setCurrentTurn(int *currentTurn) {
    GameEngine::currentTurn = currentTurn;
}

int *GameEngine::getMaxTurns() const {
    return maxTurns;
}

void GameEngine::setMaxTurns(int *maxTurns) {
    GameEngine::maxTurns = maxTurns;
}

// Startup
void
GameEngine::startupPhase(GameEngine *game, CommandProcessor *cp, Command *command, PHASE phase, LogObserver *observer) {
    cout << "Welcome to our bootleg Warzone!" << endl;
    int playerId = 0;
    string mapFile;
    int maxTurnsInt = 0;
    while (maxTurnsInt != -1) {
        switch (phase) {
            case START: {
                cout << "Start state" << endl;
                // will prompt user, and should not pass for anything other than 'loadmap <mapfile>' (in this phase)
                // also accepts tournament command!
                int numGames = 0;
                int numMaps = 0;
                command = cp->getCommand(phase, cp, observer);
                cout << *command << endl;  // just to show I did my part
                if (*command->getName() == COMMAND::loadmap) {
                    mapFile = *command->getArgument();
                    phase = loadMap(game, phase, mapFile);
                } else if (*command->getName() == COMMAND::tournament) {
                    maxTurnsInt = loadTournament(*command->getArgument()); //get maxTurns
                    if (maxTurnsInt == -1) {
                        cout << "Tournament command invalid. Please try again!" << endl;
                        break;
                    }
                    // set numGames to the number of files in the map0 folder in tournament
                    for (const auto &gameFile: fs::directory_iterator("tournament/map0")) {
                        numGames++;
                    }
                    game->setMaxTurns(&maxTurnsInt);
                    auto *winners = new vector<string>(); //vector of winners
                    for (const auto &mapFolder: fs::directory_iterator(
                            "tournament")) { //loop through all the map folders
                        if (mapFolder.is_directory()) {
                            cout << mapFolder.path() << endl;
                            for (const auto &gameFile: fs::directory_iterator(
                                    mapFolder.path())) { //loop through all the game files
                                if (gameFile.is_regular_file()) {
                                    cout << gameFile.path() << endl;
                                    //create a new game
                                    GameEngine *gameT = new GameEngine(observer);
                                    CommandProcessor *cpT = new FileCommandProcessorAdapter(gameFile.path().string(),
                                                                                            observer);
                                    Command *commandT = new Command();
                                    PHASE phaseT = START;
                                    gameT->setMaxTurns(game->getMaxTurns());

                                    //run the startup and read the commands from the file
                                    gameT->startupPhase(gameT, cpT, commandT, phaseT, observer);

                                    //run the main game loop
                                    phaseT = ASSIGN_REINFORCEMENT;
                                    gameT->mainGameLoop(gameT, phaseT, observer);

                                    //check who won
                                    if (*gameT->getWinner() == -2) {
                                        winners->push_back("Draw");
                                    } else {
                                        winners->push_back(*gameT->getPlayers()->at(0)->getName());
                                    }
                                }
                            }
                        }
                        numMaps++;
                    }

                    //print out the result in a matrix format where Game num is column name and map num is row name then the winner is the value
                    stringToLogTournament(numGames, numMaps, winners);
                    cout << "Results: " << endl << "\t";
                    for (int i = 0; i < numGames; i++) {
                        cout << "Game " << i + 1 << "\t";
                    }
                    cout << endl;
                    for (int i = 0; i < numMaps; i++) {
                        cout << "Map " << i + 1 << ":  ";
                        for (int j = 0; j < numGames; j++) {
                            cout << winners->at(i) << " ";
                        }
                        cout << endl;
                    }
                    return;
                }
                break;
            }
            case MAP_LOADED: {
                cout << "\nMap loaded state" << endl;
                command = cp->getCommand(phase, cp, observer);

                cout << *command << endl;
                if (*command->getName() == COMMAND::validatemap) {
                    phase = validateMap(game, phase);
                    break;
                } else if (*command->getName() == COMMAND::loadmap) {
                    mapFile = *command->getArgument();
                    phase = loadMap(game, phase, mapFile);
                    break;
                }
            }
            case MAP_VALIDATED: {
                cout << "\nMap validated state" << endl;
                command = cp->getCommand(phase, cp, observer);
                cout << *command << endl;
                playerId = 0;
                if (*command->getName() == COMMAND::addplayer) {
                    phase = addPlayer(game, *command->getArgument(), playerId, observer);
                    playerId = playerId + 1;
                    break;
                }
                break;
            }
            case PLAYERS_ADDED: {
                cout << "Players added state" << endl;
                command = cp->getCommand(phase, cp, observer);
                cout << *command << endl;
                if (*command->getName() == COMMAND::gamestart) {
                    if (game->getPlayers()->size() < 2) {
                        cout << "Not enough players to start the game" << endl;
                        continue;
                    } else if (game->getPlayers()->size() > 6) {
                        cout << "Too many players to start the game" << endl;
                        cout << "Restart :(" << endl;
                        phase = START;
                    } else {
                        phase = PLAY;
                    }
                    break;
                } else if (*command->getName() == COMMAND::addplayer) {
                    if (game->getPlayers()->size() >= 6) {
                        cout << "Too many players to start the game" << endl;
                        cout << "Restart player creation :(" << endl << endl;
                        //reset players
                        game->getPlayers()->clear();
                        phase = MAP_VALIDATED;
                    } else {
                        phase = addPlayer(game, *command->getArgument(), playerId, observer);
                        playerId = playerId + 1;
                    }
                    break;
                }
                break;
            }
            case PLAY:
                cout << "Gamestart phase" << endl;
                phase = game->gameStart(game);
                break;
            case END: {
                cout << "End Phase" << endl;
                game->end();
                return;
            }
            default: {
                cout << "Invalid phase" << endl;
                break;
            }
        }
    }

    setCurrentPhase(&phase);
    Notify(this);
}

void GameEngine::stringToLogTournament(int numGames, int numMaps, vector<std::string> *winners) {
    //creating file string
    string filename = "../Log/gamelog.txt";
    ofstream outputFile;

    //checking if file exists
    ifstream exists(filename);

    if (exists.bad()) {
        outputFile.open(filename);
    }

    // Append data to the file
    outputFile.open(filename, std::ios_base::app);

    //print out the result in a matrix format where Game num is column name and map num is row name then the winner is the value
    outputFile << endl << "Results: " << endl << "\t";
    for (int i = 0; i < numGames; i++) {
        outputFile << "Game " << i + 1 << "\t";
    }
    outputFile << endl;
    for (int i = 0; i < numMaps; i++) {
        outputFile << "Map " << i + 1 << ":  ";
        for (int j = 0; j < numGames; j++) {
            outputFile << winners->at(i) << " ";
        }
        outputFile << endl << endl;
    }

    outputFile.close();
}

//Load map method
PHASE GameEngine::loadMap(GameEngine *game, PHASE phase, string mapFile) {
    cout << "Load Map Method" << endl;
    if (MapLoader::loadMap(game, &mapFile)) {
        cout << *game->getMap() << endl;
        cout << *game->getMap()->getName() << " map loaded" << endl;
        phase = MAP_LOADED;
    } else { // restart if map not loaded
        cout << "Map not loaded \n" << endl;
        phase = START;
    }

    setCurrentPhase(&phase);
    Notify(this);
    return phase;
}

//Validate map method
PHASE GameEngine::validateMap(GameEngine *game, PHASE phase) {
    cout << "Validating map..." << endl;
    if (game->getMap()->validate()) {
        cout << "Map validated" << endl;
        phase = MAP_VALIDATED;
    } else { // restart if map not valid
        cout << "Map invalid" << endl;
        phase = START;
    }

    setCurrentPhase(&phase);
    Notify(this);
    return phase;
}

// Add player method
PHASE GameEngine::addPlayer(GameEngine *game, string playerName, int playerId, LogObserver *observer) {
    Player *newPlayer = new Player(playerName, playerId, observer); //create new player
    vector<Player *> *players = game->getPlayers();
    players->push_back(newPlayer); //add player to vector of players
    cout << "Player " << *newPlayer->getName() << " added" << endl;
    cout << "Num of players: " << players->size() << endl << endl;
    game->setPlayers(players);

    // if the new player name startswith any of the valid strategies assign that strategy, else Human
    if (playerName.starts_with("aggressive")) {
        newPlayer->setStrategy(new Aggressive(newPlayer));
    } else if (playerName.starts_with("benevolent")) {
        newPlayer->setStrategy(new Benevolent(newPlayer));
    } else if (playerName.starts_with("neutral")) {
        newPlayer->setStrategy(new Neutral(newPlayer));
    } else if (playerName.starts_with("cheater")) {
        newPlayer->setStrategy(new Cheater(newPlayer));
    } else {
        newPlayer->setStrategy(new Human(newPlayer));
    }

    PHASE p = PLAYERS_ADDED;
    setCurrentPhase(&p);
    Notify(this);
    return p;
}

// Game start method
PHASE GameEngine::gameStart(GameEngine *game) {
    distributeTerritories(game);
    determinePlayerOrder(game);
    giveInitialArmies(game);
    drawCards(game);

    PHASE p = END;
    setCurrentPhase(&p);
    Notify(this);
    return p;
}

// Distribute territories method
void GameEngine::distributeTerritories(GameEngine *game) {
    cout << "Distributing territories..." << endl;
    vector<Territory *> *territories = game->getMap()->getTerritories();
    int numPlayers = game->getPlayers()->size();
    int numTerritories = territories->size();
    int territoriesPerPlayer = numTerritories / numPlayers;
    int remainderTerritories = numTerritories % numPlayers;

    //distribute all the territories to the players and set owner of territory
    for (int i = 0; i < numPlayers; i++) {
        vector<Territory *> *territoriesForPlayers = game->getPlayers()->at(i)->getPlayerTerritories();
        for (int j = 0; j < territoriesPerPlayer; j++) {
            territoriesForPlayers->push_back(territories->at(i * territoriesPerPlayer + j)); //add territory to player
            territories->at(i * territoriesPerPlayer + j)->setOwner(game->getPlayers()->at(i)); //set owner of territory
        }
        game->getPlayers()->at(i)->setPlayerTerritories(territoriesForPlayers);
    }
    //distribute the remainder of the territories to the players and set owner of territory
    for (int i = 0; i < remainderTerritories; i++) {
        game->getPlayers()->at(i)->getPlayerTerritories()->push_back(
                territories->at(i + numPlayers * territoriesPerPlayer)); //add territory to player
        territories->at(i + numPlayers * territoriesPerPlayer)->setOwner(players->at(i)); //set owner of territory
    }
    //print out territories of players
    for (int i = 0; i < game->getPlayers()->size(); i++) {
        cout << "\nPlayer " << *game->getPlayers()->at(i)->getName() << " has territories: " << endl;
        vector<Territory *> *tempTerritories = game->getPlayers()->at(i)->getPlayerTerritories();
        for (int j = 0; j < tempTerritories->size(); j++) {
            cout << *tempTerritories->at(j)->getTerritoryName() << endl;
        }
        tempTerritories = nullptr;
    }
}

// Determine player order method
void GameEngine::determinePlayerOrder(GameEngine *game) {
    cout << "\nDetermining order of players..." << endl;
    vector<Player *> *players = getPlayers();
    vector<Player *> *playersOrder = new vector<Player *>();
    int numPlayers = players->size();
    int randomNum;
    while (playersOrder->size() < numPlayers) {
        randomNum = rand() % numPlayers;
        if (find(playersOrder->begin(), playersOrder->end(), players->at(randomNum)) == playersOrder->end()) {
            playersOrder->push_back(players->at(randomNum));
        }
    }
    game->setPlayers(playersOrder);
    delete players;
    players = playersOrder;
    for (int i = 0; i < players->size(); i++) {
        cout << "Player " << *players->at(i)->getName() << " is player " << i + 1 << endl;
    }
}

// Give initial armies method
void GameEngine::giveInitialArmies(GameEngine *game) {
    //give initial armies of 50 to each player
    cout << "\nGiving initial armies..." << endl;
    for (int i = 0; i < game->getPlayers()->size(); i++) {
        game->getPlayers()->at(i)->setReinforcements(50);
        cout << "Player " << *game->getPlayers()->at(i)->getName() << " has "
             << game->getPlayers()->at(i)->getReinforcements()
             << " armies" << endl;
    }
}

// Draw cards method
void GameEngine::drawCards(GameEngine *game) {
    cout << "\nDrawing cards for players..." << endl;
    Deck *deck = new Deck();
    for (int i = 0; i < game->getPlayers()->size(); i++) {
        Hand *hand = new Hand();
        hand->insert(deck->draw());
        hand->insert(deck->draw());
        game->getPlayers()->at(i)->setHand(hand);
    }
    //print hand of players
    for (int i = 0; i < game->getPlayers()->size(); i++) {
        cout << "Player " << *game->getPlayers()->at(i)->getName() << " has "
             << game->getPlayers()->at(i)->getHand()->size()
             << " cards" << endl;
    }

}

//Win phase
PHASE GameEngine::win() {
    cout << "Player " << *(players->at(0)->getId()) << " wins!" << endl;
    cout << "Game Over" << endl;
    while (true) {
        cout << "Play again? (y/n): ";
        string playAgain;
        cin >> playAgain;
        if (playAgain == "y") {

            return START; //go to start phase
        } else if (playAgain == "n") {
            cout << "Goodbye!" << endl;
            return END; //go to end phase
        }
        cout << "Invalid input" << endl << "Try again" << endl;
    }
}

//End phase
void GameEngine::end() {
    cout << "Bye Bye" << endl;
}

// Start of new turn
void GameEngine::mainGameLoop(GameEngine *game, PHASE phase, LogObserver *observer) {
    while (true) {
        switch (phase) {
            case ASSIGN_REINFORCEMENT: {
                cout << "Assign reinforcement state" << endl;
                phase = game->reinforcementPhase(game);
                break;
            }
            case ISSUE_ORDERS: {
                cout << "Issue orders state" << endl;
                phase = game->issueOrdersPhase(game, observer);
                break;
            }
            case EXECUTE_ORDERS: {
                cout << "Execute orders state" << endl;
                phase = game->executeOrdersPhase();
                break;
            }
            case CHECK_WIN: {
                cout << "Check victory state" << endl;
                phase = game->checkWin();
                break;
            }
            case WIN:
                cout << "Win Phase" << endl;
                // phase = game->win();
                game->setWinner(game->getPlayers()->at(0)->getId());
                phase = END;
                break;
            case CHECK_DRAW: {
                cout << "Check draw state" << endl;
                phase = game->checkDraw(game);
                break;
            }
            case DRAW: {
                cout << "Draw state" << endl;
                int *draw = new int(-2);
                game->setWinner(draw);
                phase = END;
                break;
            }
            case END:
                cout << "End Phase" << endl;
                game->end();
                return;
            default:
                cout << "Invalid phase" << endl;
                break;
        }
    }
}

//Assign reinforcement phase
PHASE GameEngine::reinforcementPhase(GameEngine *game) {
    cout << "Assigning reinforcements to all players..." << endl;

    // loop through all current players and assign reinforcements based on game logic
    for (Player *player: *game->getPlayers()) {
        // get current player's territories
        vector<Territory *> playerTerritories = *(player->getPlayerTerritories());

        // Assign troops based on game criteria
        int newTroops = 3; // minimum new troops

        // Add bonus of player's territories divided by 3, rounded down
        newTroops += playerTerritories.size() / 3;

        // Add continent bonus
        // loop through all continents
        for (Continent *c: *(game->getMap()->getContinents())) {
            // get all member territories of continent
            vector<Territory *> conts = *(c->getTerritoriesInContinent());

            int matches = 0;
            // for each territory in continent, check if it's also in player's territories
            // if so, increment matches
            for (Territory *t: conts) {
                if (std::find(playerTerritories.begin(), playerTerritories.end(), t) != playerTerritories.end()) {
                    matches++;
                }
            }

            // if matches == size of continent territories, player has whole continent
            if (matches == conts.size()) {
                newTroops += 5;
            }
        }
        // Update player's reinforcement pool
        player->setReinforcements(newTroops);
    }
    cout << "Reinforcements assigned.\n" << endl;

    PHASE p = ISSUE_ORDERS;
    setCurrentPhase(&p);
    Notify(this);
    return p;
}

//Issue orders phase
PHASE GameEngine::issueOrdersPhase(GameEngine *game, LogObserver *observer) {

// loop through each player and call issueOrder method
    for (Player *player: *game->getPlayers()) {
        cout << "PLAYER " << *(player->getId()) << " ISSUING ORDERS" << endl;
        bool stillPlaying = true;

        while (stillPlaying) {
            // issue order method returns a bool
            // it will return true for any move except when
            // player selects the end turn choice
            stillPlaying = player->issueOrder(observer);
        }
    }
    PHASE p = EXECUTE_ORDERS;
    setCurrentPhase(&p);
    Notify(this);
    return p;
}

//Execute orders phase
PHASE GameEngine::executeOrdersPhase() {

    // pointer to current player's order list
    vector<Order *> *currentOrderList;

    // flags for deploy order and other order round-robin logic
    // initially set to true so we can enter loop
    bool deployFlag = true;
    bool orderFlag = true;

    // while there are deploy orders left to execute
    while (deployFlag) {
        // set to false immediately, if anyone executes a deploy order it will be set to true
        deployFlag = false;

        // go through all players and get order at top of list
        for (Player *player: *players) {
            // get list of orders
            currentOrderList = player->getOrders()->getList();

            // if there is an order to execute
            if (!currentOrderList->empty()) {
                Order *toExecute = currentOrderList->at(0);


                //check if to execute is a deploy order
                bool isDeploy = false;
                if (typeid(toExecute).name() == typeid(Deploy).name()) {
                    isDeploy = true;
                }

                // if it's a deploy order execute it and remove from order list
                if (isDeploy) {
                    toExecute->execute();
                    currentOrderList->erase(currentOrderList->begin());
                    // set falg to true as there was a deploy order this round
                    deployFlag = true;
                }

            } // end if order list not empty

        } // end Player for
    } // end while deployFlag

    // while there are still other orders to execute
    while (orderFlag) {
        // set flag to false immediately, will be set to true if someone executes an order
        orderFlag = false;

        // go through all players and get first order in list
        for (Player *player: *players) {
            // get order list
            currentOrderList = player->getOrders()->getList();

            // if order list is not empty execute order and remove it from list
            if (!currentOrderList->empty()) {
                currentOrderList->at(0)->execute();
                currentOrderList->erase(currentOrderList->begin());
                // set flag to true because there may still be orders left
                orderFlag = true;

            } // end if order list not empty

        } // end Player for
    } // end while deployFlag

    //clear peaceStatus and conqStatus
    peaceStatus->clear();
    conqStatus->clear();

    PHASE p = CHECK_WIN;
    setCurrentPhase(&p);
    Notify(this);
    return p;
}

PHASE GameEngine::checkWin() {
    cout << "There are " << players->size() << " players" << endl;

    // iterate through players and check if any has 0 territories
    std::vector<Player *>::iterator it;
    int i = 0;
    for (it = players->begin(); it != players->end();) {
        if ((*it)->getPlayerTerritories()->size() == 0) {
            it = players->erase(it);
        } else {
            it++;
        }
    }

    cout << "There are " << players->size() << " players" << endl;

    // check if there's a winner
    if (players->size() == 1) {
        return WIN;
    }
    return CHECK_DRAW;
}

PHASE GameEngine::checkDraw(GameEngine *game) {
    int *tempCurrentTurn = new int(*game->getCurrentTurn() + 1);
    game->setCurrentTurn(tempCurrentTurn);
    cout << "Turn: " << *game->getCurrentTurn() << endl;
    if (*game->getCurrentTurn() == *game->getMaxTurns()) {
        return DRAW;
    }
    return ASSIGN_REINFORCEMENT;
}

// inits a bunch of objects to have something to test with in dev phase
void GameEngine::initGameDummy(LogObserver *observer) {
    // DUMMY CODE adding players for dev purposes
    Territory *t1 = new Territory(1, 1, "A");
    Territory *t2 = new Territory(2, 1, "B");
    Territory *t3 = new Territory(3, 1, "C");
    Territory *t4 = new Territory(4, 1, "D");
    Territory *t5 = new Territory(5, 1, "E");
    Territory *t6 = new Territory(6, 1, "F");
    Territory *t7 = new Territory(7, 1, "G");
    Territory *t8 = new Territory(8, 1, "H");
    Territory *t9 = new Territory(9, 1, "I");

    vector<Territory *> *borders1 = new vector<Territory *>;
    borders1->push_back(t2);
    borders1->push_back(t4);
    t1->testSetBorders(borders1);

    vector<Territory *> *borders2 = new vector<Territory *>;
    borders2->push_back(t1);
    borders2->push_back(t3);
    borders2->push_back(t5);
    t2->testSetBorders(borders2);

    vector<Territory *> *borders3 = new vector<Territory *>;
    borders3->push_back(t2);
    borders3->push_back(t6);
    t3->testSetBorders(borders3);

    vector<Territory *> *borders4 = new vector<Territory *>;
    borders4->push_back(t1);
    borders4->push_back(t5);
    borders4->push_back(t7);
    t4->testSetBorders(borders4);

    vector<Territory *> *borders5 = new vector<Territory *>;
    borders5->push_back(t2);
    borders5->push_back(t4);
    borders5->push_back(t6);
    borders5->push_back(t8);
    t5->testSetBorders(borders5);

    vector<Territory *> *borders6 = new vector<Territory *>;
    borders6->push_back(t3);
    borders6->push_back(t5);
    borders6->push_back(t9);
    t6->testSetBorders(borders6);

    vector<Territory *> *borders7 = new vector<Territory *>;
    borders7->push_back(t4);
    borders7->push_back(t8);
    t7->testSetBorders(borders7);

    vector<Territory *> *borders8 = new vector<Territory *>;
    borders8->push_back(t5);
    borders8->push_back(t7);
    borders8->push_back(t9);
    t8->testSetBorders(borders8);

    vector<Territory *> *borders9 = new vector<Territory *>;
    borders9->push_back(t6);
    borders9->push_back(t8);
    t9->testSetBorders(borders9);

    vector<Territory *> *list1 = new vector<Territory *>;
    list1->push_back(t1);
    list1->push_back(t2);
    list1->push_back(t3);
    vector<Territory *> *list2 = new vector<Territory *>;
    list2->push_back(t4);
    list2->push_back(t5);
    list2->push_back(t6);
    vector<Territory *> *list3 = new vector<Territory *>;
    list3->push_back(t7);
    list3->push_back(t8);
    list3->push_back(t9);

    Human *strat1 = new Human();
    Player *p1 = new Player(observer, strat1);
    int *id1 = new int;
    *id1 = 1;
    p1->setId(id1);
    p1->setPlayerTerritories(list1);
    for (Territory *t: *list1) {
        t->setOwner(p1);
    }

    Human *strat2 = new Human();
    Player *p2 = new Player(observer, strat2);
    int *id2 = new int;
    *id2 = 2;
    p2->setId(id2);
    p2->setPlayerTerritories(list2);
    for (Territory *t: *list2) {
        t->setOwner(p2);
    }

    Human *strat3 = new Human();
    Player *p3 = new Player(observer, strat3);
    int *id3 = new int;
    *id3 = 3;
    p3->setId(id3);
    p3->setPlayerTerritories(list3);
    for (Territory *t: *list3) {
        t->setOwner(p3);
    }

    Player *p4 = new Player(observer);


    Deck *deck = new Deck();
    Hand *h1 = new Hand();
    Hand *h2 = new Hand();
    Hand *h3 = new Hand();

    Card *c1 = new Card(deck, static_cast<CardType>(0));
    Card *c2 = new Card(deck, static_cast<CardType>(1));
    Card *c3 = new Card(deck, static_cast<CardType>(2));
    Card *c4 = new Card(deck, static_cast<CardType>(3));
    Card *c5 = new Card(deck, static_cast<CardType>(4));

    h1->insert(c1);
    h1->insert(c2);
    h1->insert(c3);
    h1->insert(c4);
    h1->insert(c5);

    p1->setHand(h1);
    h2->insert(deck->draw());
    h2->insert(deck->draw());
    p2->setHand(h2);
    h3->insert(deck->draw());
    h3->insert(deck->draw());
    p2->setHand(h3);


    players->push_back(p1);
    players->push_back(p2);
    players->push_back(p3);
    players->push_back(p4);

    vector<Territory *> *mapList = new vector<Territory *>;
    mapList->push_back(t1);
    mapList->push_back(t2);
    mapList->push_back(t3);
    mapList->push_back(t4);
    mapList->push_back(t5);
    mapList->push_back(t6);
    mapList->push_back(t7);
    mapList->push_back(t8);
    mapList->push_back(t9);
    // create map for dev purposes
    map = new Map();
    //
    map->setTerritories(mapList);

    Continent *cont = new Continent();
    vector<Continent *> *contVector = new vector<Continent *>;
    contVector->push_back(cont);

    cont->testSetTerritories(list1);
    map->setContinents(contVector);

    // END OF DUMMY CODE
}

void GameEngine::initGameEndDummy(LogObserver *observer) {
    Player *p = new Player(observer);
    Territory *t = new Territory();
    vector<Territory *> *tvec = new vector<Territory *>;
    tvec->push_back(t);
    p->setPlayerTerritories(tvec);
    players->push_back(p);
}

void GameEngine::stringToLog() {

    //creating file string
    string filename = "../Log/gamelog.txt";
    ofstream outputFile;

    //checking if file exists
    ifstream exists(filename);

    if (exists.bad()) {
        outputFile.open(filename);
    }

    // Append data to the file
    outputFile.open(filename, std::ios_base::app);

    // Print current phase enum to log
    PHASE *currentPhase = this->getCurrentPhase();
    string phaseString;
    switch (*currentPhase) {
        case START:
            phaseString = "START";
            break;
        case MAP_LOADED:
            phaseString = "MAP_LOADED";
            break;
        case MAP_VALIDATED:
            phaseString = "MAP_VALIDATED";
            break;
        case PLAYERS_ADDED:
            phaseString = "PLAYERS_ADDED";
            break;
        case PLAY:
            phaseString = "PLAY";
            break;
        case ASSIGN_REINFORCEMENT:
            phaseString = "ASSIGN_REINFORCEMENT";
            break;
        case ISSUE_ORDERS:
            phaseString = "ISSUE_ORDERS";
            break;
        case EXECUTE_ORDERS:
            phaseString = "EXECUTE_ORDERS";
            break;
        case CHECK_DRAW:
            phaseString = "CHECK_DRAW";
            break;
        case DRAW:
            phaseString = "DRAW";
            break;
        case CHECK_WIN:
            phaseString = "CHECK_WIN";
            break;
        case WIN:
            phaseString = "WIN";
            break;
        case END:
            phaseString = "END";
            break;
        default:
            phaseString = "UNKNOWN";
    }
    outputFile << "Current phase: " << phaseString << endl;

    outputFile.close();
}

// This is int because it does not change the PHASE of the game, it simply creates command files for each tournament and returns the max amount of turns
int GameEngine::loadTournament(string arguments) {
    // delete existing tournament if exists
    fs::remove_all("tournament");

    // create new tournament
    vector<string> commandTokens = MapLoader::getTokens(arguments, ' ');

    vector<string> mapFiles = *new vector<string>();
    vector<string> strategyStrings = *new vector<string>();
    int numberOfGames;
    int maxNumberOfTurns;

    if (commandTokens.size() == 8 &&
        commandTokens[0] == "-M" &&
        commandTokens[2] == "-P" &&
        commandTokens[4] == "-G" &&
        commandTokens[6] == "-D") {

        // get each map file
        vector<string> mapFileStrings = MapLoader::getTokens(commandTokens[1], ',');
        for (const string &mapFileString: mapFileStrings) {
            // run pre validation of map
            bool mapLoaded = MapLoader::loadMap(this, new string(mapFileString));
            if (!mapLoaded) {
                cout << "Tournament command invalid: Incorrect map file " << mapFileString << " Please try again!" << endl;
                return -1;
            }

            // add map
            mapFiles.push_back(mapFileString);
        }

        strategyStrings = MapLoader::getTokens(commandTokens[3], ',');
        numberOfGames = stoi(commandTokens[5]);
        maxNumberOfTurns = stoi(commandTokens[7]);

        // validate
        if (mapFiles.size() < 1 || mapFiles.size() > 5 ||
            strategyStrings.size() < 2 || strategyStrings.size() > 4 ||
            numberOfGames < 1 || numberOfGames > 5 ||
            maxNumberOfTurns < 10 || maxNumberOfTurns > 50) {
            cout << "Tournament command invalid: Incorrect arg values. Please try again!" << endl;
            return -1;
        }
    } else {
        cout << "Tournament command invalid: Incorrect args. Please try again!" << endl;
        return -1;
    }

    // Create tournament directory
    fs::path tournamentPath = fs::current_path() / "tournament";
    fs::create_directory(tournamentPath);

    // Create tournament files
    int tournamentCounter = 0;
    for (int i = 0; i < mapFiles.size(); i++) {
        stringstream *mapDirectory = new stringstream();
        *mapDirectory << "map" << i;
        fs::path mapPath = tournamentPath / mapDirectory->str();
        fs::create_directory(mapPath);
        for (int j = 0; j < numberOfGames; j++) {
            // Create a tournament file and increment counter
            stringstream *gameFileName = new stringstream();
            *gameFileName << "tournament/map" << i << "/game" << tournamentCounter++ << ".cmd";
            ofstream newGameFile(gameFileName->str());

            // Each tournament game file includes
            newGameFile << "loadmap " << mapFiles[i] << endl;
            newGameFile << "validatemap" << endl;

            int playerCounter = 0;
            for (string strategyString: strategyStrings) {
                newGameFile << "addplayer " << strategyString << playerCounter++ << endl;
            }

            newGameFile << "gamestart" << endl;
            newGameFile.close();
        }
    }

    return maxNumberOfTurns;
}
