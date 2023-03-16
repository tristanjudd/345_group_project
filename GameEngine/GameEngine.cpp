#include "GameEngine.h"
#include <set>

Player* GameEngine::neutral = new Player(-1); //CREATING THE STATIC NEUTRAL PLAYER ID = -1
std::unordered_map<string, bool>* GameEngine::peaceStatus = new std::unordered_map<string, bool>(); //CREATING THE STATIC PEACE STATUS MAP
vector<int>* GameEngine::conqStatus = new vector<int>(); //CREATING THE STATIC CONQUERED STATUS VECTOR

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

    initGameDummy();
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
    cout << "Bye again" << endl;
}

//default constructor
GameEngine::GameEngine() {
    cout << "GameEngine default constructor called" << endl;
    winner = new int(-1);
    players = new vector<Player *>;
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

    delete neutral;
    delete peaceStatus;
    delete conqStatus;
}

// START OF ASSIGNMENT 2
// Start of new turn
PHASE GameEngine::mainGameLoop() {

    cout << "There are " << players->size() << " players" << endl;

    // check if there's a winner
    if (players->size() == 1) {
        return WIN;
    }

    return ASSIGN_REINFORCEMENT;

};

//Assign reinforcement phase
PHASE GameEngine::reinforcementPhase() {
    cout << "Assigning reinforcements to all players..." << endl;

    // loop through all current players and assign reinforcements based on game logic
    for (Player* player : *players) {
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

    cout << "Reinforcements assigned.\n" << endl;

    return ISSUE_ORDERS;
}

//Issue orders phase
PHASE GameEngine::issueOrdersPhase() {
// loop through each player and call issueOrder method
    for (Player* player : *players) {
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
       for (Player* player : *players) {
           // get current player's order list
           currentOrderList = *(player->getOrders()->getList());

           // if there is at least one order left to execute
           if (currentOrderList.size() > 0) {
               //get top order
               Order* toExecute = currentOrderList.at(0);
               // remove order from front of list
               currentOrderList.erase(currentOrderList.begin());
               // check if order is a deploy order
               auto* isDeploy = dynamic_cast<Deploy *>(toExecute);

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

    return PLAY;
}

//// function for checking whether input is a number within a certain range
//int string_is_num_in_range(string str, int n, int m) {
//    // check that string is not empty and all chars are digits
//    if (!str.empty() && std::all_of(str.begin(), str.end(), ::isdigit)) {
//        // convert string to int and return
//        int num = std::stoi(str);
//        // if num in range return num
//        if (num >= n && num <= m) return num;
//            // else return false
//        else return 0;
//
//    } else {
//        // return false
//        return 0;
//    }
//}
//
//void invalidInput() {
//    cout << "Invalid input, try again" << endl;
//    //clear input stream
//    cin.clear();
//    cin.ignore();
//}

// inits a bunch of objects to have something to test with in dev phase
void GameEngine::initGameDummy() {
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

    vector<Territory *>* borders1 = new vector<Territory *>;
    borders1->push_back(t2);
    borders1->push_back(t4);
    t1->testSetBorders(borders1);

    vector<Territory *>* borders2 = new vector<Territory *>;
    borders2->push_back(t1);
    borders2->push_back(t3);
    borders2->push_back(t5);
    t2->testSetBorders(borders2);

    vector<Territory *>* borders3 = new vector<Territory *>;
    borders3->push_back(t2);
    borders3->push_back(t6);
    t3->testSetBorders(borders3);

    vector<Territory *>* borders4 = new vector<Territory *>;
    borders4->push_back(t1);
    borders4->push_back(t5);
    borders4->push_back(t7);
    t4->testSetBorders(borders4);

    vector<Territory *>* borders5 = new vector<Territory *>;
    borders5->push_back(t2);
    borders5->push_back(t4);
    borders5->push_back(t6);
    borders5->push_back(t8);
    t5->testSetBorders(borders5);

    vector<Territory *>* borders6 = new vector<Territory *>;
    borders6->push_back(t3);
    borders6->push_back(t5);
    borders6->push_back(t9);
    t6->testSetBorders(borders6);

    vector<Territory *>* borders7 = new vector<Territory *>;
    borders7->push_back(t4);
    borders7->push_back(t8);
    t7->testSetBorders(borders7);

    vector<Territory *>* borders8 = new vector<Territory *>;
    borders8->push_back(t5);
    borders8->push_back(t7);
    borders8->push_back(t9);
    t8->testSetBorders(borders8);

    vector<Territory *>* borders9 = new vector<Territory *>;
    borders9->push_back(t6);
    borders9->push_back(t8);
    t9->testSetBorders(borders9);

    vector<Territory *>* list1 = new vector<Territory *>;
    list1->push_back(t1);
    list1->push_back(t2);
    list1->push_back(t3);
    vector<Territory *>* list2 = new vector<Territory *>;
    list2->push_back(t4);
    list2->push_back(t5);
    list2->push_back(t6);
    vector<Territory *>* list3 = new vector<Territory *>;
    list3->push_back(t7);
    list3->push_back(t8);
    list3->push_back(t9);

    Player *p1 = new Player();
    p1->setTerritories(list1);
    for (Territory* t : *list1) {
        t->setOwner(p1);
    }
    Player* p2 = new Player();
    p2->setTerritories(list2);
    for (Territory* t : *list2) {
        t->setOwner(p2);
    }
    Player* p3 = new Player();
    p3->setTerritories(list3);
    for (Territory* t : *list3) {
        t->setOwner(p3);
    }

    Deck* deck = new Deck();
    Hand* h1 = new Hand();
    Hand* h2 = new Hand();
    Hand* h3 = new Hand();

    h1->insert(deck->draw());
    h1->insert(deck->draw());
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

    vector<Territory *>* mapList = new vector<Territory *>;
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

    // END OF DUMMY CODE
}