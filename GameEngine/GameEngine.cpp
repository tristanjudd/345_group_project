#include "GameEngine.h"

//Start phase
PHASE GameEngine::start() {
    cout << "Welcome to our bootleg Warzone!" << endl;
    return MAP_LOADED; // go to load map phase
}

//Load map phase
PHASE GameEngine::loadMap() {
    cout << "Loading map..." << endl;
    cout << "Map loaded" << endl;
    while (true) {
        cout << "Load another map? (y/n): ";
        string loadAnotherMap;
        cin >> loadAnotherMap;
        if (loadAnotherMap == "y") {
            return MAP_LOADED; //load another map
        } else if (loadAnotherMap == "n") {
            return MAP_VALIDATED; //go to validate map phase
        }
        cout << "Invalid input" << endl << "Try again" << endl;
    }
}

//Validate map phase
PHASE GameEngine::validateMap() {
    cout << "Validating map..." << endl;
    cout << "Map validated" << endl;
    while (true) {
        cout << "Validate another map? (y/n): ";
        string validateAnotherMap;
        cin >> validateAnotherMap;
        if (validateAnotherMap == "y") {
            return MAP_VALIDATED; //validate another map
        } else if (validateAnotherMap == "n") {
            return PLAYERS_ADDED; //go to add players phase
        }
        cout << "Invalid input" << endl << "Try again" << endl;
    }
}

//Add players phase
PHASE GameEngine::addPlayers() {
    int numPlayers;
    cout << "How many players would you like to add: ";
    cin >> numPlayers;
    if (numPlayers < 1 || !isdigit(numPlayers) == 0) { //check if input is a number greater than 0
        cout << "Invalid number of players" << endl;
        cin.clear();
        cin.ignore(100, '\n');
        return PLAYERS_ADDED; //go back to add players phase
    }
    cout << "Players created" << endl;
    return PLAY; //go to assign reinforcement phase
}

//Assign reinforcement phase ***DEPRECATED FROM A1
PHASE GameEngine::assignReinforcements() {
    while (true) {
        cout << "Assign reinforcements" << endl;
        while (true) {
            cout << "Continue? (y/n): ";
            string continueAssigningReinforcements;
            cin >> continueAssigningReinforcements;
            if (continueAssigningReinforcements == "y") {
                return ASSIGN_REINFORCEMENT; //assign more reinforcements
            } else if (continueAssigningReinforcements == "n") {
                return ISSUE_ORDERS; //go to issue orders phase
            }
            cout << "Invalid input" << endl << "Try again" << endl;
            cin.clear(); //clear input stream
            cin.ignore();
        }
    }
}

//Issue orders phase ***DEPRECATED FROM A1
PHASE GameEngine::issueOrders() {
    while (true) {
        cout << "Issue orders" << endl;
        while (true) {
            cout << "Continue? (y/n): ";
            string continueIssuingOrders;
            cin >> continueIssuingOrders;
            if (continueIssuingOrders == "y") {
                return ISSUE_ORDERS; //issue more orders
            } else if (continueIssuingOrders == "n") {
                return EXECUTE_ORDERS; //go to execute orders phase
            }
            cout << "Invalid input" << endl << "Try again" << endl;
            cin.clear(); //clear input stream
            cin.ignore();
        }
    }
}

//Execute orders phase ***DEPRECATED FROM A1
PHASE GameEngine::executeOrders() {
    while (true) {
        cout << "Execute orders" << endl;
        while (true) {
            if (*winner != -1) {
                return WIN; //go to win phase
            }
            cout << "Continue? (y/n): ";
            string continueExecutingOrders;
            cin >> continueExecutingOrders;
            if (continueExecutingOrders == "y") {
                return EXECUTE_ORDERS; //execute more orders
            } else if (continueExecutingOrders == "n") {
                return ASSIGN_REINFORCEMENT; //go to assign reinforcement phase
            } else if (continueExecutingOrders == "w") { //simulate winner
                return WIN; //simulate win
            }
            cout << "Invalid input" << endl << "Try again" << endl;
        }
    }
}

//Win phase
PHASE GameEngine::win() {
    cout << "Player " << *winner << " wins!" << endl;
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
    cout << "Bye again" << endl;
}

//default constructor
GameEngine::GameEngine() {
    cout << "GameEngine default constructor called" << endl;
    winner = new int(-1);
    players = new vector<Player *>;
    currentPlayer = new int;
}

