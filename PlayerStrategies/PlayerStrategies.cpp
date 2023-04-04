#include "PlayerStrategies.h"
#include "../Orders/Orders.h"
#include <set>

PlayerStrategy::PlayerStrategy() {}

PlayerStrategy::PlayerStrategy(Player* player) {
    p = player;
}

PlayerStrategy::~PlayerStrategy() {
    delete p;
    p = nullptr;
}

void PlayerStrategy::setPlayer(Player* newPlayer) {
    p = newPlayer;
}

Player* PlayerStrategy::getPlayer() {
    return p;
}

Human::Human() {}

Human::Human(Player* player) : PlayerStrategy(player) {}

Human::~Human() {

}

bool Human::issueOrder(LogObserver* observer) {

    vector<Territory *> playerTerritories = *(toDefend());
    int reinforcements = p->getReinforcements();
    int id = *(p->getId());
    OrderList* orders = p->getOrders();


    // If there are troops to deploy, must be done before other orders can be issued
    if (reinforcements > 0) {
        // print remaining reinforcement pool
        cout << "Player " << id << " has " << reinforcements << " troops to assign to the following territories: "
             << endl;
        // print countries to deploy to
        for (int i = 0; i < playerTerritories.size(); i++) {
            cout << (i + 1) << ". " << *(playerTerritories.at(i)->getTerritoryName()) << endl;
        }

        // get input for territory to deploy to
        cout << "Enter the number of the territory to which you wish to deploy troops: " << endl;
        string input;
        cin >> input;

        int validTerritory = string_is_num_in_range(input, 1, playerTerritories.size());

        while (!validTerritory) {
            invalidInput();

            cin >> input;
            validTerritory = string_is_num_in_range(input, 1, playerTerritories.size());
        }

        if (validTerritory) {
            // Get number of territory (index in player's territories vector)
            int territoryNum = string_is_num_in_range(input, 1, playerTerritories.size());
            // loop until valid input is received
            while (true) {
                // get user input
                string numOfTroops;
                cout << "Enter the number of troops you wish to assign to "
                     << *(playerTerritories.at(validTerritory - 1)->getTerritoryName()) << ": " << endl;
                cin >> numOfTroops;

                int validNumOfTroops = string_is_num_in_range(numOfTroops, 1, reinforcements);

                // if input valid add order to order list
                if (validNumOfTroops) {
                    // Create an order and add to order list
                    Order *deploy = new Deploy(p, validNumOfTroops, playerTerritories.at(validTerritory - 1), observer);
                    orders->Add(deploy);

                    cout << validNumOfTroops << " troops assigned to "
                         << *(playerTerritories.at(validTerritory - 1)->getTerritoryName()) << endl;

                    // decrement player's reinforcement pool
                    p->setReinforcements(reinforcements - validNumOfTroops);
                    // end get valid input loop, returning to deploy troops loop
                    return true;
                    // player enters invalid input
                } else {
                    cout << "got here" << endl;
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
            cout << "> ";

            cin >> choice;
            int validInput = string_is_num_in_range(choice, 1, 4);

            if (validInput) {

                switch (validInput) {
                    // Case defend territory
                    case 1: {
                        cout << id << " has the following territories to defend: " << endl;
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

                                        while (true) {
                                            cin >> howManyTroops;
                                            int validHowManyTroops = string_is_num_in_range(howManyTroops, 1, 999999);

                                            if (validHowManyTroops) {
                                                cout << "Defend "
                                                     << *(defendable.at(validDefend - 1)->getTerritoryName())
                                                     << " from "
                                                     << *(defendable.at(validDefendFrom - 1)->getTerritoryName())
                                                     << " with " << validHowManyTroops << " troops." << endl;
                                                // Issue order
                                                Order *advance = new Advance(p,
                                                                             validHowManyTroops,
                                                                             defendable.at(validDefendFrom - 1),
                                                                             defendable.at(validDefendFrom - 1),
                                                                             observer);
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
                                    if (std::find(playerTerritories.begin(), playerTerritories.end(), t) != playerTerritories.end()) {
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
                                                string nameAttack = *(attackable.at(
                                                        validAttack - 1)->getTerritoryName());
                                                string nameAttackFrom = *(attackingTerritories.at(
                                                        validAttackingTerritory - 1)->getTerritoryName());
                                                cout << "Attacking " << nameAttack << " from " << nameAttackFrom
                                                     << " with " << validNumTroops << " troops." << endl;

                                                // Issue order
                                                Order *advance = new Advance(p,
                                                                             validNumTroops,
                                                                             attackable.at(validAttack - 1),
                                                                             attackingTerritories.at(
                                                                                     validAttackingTerritory - 1), observer);
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
                        vector<Card *> currentHand = p->getHand()->getHand();
                        // check if hand is empty, return if so
                        if (currentHand.size() == 0) {
                            cout << "You have no cards in your hand" << endl;
                            return true;
                        }

                        // else display cards in hand
                        cout << "You have the following cards to play: " << endl;

                        for (int i = 0; i < currentHand.size(); i++) {
                            CardType currentCard = currentHand.at(i)->getType();

                            switch (currentCard) {
                                case 0:
                                    cout << (i + 1) << ". Bomb" << endl;
                                    break;
                                case 1:
                                    cout << (i + 1) << ". Reinforcement" << endl;
                                    break;
                                case 2:
                                    cout << (i + 1) << ". Blockade" << endl;
                                    break;
                                case 3:
                                    cout << (i + 1) << ". Airlift" << endl;
                                    break;
                                case 4:
                                    cout << (i + 1) << ". Diplomacy" << endl;
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
                                CardType cardType = currentHand.at(validCard - 1)->getType();

                                switch (cardType) {
                                    //Bomb
                                    case 0: {
                                        cout << "You can bomb: " << endl;

                                        for (int i = 0; i < playerTerritories.size(); i++) {
                                            cout << (i + 1) << ". " << *(toAttack()->at(i)->getTerritoryName()) << endl;
                                        }

                                        cout << "What territory do you want to bomb? " << endl;
                                        string toBomb;
                                        int validBomb;
                                        // get valid input
                                        while (true) {
                                            cin >> toBomb;
                                            validBomb = string_is_num_in_range(toBomb, 1, toAttack()->size());

                                            if (validBomb) {
                                                break;
                                            } else {
                                                invalidInput();
                                            }
                                        }
                                        cout << "Order to bomb " << validBomb << " issued" << endl;
                                        // create bomb order
                                        Order *bomb = new Bomb(p, toAttack()->at(validBomb - 1), observer);
                                        // add to order list
                                        orders->Add(bomb);

                                        break;
                                    } // end case 0
                                        //Reinforcement
                                    case 1: {
                                        cout << "What territory do you want to send reinforcements to? " << endl;

                                        // print player territories
                                        for (int i = 0; i < playerTerritories.size(); i++) {
                                            cout << (i + 1) << ". " << *(playerTerritories.at(i)->getTerritoryName())
                                                 << endl;
                                        }

                                        string toReinforce;
                                        int validReinforce;
                                        while (true) {
                                            cin >> toReinforce;
                                            validReinforce = string_is_num_in_range(toReinforce, 1,
                                                                                    playerTerritories.size());

                                            if (validReinforce) {
                                                break;
                                            } else {
                                                invalidInput();
                                            }

                                        }

                                        cout << "Sending 5 reinforcements to "
                                             << *(playerTerritories.at(validReinforce - 1)->getTerritoryName());

                                        // create order
                                        Order *reinforce = new Deploy(p, 5, playerTerritories.at(validReinforce - 1), observer);
                                        // add to order list
                                        orders->Add(reinforce);

                                        break;
                                    } // end case 1
                                        // Blockade
                                    case 2: {
                                        cout << "You can blockade: " << endl;
                                        // print player's territories
                                        for (int i = 0; i < playerTerritories.size(); i++) {
                                            cout << (i + 1) << ". " << *(playerTerritories.at(i)->getTerritoryName())
                                                 << endl;
                                        }

                                        cout << "What territory do you want to blockade? ";

                                        string toBlockade;
                                        int validBlockade;
                                        while (true) {
                                            cin >> toBlockade;
                                            validBlockade = string_is_num_in_range(toBlockade, 1,
                                                                                   playerTerritories.size());

                                            if (validBlockade) {
                                                break;
                                            } else {
                                                invalidInput();
                                            }
                                        }
                                        cout << "Issued order to blockade " << validBlockade << endl;

                                        // create order
                                        Order *blockade = new Blockade(p, playerTerritories.at(validBlockade - 1), observer);
                                        // add order to list
                                        orders->Add(blockade);

                                        break;
                                    } // end case 2
                                        // Airlift
                                    case 3: {
                                        cout << "Where do you want to airlift from?" << endl;
                                        for (int i = 0; i < playerTerritories.size(); i++) {
                                            cout << (i + 1) << ". " << *(playerTerritories.at(i)->getTerritoryName())
                                                 << endl;
                                        }

                                        string airliftFrom;
                                        while (true) {
                                            cin >> airliftFrom;
                                            int validAirliftFrom = string_is_num_in_range(airliftFrom, 1,
                                                                                          playerTerritories.size());

                                            if (validAirliftFrom) {
                                                cout << "How many troops to airlift? ";

                                                string troopsToAirlift;
                                                while (true) {
                                                    cin >> troopsToAirlift;
                                                    int validTroopsToAirlift = string_is_num_in_range(troopsToAirlift,
                                                                                                      1, 999999);

                                                    if (validTroopsToAirlift) {
                                                        cout << "Airlift troops to which territory? ";

                                                        string airliftTo;

                                                        while (true) {
                                                            cin >> airliftTo;
                                                            int validAirliftTo = string_is_num_in_range(airliftTo, 1,
                                                                                                        playerTerritories.size());

                                                            if (validAirliftTo) {
                                                                cout << "Airlift " << validTroopsToAirlift
                                                                     << " troops form "
                                                                     << *(playerTerritories.at(
                                                                             validAirliftFrom - 1)->getTerritoryName())
                                                                     << " to "
                                                                     << *(playerTerritories.at(
                                                                             validAirliftTo - 1)->getTerritoryName())
                                                                     << endl;
                                                                // issue order
                                                                Order *airlift = new Airlift(
                                                                        p,
                                                                        validTroopsToAirlift,
                                                                        playerTerritories.at(validAirliftFrom - 1),
                                                                        playerTerritories.at(validAirliftTo - 1),
                                                                        observer
                                                                );
                                                                orders->Add(airlift);

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
                                        int validDiplomacyTarget;

                                        while (true) {
                                            cin >> diplomacyTarget;
                                            validDiplomacyTarget = string_is_num_in_range(diplomacyTarget, 1, 9999);

                                            if (validDiplomacyTarget) {
                                                break;
                                            } else {
                                                invalidInput();
                                            }
                                        }

                                        cout << "Using diplomacy on player " << validDiplomacyTarget << endl;

                                        // create order
                                        Order *diplomacy = new Negotiate(p, validDiplomacyTarget, observer);
                                        // add to order list
                                        orders->Add(diplomacy);

                                        break;
                                    } // end case 4

                                } // end of switch

                                // play card
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

vector<Territory* >* Human::toAttack() {
    set<Territory *> attackable;
    vector<Territory *>* territories = p->getPlayerTerritories();
    // go through each of player's territories
    for (Territory *t: *territories) {
        // for each territory, go through each of its bordering territories
        for (Territory *bordering: *(t->getBorderedTerritories())) {
            // if it doesn't belong to the player, add it to the set of attackable territories
            if (std::find(territories->begin(), territories->end(), bordering) == territories->end()) {
                attackable.insert(bordering);
            }
        }
    }

    // convert set to vector
    vector<Territory *> *attackableVector = new vector<Territory *>;
    for (Territory *t: attackable) {
        attackableVector->push_back(t);
    }

    return attackableVector;
}

vector<Territory* >* Human::toDefend() {
    return p->getPlayerTerritories();
}