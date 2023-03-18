#include "GameEngineDriver.h"

int gameEngineDriver() {
    GameEngine *game = new GameEngine();
    CommandProcessor *cp = new CommandProcessor();
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