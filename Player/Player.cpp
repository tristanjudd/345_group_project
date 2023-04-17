#include "Player.h"
#include <vector>
#include <set>
#include <algorithm>
using std::all_of;

//Default Constructor
Player::Player(LogObserver* observer) {
    territories = new vector<Territory *>();
    hand = new Hand();
    orders = new OrderList(observer);
    id = new int(0);

    // ASSIGNMENT 2
    reinforcements = new int;
    *reinforcements = 0;
}

Player::Player(string playerName, int playerId, LogObserver* observer) {
    name = new string(playerName);
    territories = new vector<Territory *>();
    hand = new Hand();
    orders = new OrderList(observer);
    id = new int(playerId);
    reinforcements = new int;
}

//Constructor
Player::Player(vector<Territory *> *territories, Hand *hand, OrderList *orders, int *id) {
    Player::id = id;
    Player::territories = territories;
    Player::hand = hand;
    Player::orders = orders;
    Player::reinforcements = new int(0);
}

Player::Player(int id) {

    Player::id = new int(id);
    Player::territories = new vector<Territory *>();
    Player::hand = new Hand();
    Player::reinforcements = new int(0);

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
    delete name;
    delete territories;
    delete hand;
    delete orders;
    delete id;
    delete reinforcements;
}

//Function creates an order and
//Adds it to the list of orders
bool Player::issueOrder(LogObserver* observer) {
    // use strategy's issueOrder method
    bool play = strategy->issueOrder(observer);
    // return its output
    return play;

}


//Function creates  list of territories a player will defend
// the
vector<Territory *> *Player::toDefend() {
    // use strategy
    return strategy->toDefend();

}

//Function creates a list of territories a player will attack
vector<Territory *> *Player::toAttack() {
    // use strategy
    return strategy->toAttack();

}

//Getters and Setters
string *Player::getName() const {
    return name;
}

void Player::setName(string *name) {
    Player::name = name;
}

vector<Territory *> *Player::getPlayerTerritories() const {
    return territories;
}

void Player::setPlayerTerritories(vector<Territory *> *territories) {
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

// function for checking whether input is a number within a certain range
int string_is_num_in_range(string str, int n, int m) {
    // check that string is not empty and all chars are digits
    if (!str.empty() && std::all_of(str.begin(), str.end(), ::isdigit)) {
        // convert string to int and return
        int num = std::stoi(str);
        // if num in range return num
        if (num >= n && num <= m) return num;
            // else return false
        else return 0;

    } else {
        // return false
        return 0;
    }
}

void invalidInput() {
    cout << "Invalid input, try again" << endl;
    //clear input stream
    cin.clear();
    cin.ignore();
}

// ASSIGNMENT 3
Player::Player(LogObserver *observer, PlayerStrategy *s) {
    territories = new vector<Territory *>();
    hand = new Hand();
    orders = new OrderList(observer);
    id = new int(0);
    reinforcements = new int;
    *reinforcements = 0;
    strategy = s;
    s->setPlayer(this);
}

void Player::setStrategy(PlayerStrategy *newStrategy) {
    strategy = newStrategy;
}

PlayerStrategy* Player::getStrategy() {
    return strategy;
}



