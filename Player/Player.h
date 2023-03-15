//class Hand;
#pragma once
//#include "Map.h"
#include <vector>
#include <ostream>

#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"

using std::vector;


class Player {

private:

    vector<Territory *> *territories;
    Hand *hand;
    OrderList* orders;
    int * id;

    // ASSIGNMENT 2
    int* reinforcements;

public:

    //Constructors
    Player(); //Default Constructor
    Player(vector<Territory *> *territories, Hand* hand, OrderList* orders, int *id); //Constructor
    Player(int id);
    Player(const Player &p);//Copy Constructor
    ~Player(); //Destructor
    Player &operator=(const Player &p);//Assignment operator

    friend ostream &operator<<(ostream &os, const Player &player);

    //Player functions

    // changed return type to int because had to use territory ids for comparison
    vector<Territory *> *toAttack();

    vector<Territory*> *toDefend();

    Order* issueOrder();

    //getters and setters
    Hand *getHand();

    void setHand(Hand *hand);

    vector<Territory *> *getTerritories() const;

    void setTerritories(vector<Territory *> *territories);


    OrderList *getOrders() const;

    void setOrders(OrderList* orders);

    int *getId() const;

    void setId(int *id);

    // ASSIGNMENT 2
    int getReinforcements();
    void setReinforcements(int n);
};
