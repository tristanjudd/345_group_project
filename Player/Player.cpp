#include "Player.h"
#include <vector>
#include <set>

//Default Constructor
Player::Player() {
    territories = new vector<Territory *>();
    hand = new Hand();
    orders = new OrderList();
    id = new int(0);

    // ASSIGNMENT 2
    reinforcements = new int;
    *reinforcements = 0;
}

//Constructor
Player::Player(vector<Territory *> *territories, Hand *hand, OrderList* orders, int *id) {
    Player::id = id;
    Player::territories = territories;
    Player::hand = hand;
    Player::orders = orders;
}

Player::Player(int id){

    Player::id = new int(id);

}

//Copy Constructor
Player::Player(const Player &p) {

    territories = new vector<Territory *>(*p.territories);
    hand = new Hand(*p.hand);
    orders = new OrderList(*p.orders);
    id = new int(*p.id);
}


//Assignment operator
Player &Player::operator=(const Player &p) {
    if (this != &p) {
        territories = new vector<Territory *>(*p.territories);
        hand = new Hand(*p.hand);
        orders = new OrderList(*p.orders);
        id = new int(*p.id);

    }
    return *this;
}

//Stream insertion operator
ostream &operator<<(ostream &os, const Player &player) {

    os << "Player ID: " << *player.id << endl;
    os << "territories: " << endl;
    for (int i = 0; i < player.territories->size(); i++) {
        os << *player.territories->at(i) << endl;
    }

    os << " hand: " << *player.hand << endl;

    os << " orders: " << endl;

    for (int i = 0; i < player.orders->getList()->size(); i++) {
        os << *player.orders->getList()->at(i) << endl;
    }

    return os;
}

//Destructor Implementation
Player::~Player() {

    delete territories;
    delete hand;
    delete orders;
    delete id;
    delete reinforcements;
}

