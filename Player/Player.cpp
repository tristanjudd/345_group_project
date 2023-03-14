#include "Player.h"
#include <vector>

//Default Constructor
Player::Player() {
    territories = new vector<Territory *>();
    hand = new Hand(this);
    orders = new OrderList();
    id = new int(0);

    // ASSIGNMENT 2
    reinforcements = new int;
    *reinforcements = 0;
}

//Constructor
Player::Player(vector<Territory *> *territories, Hand *hand, OrderList* orders, int *id) {
    Player::id = id;
    Player::territories = territories;
    Player::hand = hand;
    Player::orders = orders;
}

Player::Player(int id){

    Player::id = new int(id);

}

//Copy Constructor
Player::Player(const Player &p) {

    territories = new vector<Territory *>(*p.territories);
    hand = new Hand(*p.hand);
    orders = new OrderList(*p.orders);
    id = new int(*p.id);
}


//Assignment operator
Player &Player::operator=(const Player &p) {
    if (this != &p) {
        territories = new vector<Territory *>(*p.territories);
        hand = new Hand(*p.hand);
        orders = new OrderList(*p.orders);
        id = new int(*p.id);

    }
    return *this;
}

//Stream insertion operator
ostream &operator<<(ostream &os, const Player &player) {

    os << "Player ID: " << *player.id << endl;
    os << "territories: " << endl;
    for (int i = 0; i < player.territories->size(); i++) {
        os << *player.territories->at(i) << endl;
    }

    os << " hand: " << *player.hand << endl;

    os << " orders: " << endl;

    for (int i = 0; i < player.orders->getList()->size(); i++) {
        os << *player.orders->getList()->at(i) << endl;
    }

    return os;
}

//Destructor Implementation
Player::~Player() {

    delete territories;
    delete hand;
    delete orders;
    delete id;
    delete reinforcements;
}

//Function creates an order and
//Adds it to the list of orders
void Player::issueOrder() {

    /*Order *order = new Order("Specific order");
    orders->push_back(order);*/
    //changed Order to abstract class need param to create specific order
    //Order *order = new Order("Specific order");
    //orders->Add(order);
}

//Function creates  list of territories a player will defend
vector<Territory *> *Player::toDefend() {

    vector<Territory *> *territories = new vector<Territory *>();
    Territory *t1 = new Territory(1, 1, "France");
    Territory *t2 = new Territory(2, 2, "England");
    Territory *t3 = new Territory(3, 3, "Spain");
    Territory *t4 = new Territory(4, 4, "Germany");
    Territory *t5 = new Territory(5, 5, "Portugal");

    territories->push_back(t1);
    territories->push_back(t2);
    territories->push_back(t3);
    territories->push_back(t4);
    territories->push_back(t5);

    return territories;

}

//Function creates a list of territories a player will attack
vector<Territory *> *Player::toAttack() {

    vector<Territory *> *territories = new vector<Territory *>();
    Territory *t1 = new Territory(1, 1, "Japan");
    Territory *t2 = new Territory(2, 2, "China");
    Territory *t3 = new Territory(3, 3, "Korea");
    Territory *t4 = new Territory(4, 4, "Vietnam");
    Territory *t5 = new Territory(5, 5, "Singapore");

    territories->push_back(t1);
    territories->push_back(t2);
    territories->push_back(t3);
    territories->push_back(t4);
    territories->push_back(t5);

    return territories;
}

//Getters and Setters
vector<Territory *> *Player::getTerritories() const {
    return territories;
}

void Player::setTerritories(vector<Territory *> *territories) {
    Player::territories = territories;
}

void Player::setHand(Hand *hand) {
    Player::hand = hand;
}

Hand *Player::getHand() {
    return hand;
}

OrderList *Player::getOrders() const {
    return orders;
}

void Player::setOrders(OrderList *orders) {
    Player::orders = orders;
}

int *Player::getId() const {
    return id;
}

void Player::setId(int *id) {
    Player::id = id;
}


// ASSIGNMENT 2
// get the number of troops in Player's reinforcement pool
int Player::getReinforcements() {
    return *reinforcements;
}

// set the number of troops in Player's reinforcement pool
void Player::setReinforcements(int n) {
    *reinforcements = n;
}











