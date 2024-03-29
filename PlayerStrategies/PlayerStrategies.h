class Player; // forward declaration
class Territory; // forward declaration
#pragma once
#include "../Player/Player.h"
#include "../GameLog/LoggingObserver.h"
#include "../Map/Map.h"
#include <vector>
#include <ostream>

class PlayerStrategy {
protected:
    Player* p;
public:
    PlayerStrategy();
    PlayerStrategy(Player* player);
    PlayerStrategy(const PlayerStrategy& ps);
    virtual ~PlayerStrategy();

    void setPlayer(Player* newPlayer);
    Player* getPlayer();

    virtual bool issueOrder(LogObserver* observer) = 0;
    virtual vector<Territory *>* toAttack() = 0;
    virtual vector<Territory *>* toDefend() = 0;

};

class Neutral : public PlayerStrategy {
public:
    Neutral();
    Neutral(Player* player);
    Neutral(const Neutral& n);
    ~Neutral();

    // Assignment operator
    void operator= (Neutral const& n);

    // Stream operator
    friend ostream &operator<<(ostream &os, const Neutral& n);

    bool issueOrder(LogObserver* observer);
    vector<Territory *>* toAttack();
    vector<Territory *>* toDefend();
};

class Cheater : public PlayerStrategy {
public:
    Cheater();
    Cheater(Player* player);
    Cheater(const Cheater& c);
    ~Cheater();

    // Assignment operator
    void operator= (Cheater const& c);
    // Stream operator
    friend ostream &operator<<(ostream &os, const Cheater& c);

    bool issueOrder(LogObserver* observer);
    vector<Territory *>* toAttack();
    vector<Territory *>* toDefend();
};

class Human : public PlayerStrategy {
public:
    Human();
    Human(Player* player);
    Human(const Human& h);
    ~Human();

    // Assignment operator
    void operator= (Human const& h);
    // Stream operator
    friend ostream &operator<<(ostream &os, const Human& h);

    bool issueOrder(LogObserver* observer);
    vector<Territory *>* toAttack();
    vector<Territory *>* toDefend();
};

class Aggressive : public PlayerStrategy {
public:
    Aggressive();
    Aggressive(Player* player);
    Aggressive(const Aggressive& h);
    ~Aggressive();

    // Assignment operator
    void operator= (Aggressive const& a);
    // Stream operator
    friend ostream &operator<<(ostream &os, const Aggressive &a);

    bool issueOrder(LogObserver* observer);
    vector<Territory *>* toAttack();
    vector<Territory *>* toDefend();
    vector<Territory *>* toAttack(Territory*); //Territories to attack based on selected territory
    bool checkOpposingOrFree(vector<Territory *> *playerTerritories, Territory*);

    Territory * getTerrWithLargestArmy();
};

class Benevolent : public PlayerStrategy {

public:
    Benevolent();
    Benevolent(Player* player);
    Benevolent(const Benevolent& b);
    ~Benevolent();

    // Assignment operator
    void operator= (Benevolent const& b);
    // Stream operator
    friend ostream &operator<<(ostream &os, const Benevolent& b);

    bool issueOrder(LogObserver* observer);
    vector<Territory *>* toAttack() ;
    vector<Territory *>* toDefend();

    Territory* getTerrWithSmallestArmy();
};