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
    vector<Territory*> borderedTerritories1 = { t2, t3 };
    vector<Territory*> borderedTerritories2 = { t1, t4 };
    vector<Territory*> borderedTerritories3 = { t1, t4, t5 };
    vector<Territory*> borderedTerritories4 = { t2, t3, t6 };
    vector<Territory*> borderedTerritories5 = { t3, t6 };
    vector<Territory*> borderedTerritories6 = { t4, t5 };

//    t1->setBorderedTerritories(t1, &borderedTerritories1);
//    t2->setBorderedTerritories(t2, &borderedTerritories2);
//    t3->setBorderedTerritories(t3, &borderedTerritories3);
//    t4->setBorderedTerritories(t4, &borderedTerritories4);
//    t5->setBorderedTerritories(t5, &borderedTerritories5);
//    t6->setBorderedTerritories(t6, &borderedTerritories6);

    //creating players for testing
    Player* p1 = new Player(1);
    Player* p2 = new Player(2);

    //create an orderList for p1
    OrderList* orderList1 = new OrderList(o1);
    p1->setOrders(orderList1);

    //setting neutral Strategy for players
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
    cout << "Player 1 cheats" << endl;
    p1->issueOrder(o1);

    //execute Player1 order
    //p1->getOrders()->getList()->at(0)->execute();

    //check if he conquered all adjacent territories (B2, C3)
    cout << "Owner of B2: " << *t2->getOwner()->getId() << endl;
    cout << "Owner of C3: " << *t3->getOwner()->getId() << endl;

    //check if we cant issue the order twice
    cout << "Player 1 cheats again" << endl;
    p1->issueOrder(o1);
    //p1->getOrders()->getList()->at(1)->execute();



    return 0;
}