//Function creates an order and
//Adds it to the list of orders
bool Player::issueOrder() {

    vector<Territory *> playerTerritories = *territories; // TODO use toDefend() here

    // If there are troops to deploy, must be done before other orders can be issued
    if (*reinforcements > 0) {
        // print remaining reinforcement pool
        cout << "Player " << *id << " has " << *reinforcements << " troops to assign to the following territories: " << endl;
        // print countries to deploy to
        for (int i = 0; i < playerTerritories.size(); i++) {
            cout << (i+1) << ". " << *(playerTerritories.at(i)->getTerritoryName()) << endl;
        }

        // get input for territory to deploy to
        cout << "Enter the number of the territory to which you wish to deploy troops: " << endl;
        string input;
        cin >> input;

        int validTerritory = string_is_num_in_range(input, 1, playerTerritories.size());

        if (validTerritory) {
            // Get number of territory (index in player's territories vector)
            int territoryNum = string_is_num_in_range(input, 1, playerTerritories.size());
            // loop until valid input is received
            while (true) {
                // get user input
                string numOfTroops;
                cout << "Enter the number of troops you wish to assign to " << *(playerTerritories.at(validTerritory - 1)->getTerritoryName()) << ": " << endl;
                cin >> numOfTroops;

                int validNumOfTroops = string_is_num_in_range(numOfTroops, 1, *reinforcements);

                // if input valid add order to order list
                if (validNumOfTroops) {
                    // Create an order and add to order list
                    Order* deploy = new Deploy(this, validNumOfTroops, playerTerritories.at(validTerritory - 1));
                    orders->Add(deploy);

                    cout << validNumOfTroops << " troops assigned to " << *(playerTerritories.at(validTerritory - 1)->getTerritoryName()) << endl;

                    // decrement player's reinforcement pool
                    *reinforcements = *reinforcements - validNumOfTroops;
                    // end get valid input loop, returning to deploy troops loop
                    return true;
                    // player enters invalid input
                } else {
                    invalidInput();
                }
            }

            // player enters invalid input
        } else {
            invalidInput();
        }
    }
    // If no reinforcements, other orders are issued
    else {
        // ISSUE OTHER ORDERS

        // loop until valid input
        while (true) {
            string choice;

            cout << "Select one of the following three options by entering the number: " << endl;
            cout << "1. Defend territory" << endl;
            cout << "2. Attack territory" << endl;
            cout << "3. Play card" << endl;
            cout << "4. End turn" << endl;
            cout << "> " ;

            cin >> choice;
            int validInput = string_is_num_in_range(choice, 1, 4);

            if (validInput) {

                switch (validInput) {
                    // Case defend territory
                    case 1: {
                        cout << *id << " has the following territories to defend: " << endl;
                        // get defendable territories
                        vector<Territory *> defendable = *toDefend();
                        // print list on screen
                        for (int i = 0; i < defendable.size(); i++) {
                            cout << (i + 1) << ". " << *(defendable.at(i)->getTerritoryName()) << endl;
                        }
                        // take user input
                        string toDefend;
                        cout << "Enter the number of the territory to defend: ";
                        cin >> toDefend;

                        // loop until valid input
                        while (true) {
                            // check if number corresponds to an option given
                            int validDefend = string_is_num_in_range(toDefend, 1, defendable.size());
                            if (validDefend) {
                                cout << "To defend territory " << *(defendable.at(validDefend - 1)->getTerritoryName())
                                     << " enter the number of the territory to send troops from: ";
                                // take user input
                                string defendFrom;
                                cin >> defendFrom;
                                int validDefendFrom = string_is_num_in_range(defendFrom, 1, defendable.size());

                                // loop until valid input
                                while (true) {
                                    if (validDefendFrom) {
                                        string howManyTroops;
                                        cout << "How many troops do you want to defend with? ";

                                        while(true) {
                                            cin >> howManyTroops;
                                            int validHowManyTroops = string_is_num_in_range(howManyTroops, 1, 999999);

                                            if(validHowManyTroops) {
                                                cout << "Defend " << *(defendable.at(validDefend - 1)->getTerritoryName())
                                                     << " from " << *(defendable.at(validDefendFrom - 1)->getTerritoryName())
                                                     << " with " << validHowManyTroops << " troops." << endl;
                                                // Issue order
                                                Order* advance = new Advance(this,
                                                                             validHowManyTroops,
                                                                             defendable.at(validDefendFrom - 1),
                                                                             defendable.at(validDefendFrom - 1));
                                                orders->Add(advance);

                                                break;
                                            } else {
                                                invalidInput();
                                            }
                                        } // end while for how many troops

                                        break;
                                    } else {
                                        invalidInput();
                                    }
                                } // end of while loop
                                // exit while loop
                                break;
                            } else {
                                invalidInput();
                            }
                        } // end of while loop
                    break;
                    } // end of case 1
                    // case attack territory
                    case 2: {
                        vector<Territory *> attackable = *toAttack();

                        cout << "You can attack: " << endl;
                        for (int i = 0; i < attackable.size(); i++) {
                            cout << (i + 1) << ". " << *(attackable.at(i)->getTerritoryName()) << endl;
                        }

                        cout << "Select the territory you want to attack" << endl;

                        string attackTerritory;
                        while (true) {
                            cin >> attackTerritory;

                            int validAttack = string_is_num_in_range(attackTerritory, 1, attackable.size());

                            if (validAttack) {
                                // find countries that can attack target
                                vector<Territory *> attackingTerritories;

                                // loop through bordering territories of selected territory to attack and find player's territories
                                for (Territory *t: *(attackable.at(validAttack - 1)->getBorderedTerritories())) {
                                    if (std::find(territories->begin(), territories->end(), t) != territories->end()) {
                                        attackingTerritories.push_back(t);
                                    }
                                }

                                cout << "You can attack " << *(attackable.at(validAttack - 1)->getTerritoryName())
                                     << " from: " << endl;
                                // print all countries player can attack from
                                for (int i = 0; i < attackingTerritories.size(); i++) {
                                    cout << (i + 1) << ". " << *(attackingTerritories.at(i)->getTerritoryName())
                                         << endl;
                                }

                                // get valid input
                                string attackingTerritory;
                                cout << "Select the territory you want to attack from: " << endl;
                                while (true) {
                                    cin >> attackingTerritory;
                                    int validAttackingTerritory = string_is_num_in_range(attackingTerritory, 1,
                                                                                         attackingTerritories.size());

                                    if (validAttackingTerritory) {
                                        cout << "How many troops do you want to attack with?" << endl;

                                        string numTroops;
                                        while (true) {
                                            cin >> numTroops;
                                            int validNumTroops = string_is_num_in_range(numTroops, 1, 999999);

                                            if (validNumTroops) {
                                                string nameAttack = *(attackable.at(validAttack - 1)->getTerritoryName());
                                                string nameAttackFrom = *(attackingTerritories.at(validAttackingTerritory - 1)->getTerritoryName());
                                                cout << "Attacking " << nameAttack << " from " << nameAttackFrom << " with " << validNumTroops << " troops." << endl;

                                                // Issue order
                                                Order* advance = new Advance(this,
                                                                             validNumTroops,
                                                                             attackable.at(validAttack - 1),
                                                                             attackingTerritories.at(validAttackingTerritory - 1));
                                                orders->Add(advance);

                                                break;
                                            } else {
                                                invalidInput();
                                            }

                                        } // end of while loop for numTropps


                                        break;
                                    } else {
                                        invalidInput();
                                    }

                                } // end of while loop for attackingTerritory
                            break;
                            } else {
                                invalidInput();
                            }

                        } // end of while loop for attackTerritory

                    break;
                    } // end of case 2
                    // case play card
                    case 3: {
                        // get hand and print cards
                        vector<Card *> currentHand = hand->getHand();
                        // check if hand is empty, return if so
                        if (currentHand.size() == 0) {
                            cout << "You have no cards in your hand" << endl;
                            return true;
                        }

                        // else display cards in hand
                        cout << "You have the following cards to play: " << endl;

                        for (int i = 0; i < currentHand.size(); i++) {
                            CardType currentCard = currentHand.at(i)->getType();

                            switch(currentCard) {
                                case 0:
                                    cout << (i+1) << ". Bomb" << endl;
                                    break;
                                case 1:
                                    cout << (i+1) << ". Reinforcement" << endl;
                                    break;
                                case 2:
                                    cout << (i+1) << ". Blockade" << endl;
                                    break;
                                case 3:
                                    cout << (i+1) << ". Airlift" << endl;
                                    break;
                                case 4:
                                    cout << (i+1) << ". Diplomacy" << endl;
                            } // end of switch
                        } // end of for loop

                        cout << "Enter the number of the card you would like to play: ";

                        string cardChosen;

                        // loop until valid input
                        while (true) {
                            // get input
                            cin >> cardChosen;
                            // validate input
                            int validCard = string_is_num_in_range(cardChosen, 1, currentHand.size());
                            // if valid play card
                            if (validCard) {
                                CardType cardType = currentHand.at(validCard -1)->getType();

                                switch(cardType) {
                                    //Bomb
                                    case 0: {
                                        cout << "What territory do you want to bomb? ";
                                        string toBomb;
                                        cin >> toBomb;
                                        cout << "Order to bomb " << toBomb << " issued" << endl;

                                        break;
                                    } // end case 0
                                    //Reinforcement
                                    case 1: {
                                        cout << "Reinforcement" << endl;
                                        break;
                                    } // end case 1
                                    // Blockade
                                    case 2: {
                                        cout << "What territory do you want to blockade? ";
                                        string toBlockade;
                                        cin >> toBlockade;
                                        cout << "Issued order to blockade " << toBlockade << endl;

                                        break;
                                    } // end case 2
                                    // Airlift
                                    case 3: {
                                        cout << "Where do you want to airlift from?" << endl;
                                        for (int i = 0; i < territories->size(); i++) {
                                            cout << (i+1) << ". " << territories->at(i) << endl;
                                        }

                                        string airliftFrom;
                                        while (true) {
                                            cin >> airliftFrom;
                                            int validAirliftFrom = string_is_num_in_range(airliftFrom, 1, territories->size());

                                            if (validAirliftFrom) {
                                                cout << "How many troops to airlift? ";

                                                string troopsToAirlift;
                                                while(true) {
                                                    cin >> troopsToAirlift;
                                                    int validTroopsToAirlift = string_is_num_in_range(troopsToAirlift, 1, 999999);

                                                    if (validTroopsToAirlift) {
                                                        cout << "Airlift troops to which territory? ";

                                                        string airliftTo;

                                                        while(true) {
                                                            cin >> airliftTo;
                                                            int validAirliftTo = string_is_num_in_range(airliftTo, 1, territories->size());

                                                            if (validAirliftTo) {
                                                                // TODO issue order
                                                                cout << "Airlift " << validTroopsToAirlift << " troops form "
                                                                << *(territories->at(validAirliftFrom)->getTerritoryName()) << " to "
                                                                << *(territories->at(validAirliftTo - 1)->getTerritoryName()) << endl;

                                                                break;
                                                            } else {
                                                                invalidInput();
                                                            }
                                                        }

                                                        break;
                                                    } else {
                                                        invalidInput();
                                                    }
                                                }


                                                break;
                                            } else {
                                                invalidInput();
                                            }
                                        }

                                        break;
                                    } // end case 3
                                    // Diplomacy
                                    case 4: {
                                        cout << "What player do you want to use diplomacy on? ";

                                        string diplomacyTarget;

                                        while(true) {
                                            cin >> diplomacyTarget;
                                            int validDiplomacyTarget = string_is_num_in_range(diplomacyTarget, 1, 9999);

                                            if (validDiplomacyTarget) {
                                                // TODO issue order
                                                cout << "Using diplomacy on player " << validDiplomacyTarget << endl;
                                                break;
                                            } else {
                                                invalidInput();
                                            }
                                        }

                                        break;
                                    } // end case 4

                                } // end of switch

                                // TODO issue order
                                currentHand.at(validCard - 1)->play();

                                return true;
                            } else {
                                invalidInput();
                            }
                        } // end of while loop

                    return true;
                    } // end of case 3
                    // case end turn
                    case 4: {
                    return false;
                    } // end of case 4

                } // end of switch statement



                } else {
                    invalidInput();
                }
            } // end of while loop

        } // end of else for other orders

    return false;
    /*Order *order = new Order("Specific order");
    orders->push_back(order);*/
    //changed Order to abstract class need param to create specific order
    //Order *order = new Order("Specific order");
    //orders->Add(order);

}






