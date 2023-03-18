//
// Created by jay on 16/03/23.
//

#ifndef WARZONE_COMMANDPROCESSING_H
#define WARZONE_COMMANDPROCESSING_H

#include <vector>
using std::vector;
#include <string>
using std::string;
#include <map>
using std::map;
#include <iostream>
using std::cin;
using std::getline;
using std::cout;
using std::endl;
#include <sstream>
using std::stringstream;

#include "../GameEngine/GameEngine.h"

enum COMMAND {
    loadmap,
    validatemap,
    addplayer,
    gamestart,
    replay,
    quit
};

class Command {
private:
    COMMAND *name;
    string *argument;
    string *effect;
public:
    // constructors
    Command();
    Command(COMMAND cmd);
    Command(COMMAND cmd, string& arg);
    Command(const Command &copy);
    ~Command();

    // operators
    Command& operator=(const Command& c);
    friend ostream& operator<<(ostream& os, PHASE p);
    friend ostream& operator<<(ostream& os, COMMAND c);  // not to be confused with the Command...
    friend ostream& operator<<(ostream& os, const Command& c);

    // getters & setters
    COMMAND* getName() const;
    string* getArgument() const;
    string* getEffect() const;
    void setName(COMMAND newCmd);
    void setArgument(const string& newArg);
    void saveEffect(const string& newEffect);
};

class CommandProcessor {
private:
    vector<Command*> *commands;

    // methods
    static string generateEffect(bool, Command *cmd, PHASE currentPhase);

    void saveCommand(Command *cmd);
public:
    // constructors
    CommandProcessor();
    CommandProcessor(const CommandProcessor &copy);
    ~CommandProcessor();

    // operators
    CommandProcessor& operator=(const CommandProcessor& cp);
    friend ostream& operator<<(ostream& os, const CommandProcessor& cp);

    // methods
    static bool validate(Command* cmd, PHASE currentPhase);
    static Command* readCommand();

    Command* getCommand(PHASE currentPhase);
};

// TODO IMPLEMENT THIS & ADD ALL THE BS STUFF THEY WANT FOR CLASS (STREAM INSERTION, COPY, DESTRUCTOR ETC.)
class FileCommandProcessorAdapter {

};


#endif //WARZONE_COMMANDPROCESSING_H
