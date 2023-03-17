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
    virtual void Update() = 0;

protected:
    Observer();
};

class Subject {

public:
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify();
    Subject();
    ~Subject();
private:

    list<Observer*> * _observers;

};





#endif //WARZONE_LOGGINGOBSERVER_H
