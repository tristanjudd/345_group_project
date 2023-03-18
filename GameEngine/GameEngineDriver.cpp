#include "GameEngineDriver.h"

int gameEngineDriver() {
    GameEngine *game = new GameEngine();
    CommandProcessor *cp = new CommandProcessor();
    Command *command;
    PHASE phase = START;
    Map *map;

    game->startupPhase(game, cp, command, phase, map);
}