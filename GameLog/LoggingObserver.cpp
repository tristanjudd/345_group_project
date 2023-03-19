//
// Created by Kojo on 3/17/2023.
//

#include "LoggingObserver.h"
#include <string>
#include <iostream>
#include <fstream>

using std::ofstream;
using std::string;

//Observer Functions
Observer::Observer() {}

Observer::~Observer() {}


//Subject Functions
Subject::Subject() {
    //_observers = new list<Observer*>;
}

Subject::Subject(Observer *observer) {

    this->observer = observer;
}

Subject::~Subject() {

    delete observer;
}


void Subject::Notify(ILoggable *loggable) {
    observer->Update(loggable);
}

void ILoggable::stringToLog() {}

//LogObserver Functions

void LogObserver::Update(ILoggable *loggable) {

    loggable->stringToLog();
}

LogObserver::LogObserver() {}

LogObserver::~LogObserver() {}

ofstream checkFile() {

    //creating file string
    string filename = "../Log/gamelog.txt";
    ofstream outputFile;

    //checking if file exists
    ofstream exists(filename);

    if (exists.bad()) {
        outputFile.open(filename);
    }

    return outputFile;
}