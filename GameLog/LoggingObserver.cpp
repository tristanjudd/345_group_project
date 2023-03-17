//
// Created by Kojo on 3/17/2023.
//

#include "LoggingObserver.h"


//Observer Functions
Observer::Observer() {}

Observer::~Observer() {}


//Subject Functions
Subject::Subject(){
    //_observers = new list<Observer*>;
}
Subject::~Subject(){
    delete observer;
}


void Subject::Notify(ILoggable* loggable) {
    observer->Update(loggable);
}