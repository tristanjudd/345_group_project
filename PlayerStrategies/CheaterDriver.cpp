#include "CheaterDriver.h"

int cheaterDriver(){

    //creating observers for testing
    LogObserver* o1 = new LogObserver();

    //creating territories for testing
    Territory* t1 = new Territory(1, 1, "A");
    Territory* t2 = new Territory(2, 1, "B");
    Territory* t3 = new Territory(3, 1, "C");
    Territory* t4 = new Territory(4, 1, "D");
    Territory* t5 = new Territory(5, 1, "E");
    Territory* t6 = new Territory(6, 1, "F");

    //setting borders for territories
    vector<int> borders1 = { 2, 3 };
    vector<int> borders2 = { 1, 4 };
    vector<int> borders3 = { 1, 4, 5 };
    vector<int> borders4 = { 2, 3, 6 };
    vector<int> borders5 = { 3, 6 };
    vector<int> borders6 = { 4, 5 };

    t1->setBorders(&borders1);
    t2->setBorders(&borders2);
    t3->setBorders(&borders3);
    t4->setBorders(&borders4);
    t5->setBorders(&borders5);
    t6->setBorders(&borders6);

    //set bordered territories for territories
    //cout << t1->getBorderedTerritories()->size() << endl;
    t1->getBorderedTerritories()->push_back(t2);
    t1->getBorderedTerritories()->push_back(t3);
    t2->getBorderedTerritories()->push_back(t1);
    t2->getBorderedTerritories()->push_back(t4);
    t3->getBorderedTerritories()->push_back(t1);
    t3->getBorderedTerritories()->push_back(t4);
    t3->getBorderedTerritories()->push_back(t5);
    t4->getBorderedTerritories()->push_back(t2);
    t4->getBorderedTerritories()->push_back(t3);
    t4->getBorderedTerritories()->push_back(t6);
    t5->getBorderedTerritories()->push_back(t3);
    t5->getBorderedTerritories()->push_back(t6);
    t6->getBorderedTerritories()->push_back(t4);
    t6->getBorderedTerritories()->push_back(t5);



    //creating players for testing
    Player* p1 = new Player(1);
    Player* p2 = new Player(2);

    //create an orderList for p1
    OrderList* orderList1 = new OrderList(o1);
    p1->setOrders(orderList1);

    //setting Strategy for players
    p1->setStrategy(new Cheater(p1));
    p2->setStrategy(new Neutral(p2));

    //setting territories for players
    vector<Territory*> territories1 = { t1 };
    vector<Territory*> territories2 = { t2, t3, t4, t5, t6 };

    p1->setPlayerTerritories(&territories1);
    p2->setPlayerTerritories(&territories2);

    //setting owners for territories
    t1->setOwner(p1);
    t2->setOwner(p2);
    t3->setOwner(p2);
    t4->setOwner(p2);
    t5->setOwner(p2);
    t6->setOwner(p2);

    //creating game engine for testing
    GameEngine* gameEngine = new GameEngine(o1);

    //giving 10 troops to every territory
    t1->setArmyCount(new int(10));
    t2->setArmyCount(new int(10));
    t3->setArmyCount(new int(10));
    t4->setArmyCount(new int(10));
    t5->setArmyCount(new int(10));
    t6->setArmyCount(new int(10));

    /* visualization
    Player1: A 1
    Player2: B 2, C 3, D 4, E 5, F 6

    A 1	-	B 2
    |		|
    C 3	-	D 4
    |		|
    E 5	-	F 6
    */

    //p1 cheats
    cout << "\nPlayer 1 cheats" << endl;
    p1->issueOrder(o1);

    //execute Player1 order
    cout << *p1->getOrders()->getList()->at(0) << endl;

    p1->getOrders()->getList()->at(0)->execute();

    //check if he conquered all adjacent territories (B2, C3)
    cout << "Check if Player1 conquered all adjacent territories (B2, C3)" << endl;
    cout << "Owner of B2: " << *t2->getOwner()->getId() << endl;
    cout << "Owner of C3: " << *t3->getOwner()->getId() << endl;

    //check if we cant issue the order twice
    cout << "\nPlayer 1 tries cheats again in the same turn" << endl;
    p1->issueOrder(o1);
    p1->getOrders()->getList()->at(1)->execute();



    return 0;
}
