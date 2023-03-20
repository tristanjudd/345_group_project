//
// Created by Kojo on 3/19/2023.
//

#include "../GameEngine/GameEngineDriver.h"

int logDriver(int argc, char *argv[]){

    try {
        if (string(argv[1]) == "-console") {
            gameEngineDriver(GAME_MODE::console, "");
        } else if (string(argv[1]) == "-file"){
            gameEngineDriver(GAME_MODE::file, argv[2]);
        } else {
            throw std::runtime_error("Invalid command line arguments.");
        }
    } catch (const std::exception& e) {
        cout << "[ERROR]: " << e.what() << "... Exiting program.";
        return -1;
    }


}