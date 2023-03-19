#ifndef WARZONE_GAMEENGINEDRIVER_H
#define WARZONE_GAMEENGINEDRIVER_H

#include <iostream>
using std::iostream;

#include "../CommandProcessing/CommandProcessing.h"

enum GAME_MODE {
    console,
    file
};

int gameEngineDriver(GAME_MODE gm, const string& fileArg);

#endif //WARZONE_GAMEENGINEDRIVER_H
