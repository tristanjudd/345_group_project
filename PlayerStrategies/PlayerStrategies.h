#pragma once
#include "../Player/Player.h"
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

    virtual bool issueOrder() = 0;
    virtual vector<Territory *>* toAttack() = 0;
    virtual vector<Territory *>* toDefend() = 0;

};

//class Neutral : PlayerStrategy {
//    Neutral();
//    Neutral(Neutral* neutral);
//    Neutral(const Neutral& n);
//    ~Neutral();
//
//    // Assignment operator
//    void operator= (Neutral const& n);
//    // Stream operator
//    friend ostream &operator<<(ostream &os, const Neutral& n);
//
//    bool issueOrder();
//    vector<Territory *>* toAttack();
//    vector<Territory *>* toDefend();
//};

//class Cheater : PlayerStrategy {
//    Cheater();
//    Cheater(Cheater* cheater);
//    Cheater(const Cheater& c);
//    ~Cheater();
//
//    // Assignment operator
//    void operator= (Cheater const& c);
//    // Stream operator
//    friend ostream &operator<<(ostream &os, const Cheater& c);
//
//    bool issueOrder();
//    vector<Territory *>* toAttack();
//    vector<Territory *>* toDefend();
//};

class Human : PlayerStrategy {
    Human();
    Human(Player* player);
    Human(const Human& h);
    ~Human();

    // Assignment operator
    void operator= (Human const& h);
    // Stream operator
    friend ostream &operator<<(ostream &os, const Human& h);

    bool issueOrder();
    vector<Territory *>* toAttack();
    vector<Territory *>* toDefend();
};

//class Aggressive : PlayerStrategy {
//    Aggressive();
//    Aggressive(Player* player);
//    Aggressive(const Aggressive& h);
//    ~Aggressive();
//
//    // Assignment operator
//    void operator= (Aggressive const& a);
//    // Stream operator
//    friend ostream &operator<<(ostream &os, const Aggressive &a);
//
//    bool issueOrder();
//    vector<Territory *>* toAttack();
//    vector<Territory *>* toDefend();
//};

//class Benevolent : PlayerStrategy {
//    Benevolent();
//    Benevolent(Player* player);
//    Benevolent(const Benevolent& b);
//    ~Benevolent();
//
//    // Assignment operator
//    void operator= (Benevolent const& b);
//    // Stream operator
//    friend ostream &operator<<(ostream &os, const Benevolent& b);
//
//    bool issueOrder();
//    vector<Territory *>* toAttack() ;
//    vector<Territory *>* toDefend();
//};