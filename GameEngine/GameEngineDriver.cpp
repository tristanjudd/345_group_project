#include "GameEngineDriver.h"

int gameEngineDriver(GAME_MODE gm, const string& fileArg) {
    GameEngine *game = new GameEngine();

    // use different command processor (file/console)
    CommandProcessor *cp;
    if (gm == GAME_MODE::console) {
        cp = new CommandProcessor();
        cout << "Running Warzone in console mode." << endl;
    } else if (gm == GAME_MODE::file) {
        cp = new FileCommandProcessorAdapter(fileArg);
        cout << "Running Warzone in file mode." << endl;
    }

    Command *command;
    PHASE phase;

    phase = START;
    game->startupPhase(game, cp, command, phase);

//    phase = ASSIGN_REINFORCEMENT;
//    game->mainGameLoop(game, phase);

    // TRISTAN: THESE METHODS ARE FOR DEMO PURPOSES
    // initGameDummy();
    // initGameEndDummy();
    // END OF DEMO METHODS
}