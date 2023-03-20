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

// Copy constructor for Subject class
Subject::Subject(const Subject &copy) {
    // Copy the observer pointer from the original object
    observer = copy.observer;

    // Downcast the observer pointer to a LogObserver*
    LogObserver* logObserver = dynamic_cast<LogObserver*>(observer);


    observer = new LogObserver(*logObserver);

}

Subject::~Subject() {

    delete observer;
}


void Subject::Notify(ILoggable *loggable) {
    observer->Update(loggable);
}

std::ostream &operator<<(std::ostream &os, const Subject &subject) {
    os << "observer: " << subject.observer;
    return os;
}

//LogObserver Functions

// Copy constructor for LogObserver class
LogObserver::LogObserver(const LogObserver &copy) : Observer(copy) {
}

void LogObserver::Update(ILoggable *loggable) {

    loggable->stringToLog();
}

LogObserver::LogObserver() {}

LogObserver::~LogObserver() {}