//copy constructor
GameEngine::GameEngine(const GameEngine& gameEngine) {
    cout << "GameEngine copy constructor called" << endl;
    winner = new int(*gameEngine.winner);
    players = gameEngine.players;
}

//assignment operator
GameEngine& GameEngine::operator=(const GameEngine& gameEngine) {
    cout << "GameEngine assignment operator called" << endl;
    if (this != &gameEngine) {
        delete this->winner;
        this->winner = new int(*gameEngine.winner);
    }
    return *this;
}

//ostream operator
ostream& operator<<(ostream& out, const GameEngine& gameEngine) {
    cout << "GameEngine ostream operator called" << endl;
    out << "Winner: " << *gameEngine.winner << endl;
    return out;
}

//destructor
GameEngine::~GameEngine() {
    cout << "GameEngine destructor called" << endl;
    winner = nullptr;
    delete winner;
    delete [] players;
}

// START OF ASSIGNMENT 2

// Start of new turn
PHASE GameEngine::mainGameLoop() {
    cout << "There are " << players->size() << " players" << endl;

    // check if there's a winner
    if (players->size() == 1) {
        return WIN;
    }

    // set the current player to first player in the players list
    *currentPlayer = 0;

    return ASSIGN_REINFORCEMENT;

};

//Assign reinforcement phase
PHASE GameEngine::reinforcementPhase() {
    // if all players are done assigning reinforcements, move to assign order phase
    if (*currentPlayer > players->size()) {
        *currentPlayer = 0;
        return ISSUE_ORDERS;
    }

    // get pointer to current player object
    Player* player = players->at(*currentPlayer);
    vector<Territory *> playerTerritories = *(player->getTerritories());

    // Assign troops based on game criteria
    int newTroops = 3;

    // Add bonus of player's territories divided by 3, rounded down
    newTroops += playerTerritories.size() / 3;

    // Add continent bonus
    // TODO

    // Update player's reinforcement pool
    player->setReinforcements(player->getReinforcements() + newTroops);

    // Print current player and available troops
    cout << "Player " << *currentPlayer << " reinforcement phase." << endl;

    while (true) {
        // print remaining reinforcement pool
        cout << "You have " << player->getReinforcements() << " troops to assign" << endl;
        // print countries to deploy to
        cout << "in the following territories: " ;

        for (int i = 0; i < playerTerritories.size(); i++) {
            cout << playerTerritories.at(i)->getTerritoryName() << " ";
        }

        cout << "." << endl;

        while (player->getReinforcements() > 0) {
            cout << "Continue? (y/n): ";
            string continueAssigningReinforcements;
            cin >> continueAssigningReinforcements;
            if (continueAssigningReinforcements == "y") {

                return ASSIGN_REINFORCEMENT; //assign more reinforcements
            } else if (continueAssigningReinforcements == "n") {
                // if player doesn't want to deploy any other troops, return
                // to top of reinforcement phase for next player or next phase
                return ASSIGN_REINFORCEMENT; //go to issue orders phase
            }
            cout << "Invalid input" << endl << "Try again" << endl;
            cin.clear(); //clear input stream
            cin.ignore();
        }
    }
}

//Issue orders phase
PHASE GameEngine::issueOrdersPhase() {
    while (true) {
        cout << "Issue orders" << endl;
        while (true) {
            cout << "Continue? (y/n): ";
            string continueIssuingOrders;
            cin >> continueIssuingOrders;
            if (continueIssuingOrders == "y") {
                return ISSUE_ORDERS; //issue more orders
            } else if (continueIssuingOrders == "n") {
                return EXECUTE_ORDERS; //go to execute orders phase
            }
            cout << "Invalid input" << endl << "Try again" << endl;
            cin.clear(); //clear input stream
            cin.ignore();
        }
    }
}

//Execute orders phase
PHASE GameEngine::executeOrdersPhase() {
    while (true) {
        cout << "Execute orders" << endl;
        while (true) {
            if (*winner != -1) {
                return WIN; //go to win phase
            }
            cout << "Continue? (y/n): ";
            string continueExecutingOrders;
            cin >> continueExecutingOrders;
            if (continueExecutingOrders == "y") {
                return EXECUTE_ORDERS; //execute more orders
            } else if (continueExecutingOrders == "n") {
                return ASSIGN_REINFORCEMENT; //go to assign reinforcement phase
            } else if (continueExecutingOrders == "w") { //simulate winner
                return WIN; //simulate win
            }
            cout << "Invalid input" << endl << "Try again" << endl;
        }
    }
}