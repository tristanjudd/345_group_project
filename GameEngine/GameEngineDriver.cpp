#include "GameEngineDriver.h"
#include "GameEngine.h"

int gameEngineDriver() {
    GameEngine *g = new GameEngine();
    PHASE phase = START;
    while (true) {
        switch (phase) {
            case START:
                cout << "Start Phase" << endl;
                phase = g->start();
                break;
            case MAP_LOADED:
                cout << "Load Map Phase" << endl;
                phase = g->loadMap();
                break;
            case MAP_VALIDATED:
                cout << "Validate Map Phase" << endl;
                phase = g->validateMap();
                break;
            case PLAY:
                cout << "New turn" << endl;
                phase = g->mainGameLoop();
                break;
            case PLAYERS_ADDED:
                cout << "Add Players Phase" << endl;
                phase = g->addPlayers();
                break;
            case ASSIGN_REINFORCEMENT:
                cout << "Assign Reinforcement Phase" << endl;
                phase = g->reinforcementPhase();
                break;
            case ISSUE_ORDERS:
                cout << "Issue Orders Phase" << endl;
                phase = g->issueOrdersPhase();
                break;
            case EXECUTE_ORDERS:
                cout << "Execute Orders Phase" << endl;
                phase = g->executeOrdersPhase();
                break;
            case WIN:
                cout << "Win Phase" << endl;
                phase = g->win();
                break;
            case END:
                cout << "End Phase" << endl;
                g->end();
                return 0;
            default:
                cout << "Invalid phase" << endl;
                break;
        }
    }
}