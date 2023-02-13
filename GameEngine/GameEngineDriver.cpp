#include "GameEngineDriver.h"
#include "GameEngine.h"
#include "../Map/MapDriver.h"

int gameEngineDriver() {
    GameEngine::start();
   // mapDriver();
    GameEngine::addPlayers();
    cout << "Assigning countries to players" << endl;
    int *winner = new int(-1);
    while (*winner == -1) {
        cout << "Assign reinforcements to territories" << endl;
        cout << "Issuing orders" << endl;
        cout << "Executing orders" << endl;
        *winner = 0;
    }
    cout << "Player " << *winner << " wins!" << endl;
    cout << "Game Over" << endl;
    cout << "Play again? (y/n): ";
    char playAgain;
    cin >> playAgain;
    while (true) {
        if (playAgain == 'y') {
            gameEngineDriver();
        } else if (playAgain != 'n') {
            cout << "Invalid input" << endl << "Try again" << endl;
        }
        break;
    }
    cout << "Goodbye!" << endl;
    return 0;
}