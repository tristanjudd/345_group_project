#include "GameEngine.h"
#include "../CommandProcessing/CommandProcessing.h"

Player *GameEngine::neutral = new Player(-1); //CREATING THE STATIC NEUTRAL PLAYER ID = -1
std::unordered_map<string, bool> *GameEngine::peaceStatus = new std::unordered_map<string, bool>(); //CREATING THE STATIC PEACE STATUS MAP
vector<int> *GameEngine::conqStatus = new vector<int>(); //CREATING THE STATIC CONQUERED STATUS VECTOR

//default constructor
GameEngine::GameEngine() {
    cout << "GameEngine default constructor called" << endl;
    winner = new int(-1);
    players = new vector<Player *>;
}

//copy constructor
GameEngine::GameEngine(const GameEngine &gameEngine) {
    cout << "GameEngine copy constructor called" << endl;
    winner = new int(*gameEngine.winner);
    players = gameEngine.players;
}

//assignment operator
GameEngine &GameEngine::operator=(const GameEngine &gameEngine) {
    cout << "GameEngine assignment operator called" << endl;
    if (this != &gameEngine) {
        delete this->winner;
        this->winner = new int(*gameEngine.winner);
    }
    return *this;
}

//ostream operator
ostream &operator<<(ostream &out, const GameEngine &gameEngine) {
    out << "GameEngine: " << endl;
    out << "Winner: " << *gameEngine.winner << endl;
    out << "Map: " << *gameEngine.map << endl;
    out << "Players: " << endl;
    for (int i = 0; i < gameEngine.players->size(); i++) {
        out << *gameEngine.players->at(i) << endl;
    }
    return out;
}

//destructor
GameEngine::~GameEngine() {
    cout << "GameEngine destructor called" << endl;
    winner = nullptr;
    delete winner;
    delete players;

    delete neutral;
    delete peaceStatus;
    delete conqStatus;
}

//Getters and setters
vector<Player *> *GameEngine::getPlayers() const {
    return players;
}

void GameEngine::setPlayers(vector<Player *> *players) {
    GameEngine::players = players;
}

Map *GameEngine::getMap() const {
    return map;
}

void GameEngine::setMap(Map *map) {
    GameEngine::map = map;
}

