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
    argument = new string("");
    effect = nullptr;
}

Command::Command(COMMAND cmd, LogObserver *observer) : Subject(observer) {
    name = new COMMAND(cmd);
    argument = new string("");
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


// CommandProcessing
// Constructors
CommandProcessor::CommandProcessor() {
    commands = new vector<Command *>();
}

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
    cout << "CommandProcessing destructor called";
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
    os << "CommandProcessing with commands: " << endl;
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
        out << "[ERROR] Cannot " << *cmd->getName() << " from phase " << currentPhase;
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

Command *CommandProcessor::parseCommand(string newCommand, LogObserver *observer) {
    vector<string> commandTokens = MapLoader::getTokens(newCommand);

    if (commandTokens[0] == "loadmap") {
        if (commandTokens.size() == 1) {  // no argument specified
            return new Command(COMMAND::loadmap, *new string(""), observer);
        } else {
            return new Command(COMMAND::loadmap, commandTokens[1], observer);
        }
    } else if (commandTokens[0] == "validatemap") {
        return new Command(COMMAND::validatemap, observer);
    } else if (commandTokens[0] == "addplayer") {
        if (commandTokens.size() == 1) {  // no argument specified
            return new Command(COMMAND::addplayer, *new string(""), observer);
        } else {
            return new Command(COMMAND::addplayer, commandTokens[1], observer);
        }
    } else if (commandTokens[0] == "gamestart") {
        return new Command(COMMAND::gamestart, observer);
    } else if (commandTokens[0] == "replay") {
        return new Command(COMMAND::replay, observer);
    } else if (commandTokens[0] == "quit") {
        return new Command(COMMAND::quit, observer);
    } else {
        return new Command();
    }
}

Command* CommandProcessor::readCommand(LogObserver* observer) {
    string consoleCommand{};

    while (true) {
        cout << "Please enter your command: ";
        getline(cin, consoleCommand);

        Command* command = parseCommand(consoleCommand, observer);
        if (command->getName() != nullptr) {
            return command;
        } else {
            cout << "Not a valid command. Please try again." << endl;
        }
    }
}

Command* CommandProcessor::getCommand(PHASE currentPhase, CommandProcessor* commandProcessor, LogObserver* observer) {
    while (true) {
        Command *command = commandProcessor->readCommand(observer);
        bool cmdIsValid = validate(command, currentPhase);
        command->saveEffect(generateEffect(cmdIsValid, command, currentPhase));
        saveCommand(command);

        if (cmdIsValid) {
            return command;
        } else {
            cout << *command->getEffect() << endl;
        }
    }
}

// FileLineReader
// constructors
FileLineReader::FileLineReader() {
    lines = new vector<string>();
}

FileLineReader::FileLineReader(const string& filePath) {
    lines = new vector<string>();

    ifstream file(filePath);
    string line;
    while (getline(file, line)) {
        lines->push_back(line);
    }
}

FileLineReader::FileLineReader(const FileLineReader &copy) {
    lines = new vector<string>();
    for (string line : *copy.lines) {
        lines->push_back(line);
    }
}

FileLineReader::~FileLineReader() {
    lines = nullptr;
    delete lines;
    cout << "FileLineReader destructor called";
}

// operators
FileLineReader &FileLineReader::operator=(const FileLineReader &flr) {
    if (this != &flr) {
        lines->clear();
        for (string line : *flr.lines) {
            lines->push_back(line);
        }
    }

    return *this;
}

ostream &operator<<(ostream &os, const FileLineReader &flr) {
    os << "FileLineReader with lines: " << endl;
    for (string line : *flr.lines) {
        os << line;
    }

    return os;
}

// methods
string FileLineReader::readLineFromFile(int l) {
    return lines->at(l);
}

// FileCommandProcessorAdapter
// constructors
FileCommandProcessorAdapter::FileCommandProcessorAdapter() {
    flr = new FileLineReader();
    currentLine = new int{0};  // start at 1st line
}
FileCommandProcessorAdapter::FileCommandProcessorAdapter(LogObserver* observer): CommandProcessor(observer) {
    flr = new FileLineReader();
    currentLine = new int{0};  // start at 1st line
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const string& cmdFilePath, LogObserver* observer): CommandProcessor(observer){
    flr = new FileLineReader(cmdFilePath);
    currentLine = new int{0};
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter &copy) : CommandProcessor(){
    flr = new FileLineReader(*copy.flr);
    currentLine = new int(*copy.currentLine);
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    flr = nullptr;
    currentLine = nullptr;

    delete flr;
    delete currentLine;
    cout << "FileCommandProcessorAdapter destructor called";
}

// operators
FileCommandProcessorAdapter &FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter &fcpa) {
    if (this != &fcpa) {
        flr = fcpa.flr;
        currentLine = fcpa.currentLine;
    }

    return *this;
}

ostream &operator<<(ostream &os, const FileCommandProcessorAdapter &fcpa) {
    os << "FileCommandProcessorAdapter file line reader: " << *fcpa.flr << endl;
    os << "FileCommandProcessorAdapter current line: " << *fcpa.currentLine << endl;

    return os;
}

// methods
Command *FileCommandProcessorAdapter::readCommand(LogObserver *observer) {
    Command *command = parseCommand(flr->readLineFromFile(*currentLine), observer);
    *currentLine = *currentLine + 1;
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


