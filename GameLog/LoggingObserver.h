//
// Created by Kojo on 3/17/2023.
//

#ifndef WARZONE_LOGGINGOBSERVER_H
#define WARZONE_LOGGINGOBSERVER_H
#include <iostream>
#include <fstream>

using std::ofstream;

class ILoggable {

public:

    virtual void stringToLog() = 0;
};


class Observer {

public:
    ~Observer();
    virtual void Update(ILoggable* loggable) = 0;

protected:
    Observer();
};

class Subject {

public:

    virtual void Notify(ILoggable* loggable);
    Subject();
    Subject(Observer* observer);
    ~Subject();
private:

    Observer * observer;

};

class LogObserver: public Observer
{
public:
    LogObserver();

    void Update(ILoggable* loggable);
    ~LogObserver();
};


ofstream checkFile();




#endif //WARZONE_LOGGINGOBSERVER_H
