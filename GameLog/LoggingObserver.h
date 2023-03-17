//
// Created by Kojo on 3/17/2023.
//

#ifndef WARZONE_LOGGINGOBSERVER_H
#define WARZONE_LOGGINGOBSERVER_H


#include <list>

using std::list;

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
    ~Subject();
private:

    Observer * observer;

};





#endif //WARZONE_LOGGINGOBSERVER_H