//Function creates  list of territories a player will defend
// the
vector<Territory *> *Player::toDefend() {
    return territories;

    // Tristan commented out dummy code
    /*vector<Territory *> *territories = new vector<Territory *>();
    Territory *t1 = new Territory(1, 1, "France");
    Territory *t2 = new Territory(2, 2, "England");
    Territory *t3 = new Territory(3, 3, "Spain");
    Territory *t4 = new Territory(4, 4, "Germany");
    Territory *t5 = new Territory(5, 5, "Portugal");

    territories->push_back(t1);
    territories->push_back(t2);
    territories->push_back(t3);
    territories->push_back(t4);
    territories->push_back(t5);

    return territories; */

}

/*//Function creates a list of territories a player will attack
vector<Territory *> *Player::toAttack() {
    vector<Territory *> *territories = new vector<Territory *>();
    Territory *t1 = new Territory(1, 1, "Japan");
    Territory *t2 = new Territory(2, 2, "China");
    Territory *t3 = new Territory(3, 3, "Korea");
    Territory *t4 = new Territory(4, 4, "Vietnam");
    Territory *t5 = new Territory(5, 5, "Singapore");

    territories->push_back(t1);
    territories->push_back(t2);
    territories->push_back(t3);
    territories->push_back(t4);
    territories->push_back(t5);

    return territories;
}*/

