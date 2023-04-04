#include "NeutralDriver.h"

int neutralDriver(){
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

    //creating players for testing
    Player* p1 = new Player(1);
    Player* p2 = new Player(2);

    //setting neutral Strategy for players
    p1->setStrategy(new Neutral(p1));
    p2->setStrategy(new Neutral(p2));

    //setting territories for players
    vector<Territory*> territories1 = { t1, t3, t5 };
    vector<Territory*> territories2 = { t2, t4, t6 };

    p1->setPlayerTerritories(&territories1);
    p2->setPlayerTerritories(&territories2);

    //setting owners for territories
    t1->setOwner(p1);
    t2->setOwner(p2);
    t3->setOwner(p1);
    t4->setOwner(p2);
    t5->setOwner(p1);
    t6->setOwner(p2);

    //creating observers for testing
    LogObserver* o1 = new LogObserver();

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
    Player1	Player2
    A 1	-	B 2
    |		|
    C 3	-	D 4
    |		|
    E 5	-	F 6
    */

    //Call p1 issueOrder
    cout << "\nTest p1 issueOrder (does nothing)" << endl;
    p1->issueOrder(o1); //does nothing

    //P2 advances from B to A
    cout << "\nTest p2 advance from B to A" << endl;
    Advance* a1 = new Advance(p2,2, t2, t1, o1); //Player 2 advances 3 troops from territory 1 to territory 3
    a1->execute();

    cout << *a1 << endl;

    //Check if p1 is still neutral
    cout << "\nCheck if p1 changed to Agressive" << endl;
    Aggressive* Check = dynamic_cast<Aggressive*>(p1->getStrategy());

    if (Check != nullptr) {
        cout << "DEBUG: Neutral player strategy changed to aggressive" << endl;
    }

    return 0;
}
