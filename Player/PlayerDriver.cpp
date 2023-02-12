#include "PlayerDriver.h"

int playerDriver(){

    cout << "Making a player" << endl;

    Player *p = new Player();

    cout << endl;

    cout << "Generating Territories to attack" << endl;
    vector<Territory*>* attacking = p->toAttack();

    cout << endl;
    cout << "Generating Territories to defend" << endl;
    vector<Territory*>* defending = p->toDefend();

    cout << "Issuing an order" << endl;
    p->issueOrder();

    cout << endl;

    cout << "Defending Territories:" << endl;

    for (int i = 0; i < defending->size(); i++){

        cout << *defending->at(i) << endl;
    }

    cout << "Attacking Territories:" << endl;

    for (int i = 0; i < attacking->size(); i++){

        cout << *attacking->at(i) << endl;
    }

    cout << "added Order: " << *p->getOrders()->at(0) << endl;

    cout << endl;


    cout << "Player: " << endl << *p << endl;

    cout << endl;

    cout << "Deleting Player" << endl;
    delete p;

    cout << "Deleting Attacking Territories" << endl;
    delete attacking;

    cout << "Deleting Defending Territories" << endl;
    delete defending;

return 0;


}