//Function creates a list of territories a player will attack
vector<Territory *>* Player::toAttack() {
    set<Territory *> attackable;
    // go through each of player's territories
    for (Territory* t : *territories) {
        // for each territory, go through each of its bordering territories
        for (Territory* bordering : *(t->getBorderedTerritories())) {
            // if it doesn't belong to the player, add it to the set of attackable territories
            if (std::find(territories->begin(), territories->end(), bordering) == territories->end()) {
                attackable.insert(bordering);
            }
        }
    }

    // convert set to vector
    vector<Territory *>* attackableVector = new vector<Territory *>;
    for (Territory* t : attackable) {
        attackableVector->push_back(t);
    }

    return attackableVector;
}

//Getters and Setters
vector<Territory *> *Player::getTerritories() const {
    return territories;
}

void Player::setTerritories(vector<Territory *> *territories) {
    Player::territories = territories;
}

void Player::setHand(Hand *hand) {
    Player::hand = hand;
}

Hand *Player::getHand() {
    return hand;
}

OrderList *Player::getOrders() const {
    return orders;
}

void Player::setOrders(OrderList *orders) {
    Player::orders = orders;
}

int *Player::getId() const {
    return id;
}

void Player::setId(int *id) {
    Player::id = id;
}


// ASSIGNMENT 2
// get the number of troops in Player's reinforcement pool
int Player::getReinforcements() {
    return *reinforcements;
}

// set the number of troops in Player's reinforcement pool
void Player::setReinforcements(int n) {
    *reinforcements = n;
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

void invalidInput() {
    cout << "Invalid input, try again" << endl;
    //clear input stream
    cin.clear();
    cin.ignore();
}






