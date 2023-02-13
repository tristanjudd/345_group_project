#include "GameEngine.h"

PHASE GameEngine::start() {
    cout << "Welcome to our bootleg Warzone!" << endl;
    winner = new int(-1);
    return MAP_LOADED;
}

PHASE GameEngine::loadMap() {
    cout << "Loading map..." << endl;
    cout << "Map loaded" << endl;
    while (true) {
        cout << "Load another map? (y/n): ";
        string loadAnotherMap;
        cin >> loadAnotherMap;
        if (loadAnotherMap == "y") {
            return MAP_LOADED;
        } else if (loadAnotherMap == "n") {
            return MAP_VALIDATED;
        }
        cout << "Invalid input" << endl << "Try again" << endl;
    }
}

PHASE GameEngine::validateMap() {
    cout << "Validating map..." << endl;
    cout << "Map validated" << endl;
    while (true) {
        cout << "Validate another map? (y/n): ";
        string validateAnotherMap;
        cin >> validateAnotherMap;
        if (validateAnotherMap == "y") {
            return MAP_VALIDATED;
        } else if (validateAnotherMap == "n") {
            return PLAYERS_ADDED;
        }
        cout << "Invalid input" << endl << "Try again" << endl;
    }
}

PHASE GameEngine::addPlayers() {
    int numPlayers;
    cout << "How many players would you like to add: ";
    cin >> numPlayers;
    if (numPlayers < 1 || !isdigit(numPlayers) == 0) {
        cout << "Invalid number of players" << endl;
        cin.clear();
        cin.ignore(100, '\n');
        return PLAYERS_ADDED;
    }
    cout << "Players created" << endl;
    return ASSIGN_REINFORCEMENT;
}

PHASE GameEngine::assignReinforcements() {
    while (true) {
        cout << "Assign reinforcements" << endl;
        while (true) {
            cout << "Continue? (y/n): ";
            string continueAssigningReinforcements;
            cin >> continueAssigningReinforcements;
            if (continueAssigningReinforcements == "y") {
                return ASSIGN_REINFORCEMENT;
            } else if (continueAssigningReinforcements == "n") {
                return ISSUE_ORDERS;
            }
            cout << "Invalid input" << endl << "Try again" << endl;
            cin.clear();
            cin.ignore();
        }
    }
}

PHASE GameEngine::issueOrders() {
    while (true) {
        cout << "Issue orders" << endl;
        while (true) {
            cout << "Continue? (y/n): ";
            string continueIssuingOrders;
            cin >> continueIssuingOrders;
            if (continueIssuingOrders == "y") {
                return ISSUE_ORDERS;
            } else if (continueIssuingOrders == "n") {
                return EXECUTE_ORDERS;
            }
            cout << "Invalid input" << endl << "Try again" << endl;
            cin.clear();
            cin.ignore();
        }
    }
}

PHASE GameEngine::executeOrders() {
    while (true) {
        cout << "Execute orders" << endl;
        while (true) {
            if (*winner != -1) {
                return WIN;
            }
            cout << "Continue? (y/n): ";
            string continueExecutingOrders;
            cin >> continueExecutingOrders;
            if (continueExecutingOrders == "y") {
                return EXECUTE_ORDERS;
            } else if (continueExecutingOrders == "n") {
                return ASSIGN_REINFORCEMENT;
            } else if (continueExecutingOrders == "w") { //simulate winner
                return WIN;
            }
            cout << "Invalid input" << endl << "Try again" << endl;
        }
    }
}

PHASE GameEngine::win() {
    cout << "Player " << *winner << " wins!" << endl;
    cout << "Game Over" << endl;
    while (true) {
        cout << "Play again? (y/n): ";
        string playAgain;
        cin >> playAgain;
        if (playAgain == "y") {
            return START;
        } else if (playAgain == "n") {
            cout << "Goodbye!" << endl;
            return END;
        }
        cout << "Invalid input" << endl << "Try again" << endl;
    }
}

void GameEngine::end() {
    cout << "Bye again" << endl;
}
