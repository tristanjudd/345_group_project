//
// Created by jay on 16/03/23.
//
#include <string>
#include <iostream>
#include<fstream>

using std::ofstream;
using std::string;
using std::endl;

#include "CommandProcessing.h"

// Command
// Constructors
Command::Command() {
    name = nullptr;
    argument = nullptr;
    effect = nullptr;
}

Command::Command(COMMAND cmd, LogObserver *observer) : Subject(observer) {
    name = new COMMAND(cmd);
    argument = nullptr;
    effect = nullptr;
}


Command::Command(COMMAND cmd, string &arg, LogObserver *observer) : Subject(observer) {
    name = new COMMAND(cmd);
    argument = new string(arg);
    effect = nullptr;
}

Command::Command(const Command &copy) {
    name = new COMMAND(*copy.getName());
    argument = new string(*copy.getArgument());
    effect = new string(*copy.getEffect());
}

Command::~Command() {
    name = nullptr;
    argument = nullptr;
    effect = nullptr;

    delete name;
    delete argument;
    delete effect;
    cout << "Command destructor called" << endl;
}

// Getters & Setters
COMMAND *Command::getName() const {
    return name;
}

string *Command::getArgument() const {
    return argument;
}

string *Command::getEffect() const {
    return effect;
}

void Command::setName(COMMAND newCmd) {
    name = new COMMAND(newCmd);
}

void Command::setArgument(const string &newArg) {
    argument = new string(newArg);
}

void Command::saveEffect(const string &newEffect) {
    effect = new string(newEffect);

    Notify(this);
}

// Operators
ostream &operator<<(ostream &os, COMMAND c) {
    switch (c) {
        case loadmap:
            os << "load map";
            break;
        case validatemap:
            os << "validate map";
            break;
        case addplayer:
            os << "add player";
            break;
        case gamestart:
            os << "game start";
            break;
        case replay:
            os << "replay";
            break;
        case quit:
            os << "quit";
            break;
    }

    return os;
}

ostream &operator<<(ostream &os, const Command &c) {
    os << "Command name: " << *c.getName() << endl;
    if (c.getArgument() != nullptr) {
        os << "Command arg: " << *c.getArgument() << endl;
    } else {
        os << "This command has no extra argument." << endl;
    }
    if (c.getEffect() != nullptr) {
        os << "Command effect: " << *c.getEffect() << endl;
    } else {
        os << "This command has no effect." << endl;
    }
    return os;
}

Command &Command::operator=(const Command &c) {
    if (this != &c) {
        name = c.getName();
        argument = c.getArgument();
        effect = c.getEffect();
    }

    return *this;
}

void Command::stringToLog() {

    //creating file string
    string filename = "../Log/gamelog.txt";
    ofstream outputFile;

    //checking if file exists
    ifstream exists(filename);

    if (exists.bad()) {
        outputFile.open(filename);
    }

    // Append data to the file
    outputFile.open(filename, std::ios_base::app);
    outputFile << "Saving Effect: " << this->getEffect() << endl;
    outputFile.close();
}


// CommandProcessor
// Constructors
CommandProcessor::CommandProcessor(LogObserver *observer) : Subject(observer) {
    commands = new vector<Command *>();
}

CommandProcessor::CommandProcessor(const CommandProcessor &copy) {
    commands = new vector<Command *>();
    for (Command *cmd: *copy.commands) {
        commands->push_back(new Command(*cmd));
    }
}

CommandProcessor::~CommandProcessor() {
    commands = nullptr;
    delete commands;
    cout << "CommandProcessor destructor called";
}

// Operators
ostream &operator<<(ostream &os, PHASE p) {
    switch (p) {
        case START:
            os << "start";
            break;
        case MAP_LOADED:
            os << "map loaded";
            break;
        case MAP_VALIDATED:
            os << "map validated";
            break;
        case PLAYERS_ADDED:
            os << "players added";
            break;
        case PLAY:
            os << "play";
            break;
        case ASSIGN_REINFORCEMENT:
            os << "assign reinforcement";
            break;
        case ISSUE_ORDERS:
            os << "issue orders";
            break;
        case EXECUTE_ORDERS:
            os << "execute orders";
            break;
        case WIN:
            os << "win";
            break;
        case END:
            os << "end";
            break;
    }

    return os;
}

