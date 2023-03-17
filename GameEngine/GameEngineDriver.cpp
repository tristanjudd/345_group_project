#include "GameEngineDriver.h"
#include "GameEngine.h"
#include "../CommandProcessor/CommandProcessing.h"

int gameEngineDriver() {
    GameEngine *g = new GameEngine();
    CommandProcessor* cp = new CommandProcessor();
    Command *command;

    PHASE phase = START;
    while (true) {
        switch (phase) {
            case START:
                cout << "Start Phase" << endl;
                command = cp->getCommand(phase);  // will prompt user, and should not pass for anything other than 'loadmap <mapfile>' (in this phase)
                cout << *command << endl;  // just to show I did my part
                // actually execute the command & move to next phase. not sure how you wanna do this.
                //phase = g->start();
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
                cout << "NEW TURN \n" << endl;
                phase = g->mainGameLoop();
                break;
            case PLAYERS_ADDED:
                cout << "Add Players Phase" << endl;
                phase = g->addPlayers();
                break;
            case ASSIGN_REINFORCEMENT:
                cout << "ASSIGN REINFORCEMENTS PHASE" << endl;
                phase = g->reinforcementPhase();
                break;
            case ISSUE_ORDERS:
                cout << "ISSUE ORDERS PHASE" << endl;
                phase = g->issueOrdersPhase();
                break;
            case EXECUTE_ORDERS:
                cout << "EXECUTE ORDERS PHASE" << endl;
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