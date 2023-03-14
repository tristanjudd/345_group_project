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
    // DUMMY CODE adding players for dev purposes
    Territory* t1 = new Territory(1, 1, "A");
    Territory* t2 = new Territory(2, 1, "B");
    Territory* t3 = new Territory(3, 1, "C");
    Territory* t4 = new Territory(4, 1, "D");
    Territory* t5 = new Territory(5, 1, "E");
    Territory* t6 = new Territory(6, 1, "F");
    Territory* t7 = new Territory(7, 1, "G");
    Territory* t8 = new Territory(8, 1, "H");
    Territory* t9 = new Territory(9, 1, "I");

    vector<Territory *>* list1 = new vector<Territory *>();
    list1->push_back(t1);
    list1->push_back(t2);
    list1->push_back(t3);
    vector<Territory *>* list2 = new vector<Territory *>();
    list2->push_back(t4);
    list2->push_back(t5);
    list2->push_back(t6);
    vector<Territory *>* list3 = new vector<Territory *>();
    list3->push_back(t7);
    list3->push_back(t8);
    list3->push_back(t9);

    Player *p1 = new Player();
    p1->setTerritories(list1);
    Player* p2 = new Player();
    p2->setTerritories(list2);
    Player* p3 = new Player();
    p3->setTerritories(list3);

    players->push_back(p1);
    players->push_back(p2);
    players->push_back(p3);

    // END OF DUMMY CODE

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
    cout << "Assigning reinforcements to all players..." << endl;
    cout << "Reinforcements assigned." << endl;
    // loop through all current players and assign reinforcements based on game logic
    for (int i = 0; i < players->size(); i++) {
        // get pointer to current player object
        Player* player = players->at(i);
        // get current player's territories
        vector<Territory *> playerTerritories = *(player->getTerritories());

        // Assign troops based on game criteria
        int newTroops = 3; // minimum new troops

        // Add bonus of player's territories divided by 3, rounded down
        newTroops += playerTerritories.size() / 3;

        // Add continent bonus
        // TODO

        // Update player's reinforcement pool
        player->setReinforcements(player->getReinforcements() + newTroops);

    }

    return ISSUE_ORDERS;
}

//Issue orders phase
PHASE GameEngine::issueOrdersPhase() {
    // if all players are done issuing orders, move to order execution phase
    // Note: currently 0-indexing players, might have to change this
    if (*currentPlayer + 1 > players->size()) {
        *currentPlayer = 0;
        return EXECUTE_ORDERS;
    }

    // get pointer to current player object
    Player* player = players->at(*currentPlayer);
    // get current player's territories
    vector<Territory *> playerTerritories = *(player->getTerritories()); // TODO use toDefend() here

    cout << "PLAYER " << (*currentPlayer) << " ISSUE ORDERS PHASE" << endl;

    // loop until player has deployed all troops
    while (player->getReinforcements() > 0) {
        // print remaining reinforcement pool
        cout << "Player " << (*currentPlayer) << " has " << player->getReinforcements() << " troops to assign to the following territories: " << endl;
        // print countries to deploy to
        for (int i = 0; i < playerTerritories.size(); i++) {
            cout << (i+1) << ". " << *(playerTerritories.at(i)->getTerritoryName()) << endl;
        }

        // get input for territory to deploy to
        cout << "Enter the number of the territory to which you wish to deploy troops: " << endl;
        string input;
        cin >> input;

        if (string_is_num_in_range(input, 1, playerTerritories.size())) {
            // Get number of territory (index in player's territories vector)
            int territoryNum = string_is_num_in_range(input, 1, playerTerritories.size());
            // loop until valid input is received
            while (true) {
                // get user input
                string numOfTroops;
                cout << "Enter the number of troops you wish to assign to " << *(playerTerritories.at(territoryNum - 1)->getTerritoryName()) << ": " << endl;
                cin >> numOfTroops;

                // if input valid add order to order list
                if (string_is_num_in_range(numOfTroops, 1, player->getReinforcements())) {
                    // get number of troops assigned
                    int troopsAssigned = string_is_num_in_range(numOfTroops, 1, player->getReinforcements());

                    // TODO: actually assign troops to territory

                    cout << troopsAssigned << " troops assigned to " << *(playerTerritories.at(territoryNum - 1)) << endl;
                    // decrement player's reinforcement pool
                    player->setReinforcements(player->getReinforcements() - troopsAssigned);
                    // end get valid input loop, returning to deploy troops loop
                    break;
                } else {
                    cout << "Invalid input, try again" << endl;
                    //clear input stream
                    cin.clear();
                    cin.ignore();
                }
            }

            // player enters invalid input
        } else {
            cout << "Invalid input, try again" << endl;
            //clear input stream
            cin.clear();
            cin.ignore();
        }

    }

    // ISSUE OTHER ORDERS



    // END ISSUE ORDERS


    // increment to next player
    *currentPlayer = *currentPlayer + 1;
    // return to top of reinforcement phase
    return ISSUE_ORDERS;

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

// function for checking whether input is a number within a certain range
int string_is_num_in_range(string str, int n, int m) {
    // check that string is not empty and all chars are digits
    if (!str.empty() && std::all_of(str.begin(), str.end(), ::isdigit)) {
        // convert string to int and return
        int num = std::stoi(str);
        // if num in range return num
        if (num >= n && num <= m) return num;
            // else return false
        else return 0;

    } else {
        // return false
        return 0;
    }

}