CommandProcessor &CommandProcessor::operator=(const CommandProcessor &cp) {
    if (this != &cp) {
        commands->clear();
        for (Command *cmd: *cp.commands) {
            commands->push_back(cmd);
        }
    }

    return *this;
}

ostream &operator<<(ostream &os, const CommandProcessor &cp) {
    os << "CommandProcessor with commands: " << endl;
    for (Command *cmd: *cp.commands) {
        os << cmd;
    }

    return os;
}

// Methods
void CommandProcessor::saveCommand(Command *command) {
    this->commands->push_back(command);
    Notify(this);
}

string CommandProcessor::generateEffect(bool isValid, Command *cmd, PHASE currentPhase) {
    stringstream out{};

    if (isValid) {
        switch (*cmd->getName()) {
            case loadmap:
                out << "Loaded map " << *cmd->getArgument() << ".";
                break;
            case validatemap:
                out << "Validated map.";
                break;
            case addplayer:
                out << "Added player " << *cmd->getArgument() << ".";
                break;
            case gamestart:
                out << "Started game.";
                break;
            case replay:
                out << "Restarted the game loop.";
                break;
            case quit:
                out << "Quit the game.";
                break;
        }
    } else {
        out << "[ERROR] Cannot " << *cmd->getName() << " from phase " << currentPhase << endl;
    }

    return out.str();
}

bool CommandProcessor::validate(Command *cmd, PHASE currentPhase) {
    if (*cmd->getName() == COMMAND::loadmap) {
        if (currentPhase == PHASE::START || currentPhase == PHASE::MAP_LOADED) {
            return true;
        }
    } else if (*cmd->getName() == COMMAND::validatemap) {
        if (currentPhase == PHASE::MAP_LOADED) {
            return true;
        }
    } else if (*cmd->getName() == COMMAND::addplayer) {
        if (currentPhase == PHASE::MAP_VALIDATED || currentPhase == PHASE::PLAYERS_ADDED) {
            return true;
        }
    } else if (*cmd->getName() == COMMAND::gamestart) {
        if (currentPhase == PHASE::PLAYERS_ADDED) {
            return true;
        }
    } else if (*cmd->getName() == COMMAND::replay) {
        if (currentPhase == PHASE::WIN) {
            return true;
        }
    } else if (*cmd->getName() == COMMAND::quit) {
        if (currentPhase == PHASE::WIN) {
            return true;
        }
    }

    return false;
}

Command *CommandProcessor::readCommand(LogObserver* observer) {
    string newCommand{};

    while (true) {
        cout << "Please enter your command: ";
        getline(cin, newCommand);

        vector<string> commandTokens = MapLoader::getTokens(newCommand);

        if (commandTokens[0] == "loadmap") {
            return new Command(COMMAND::loadmap, commandTokens[1], observer);
        } else if (newCommand == "validatemap") {
            return new Command(COMMAND::validatemap, observer);
        } else if (commandTokens[0] == "addplayer") {
            return new Command(COMMAND::addplayer, commandTokens[1], observer);
        } else if (newCommand == "gamestart") {
            return new Command(COMMAND::gamestart, observer);
        } else if (newCommand == "replay", observer) {
            return new Command(COMMAND::replay, observer);
        } else if (newCommand == "quit") {
            return new Command(COMMAND::quit, observer);
        } else {
            cout << "Not a valid command. Please try again." << endl;
        }
    }
}

Command *CommandProcessor::getCommand(PHASE currentPhase, LogObserver* observer) {
    Command *command = CommandProcessor::readCommand(observer);
    Command * c = new Command(COMMAND::validatemap, observer);
    bool cmdIsValid = validate(command, currentPhase);

    command->saveEffect(generateEffect(cmdIsValid, command, currentPhase));

    saveCommand(command);
    return command;
}

void CommandProcessor::stringToLog() {

    //creating file string
    string filename = "../Log/gamelog.txt";
    ofstream outputFile;

    //checking if file exists
    ifstream exists(filename);

    if (exists.bad()) {
        outputFile.open(filename);
    }

    // Append data to the file
    outputFile.open(filename, std::ios_base::app);
    outputFile << "Saving Command: " << this->commands->back()->getName() << endl;
    outputFile.close();
}


