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

    // TRISTAN: COMMENT THESE OUT FOR GameEngine DRIVER
    // phase = START;
    // game->startupPhase(game, cp, command, phase);
    // END OF COMMENT

    // TRISTAN: THESE ARE FOR GameEngine DRIVER
    phase = CHECK_WIN;
    //game->initGameDummy();
    game->initGameEndDummy();
    game->mainGameLoop(game, phase);
    // END OF COMMENT

    // TRISTAN: THESE METHODS ARE FOR DEMO PURPOSES

    // initGameEndDummy();
    // END OF DEMO METHODS
}