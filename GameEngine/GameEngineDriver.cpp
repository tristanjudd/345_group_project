#include "GameEngineDriver.h"

int gameEngineDriver(GAME_MODE gm, const string &fileArg) {

    LogObserver *observer = new LogObserver();
    GameEngine *game = new GameEngine(observer);

    // use different command processor (file/console)
    CommandProcessor *cp;
    if (gm == GAME_MODE::console) {
        cp = new CommandProcessor(observer);
        cout << "Running Warzone in console mode." << endl;
    } else if (gm == GAME_MODE::file) {
        cp = new FileCommandProcessorAdapter(fileArg, observer);
        cout << "Running Warzone in file mode." << endl;
    }

    Command *command;
    PHASE phase;

    phase = START;
    game->startupPhase(game, cp, command, phase, observer);

//    phase = CHECK_WIN;
//    game->initGameDummy(observer);
//    game->initGameEndDummy(observer);
//    game->mainGameLoop(game, phase, observer);


}