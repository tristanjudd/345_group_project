#include "PlayerDriver.h"


int playerDriver(){

    cout << "Making a player" << endl;

    Player *p = new Player();

    cout << "Generating Territories to attack" << endl;
    vector<Territory*>* attacking = p->toAttack();

    cout << "Generating Territories to defend" << endl;
    vector<Territory*>* defending = p->toDefend();

    cout << "Issuing an order" << endl;
    p->issueOrder();


    cout << "Player: " << p << endl;

    cout << "Defending Territories:" << endl;

    for (int i = 0; i < defending->size(); i++){

        cout << defending->at(i) << endl;

    }

    cout << "Defending Territories:" << endl;

    for (int i = 0; i < attacking->size(); i++){

        cout << attacking->at(i) << endl;

    }

    cout << "added Order: " << p->getOrders()->at(0);


return 0;

    //Territory<Territory
    return 0;
}