// Startup
void GameEngine::startupPhase(GameEngine *game, CommandProcessor *cp, Command *command, PHASE phase) {
    cout << "Welcome to our bootleg Warzone!" << endl;
    int playerId = 0;
    string mapFile;
    while (true) {
        switch (phase) {
            case START: {
                cout << "Start state" << endl;
                // will prompt user, and should not pass for anything other than 'loadmap <mapfile>' (in this phase)
                command = cp->getCommand(phase, cp);
                cout << *command << endl;  // just to show I did my part
                mapFile = *command->getArgument();
                phase = loadMap(game, phase, mapFile);
                break;
            }
            case MAP_LOADED: {
                cout << "\nMap loaded state" << endl;
                command = cp->getCommand(phase, cp);
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
                command = cp->getCommand(phase, cp);
                cout << *command << endl;
                playerId = 0;
                if (*command->getName() == COMMAND::addplayer) {
                    phase = addPlayer(game, *command->getArgument(), playerId);
                    playerId = playerId + 1;
                    break;
                }
                break;
            }
            case PLAYERS_ADDED: {
                cout << "Players added state" << endl;
                command = cp->getCommand(phase, cp);
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
                        phase = addPlayer(game, *command->getArgument(), playerId);
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
}

//Load map method
PHASE GameEngine::loadMap(GameEngine *game, PHASE phase, string mapFile) {
    cout << "Load Map Method" << endl;
    if (MapLoader::loadMap(game, &mapFile)) {
        cout << *game->getMap() << endl;
        cout << *game->map->getName() << " map loaded" << endl;
        phase = MAP_LOADED;
    } else { // restart if map not loaded
        cout << "Map not loaded \n" << endl;
        phase = START;
    }
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
    return phase;
}

// Add player method
PHASE GameEngine::addPlayer(GameEngine *game, string playerName, int playerId) {
    Player *newPlayer = new Player(playerName, playerId); //create new player
    vector<Player *> *players = game->getPlayers();
    players->push_back(newPlayer); //add player to vector of players
    cout << "Player " << *newPlayer->getName() << " added" << endl;
    cout << "Num of players: " << players->size() << endl << endl;
    game->setPlayers(players);
    return PLAYERS_ADDED;
}

// Game start method
PHASE GameEngine::gameStart(GameEngine *game) {
    distributeTerritories(game->getMap());
    determinePlayerOrder(game);
    giveInitialArmies();
    drawCards();
    return END;
}

// Distribute territories method
void GameEngine::distributeTerritories(Map *map) {
    cout << "Distributing territories..." << endl;
    vector<Territory *> *territories = map->getTerritories();
    int numPlayers = players->size();
    int numTerritories = territories->size();
    int territoriesPerPlayer = numTerritories / numPlayers;
    int remainderTerritories = numTerritories % numPlayers;

    //distribute all the territories to the players and set owner of territory
    for (int i = 0; i < numPlayers; i++) {
        vector<Territory *> *territoriesForPlayers = players->at(i)->getPlayerTerritories();
        for (int j = 0; j < territoriesPerPlayer; j++) {
            territoriesForPlayers->push_back(territories->at(i * territoriesPerPlayer + j)); //add territory to player
            territories->at(i * territoriesPerPlayer + j)->setOwner(players->at(i)); //set owner of territory
        }
        players->at(i)->setPlayerTerritories(territoriesForPlayers);
    }
    //distribute the remainder of the territories to the players and set owner of territory
    for (int i = 0; i < remainderTerritories; i++) {
        players->at(i)->getPlayerTerritories()->push_back(
                territories->at(i + numPlayers * territoriesPerPlayer)); //add territory to player
        territories->at(i + numPlayers * territoriesPerPlayer)->setOwner(players->at(i)); //set owner of territory
    }
    //print out territories of players
    for (int i = 0; i < players->size(); i++) {
        cout << "\nPlayer " << *players->at(i)->getId() << " has territories: " << endl;
        vector<Territory *> *tempTerritories = players->at(i)->getPlayerTerritories();
        for (int j = 0; j < tempTerritories->size(); j++) {
            cout << *tempTerritories->at(j)->getTerritoryName() << endl;
        }
        delete tempTerritories;
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
void GameEngine::giveInitialArmies() {
    //give initial armies of 50 to each player
    cout << "\nGiving initial armies..." << endl;
    for (int i = 0; i < players->size(); i++) {
        players->at(i)->setReinforcements(50);
        cout << "Player " << *players->at(i)->getName() << " has " << players->at(i)->getReinforcements()
             << " armies" << endl;
    }
}

// Draw cards method
void GameEngine::drawCards() {
    cout << "\nDrawing cards for players..." << endl;
    Deck *deck = new Deck();
    for (int i = 0; i < players->size(); i++) {
        Hand *hand = new Hand();
        hand->insert(deck->draw());
        hand->insert(deck->draw());
        players->at(i)->setHand(hand);
    }
    //print hand of players
    for (int i = 0; i < players->size(); i++) {
        cout << "Player " << *players->at(i)->getName() << " has " << players->at(i)->getHand()->size()
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
            return WIN; //go to start phase
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
    abort();
}

// Start of new turn
void GameEngine::mainGameLoop(GameEngine *game, PHASE phase) {
    //initGameDummy();
    cout << "There are " << players->size() << " players" << endl;

    while (true) {
        switch (phase) {
            case CHECK_WIN: {
                cout << "Check victory state" << endl;
                phase = game->checkWin();
                break;
            }
            case ASSIGN_REINFORCEMENT: {
                cout << "Assign reinforcement state" << endl;
                phase = game->reinforcementPhase();
                break;
            }
            case ISSUE_ORDERS: {
                cout << "Issue orders state" << endl;
                phase = game->issueOrdersPhase();
                break;
            }
            case EXECUTE_ORDERS: {
                cout << "Execute orders state" << endl;
                phase = game->executeOrdersPhase();
                break;
            }
            case WIN:
                cout << "Win Phase" << endl;
                phase = game->win();
                break;
            case END:
                cout << "End Phase" << endl;
                game->end();
            default:
                cout << "Invalid phase" << endl;
                break;
        }
    }
};

//Assign reinforcement phase
PHASE GameEngine::reinforcementPhase() {
    cout << "Assigning reinforcements to all players..." << endl;

    // loop through all current players and assign reinforcements based on game logic
    for (Player *player: *players) {
        // get current player's territories
        vector<Territory *> playerTerritories = *(player->getPlayerTerritories());

        // Assign troops based on game criteria
        int newTroops = 3; // minimum new troops

        // Add bonus of player's territories divided by 3, rounded down
        newTroops += playerTerritories.size() / 3;

        // Add continent bonus
        // loop through all continents
        for (Continent *c: *(map->getContinents())) {
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
        player->setReinforcements(player->getReinforcements() + newTroops);
    }
    cout << "Reinforcements assigned.\n" << endl;
    return ISSUE_ORDERS;
}

//Issue orders phase
PHASE GameEngine::issueOrdersPhase() {
// loop through each player and call issueOrder method
    for (Player *player: *players) {
        cout << "PLAYER " << *(player->getId()) << " ISSUING ORDERS" << endl;
        bool stillPlaying = true;

        while (stillPlaying) {
            // issue order method returns a bool
            // it will return true for any move except when
            // player selects the end turn choice
            stillPlaying = player->issueOrder();
        }
    }
    return EXECUTE_ORDERS;
}

//Execute orders phase
PHASE GameEngine::executeOrdersPhase() {

    vector<Order *> currentOrderList;
    // flag indicating whether an order has been executed
    // initialized to true so that we can enter the execution loop
    bool modFlag = true;
    // flag indicating whether a deployment was executed
    // initialized to true to make sure all deployments are executed before other orders
    bool deployFlag = true;

    // loop executing orders until there are no orders left
    while (modFlag) {
        // set flag to false at the beginning of each round-robin
        modFlag = false;
        // go through each player and execute the first order in their list
        for (Player *player: *players) {
            // get current player's order list
            currentOrderList = *(player->getOrders()->getList());

            // if there is at least one order left to execute
            if (currentOrderList.size() > 0) {
                //get top order
                Order *toExecute = currentOrderList.at(0);
                // remove order from front of list
                currentOrderList.erase(currentOrderList.begin());
                // check if order is a deploy order
                auto *isDeploy = dynamic_cast<Deploy *>(toExecute);

                // if order is deploy, nothing needs to be checked and it can be executed right away
                if (isDeploy) {
                    toExecute->execute();
                    // set deploy flag to true to indicate there was a deployment this round
                    deployFlag = true;
                } else {
                    // if this is set, either another player deployed this turn
                    // or a player deployed last turn and we need to run through a round-robin to make sure no others deploy
                    if (deployFlag) {
                        // set to false so that if nobody else deploys this turn, next turn other orders execute
                        deployFlag = false;
                    } else {
                        // if flag is false, nobody deployed for a whole turn so non-deploy orders are now
                        // safe to execute
                        toExecute->execute();
                    }
                }

            }
        }

    }
    return CHECK_WIN;
}

PHASE GameEngine::checkWin() {
    cout << "There are " << players->size() << " players" << endl;

    // iterate through players and check if any has 0 territories
    std::vector<Player *>::iterator it;
    int i = 0;
    for (it = players->begin(); it != players->end(); ) {
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

    return ASSIGN_REINFORCEMENT;
}



// inits a bunch of objects to have something to test with in dev phase
void GameEngine::initGameDummy() {
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

    Player *p1 = new Player();
    p1->setPlayerTerritories(list1);
    for (Territory *t: *list1) {
        t->setOwner(p1);
    }
    Player *p2 = new Player();
    p2->setPlayerTerritories(list2);
    for (Territory *t: *list2) {
        t->setOwner(p2);
    }
    Player *p3 = new Player();
    p3->setPlayerTerritories(list3);
    for (Territory *t: *list3) {
        t->setOwner(p3);
    }

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
    Player *p4 = new Player();
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

void GameEngine::initGameEndDummy() {
    Player *p = new Player();
    Territory *t = new Territory();
    vector<Territory *> *tvec = new vector<Territory *>;
    tvec->push_back(t);
    p->setPlayerTerritories(tvec);
    players->push_back(p);
}