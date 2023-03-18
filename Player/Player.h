//class Hand;
#pragma once
//#include "Map.h"
#include <vector>
#include <ostream>

#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"

using std::vector;

class Territory;
class Hand;
class OrderList;

class Player {

private:
    string *name;
    vector<Territory *> *territories;
    Hand *hand;
    OrderList *orders;
    int *id;

    // ASSIGNMENT 2
    int *reinforcements;

public:

    //Constructors
    Player(); //Default Constructor
    Player(string name, int playerId); //Constructor
    Player(vector<Territory *> *territories, Hand *hand, OrderList *orders, int *id); //Constructor
    Player(int id);
    Player(const Player &p);//Copy Constructor
    ~Player(); //Destructor
    Player &operator=(const Player &p);//Assignment operator

    friend ostream &operator<<(ostream &os, const Player &player);

    //Player functions

    // changed return type to int because had to use territory ids for comparison
    vector<Territory *> *toAttack();

    vector<Territory *> *toDefend();

    bool issueOrder();

    //getters and setters
    string *getName() const;

    void setName(string *name);

    Hand *getHand();

    void setHand(Hand *hand);

    vector<Territory *> *getPlayerTerritories() const;

    void setPlayerTerritories(vector<Territory *> *territories);


    OrderList *getOrders() const;

    void setOrders(OrderList *orders);

    int *getId() const;

    void setId(int *id);

    // ASSIGNMENT 2
    int getReinforcements();

    void setReinforcements(int n);
};

int string_is_num_in_range(string str, int n, int m);

void invalidInput();