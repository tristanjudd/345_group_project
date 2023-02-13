#include "GameEngine.h"

void GameEngine::start() {
    cout << "Welcome to our bootleg Warzone!" << endl;
}

void GameEngine::addPlayers() {
    cout << "How many players would you like to add: ";
    int numPlayers;
    cin >> numPlayers;
    vector<Player*> players;
    for (int i = 0; i < numPlayers; i++) {
        Player* p = new Player(i);
        players.push_back(p);
        cout << "Player " << i+1 << " added" << endl;
    }
}