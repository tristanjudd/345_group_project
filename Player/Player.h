#pragma once
//#include "Map.h"
#include "../Cards.h"
#include <vector>
#include <ostream>
#include "../Map/Map.h"
#include "../Orders.h"

using std::vector;

class Player {

private:

    vector<Territory *> *territories;
    Hand *hand;
    vector<Order *> *orders;

public:

    //Constructors
    Player(); //Default Constructor
    //Player(vector<Territory *> *territories, Hand* hand, vector<Order*>* orders); //Constructor
    Player(const Player &p);//Copy Constructor
    ~Player(); //Destructor
    Player &operator=(const Player &p);//Assignment operator

    friend ostream &operator<<(ostream &os, const Player &player);

    //Player functions
    vector<Territory*> *toAttack();

    vector<Territory*> *toDefend();

    void issueOrder();

    //getters and setters
    Hand *getHand();

    void setHand(Hand *hand);

    vector<Territory *> *getTerritories() const;

    void setTerritories(vector<Territory *> *territories);


    vector<Order *> *getOrders() const;

    void setOrders(vector<Order *> *orders);

};
