#include "OrdersDriver.h"
#include "../Player/Player.h"
#include "../GameEngine/GameEngine.h"


int ordersDriver() {

	cout << "\nORDERS DRIVER:" << endl;

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

	//creating orders for testing
	cout << "\nEXECUTING ORDERS" << endl;

	cout << endl;
	Deploy* d1 = new Deploy(p1, 10, t1, o1); //Player 1 deploys 10 troops to territory 1
	d1->execute();
	cout << *d1 <<  endl;
	cout << *t1->getArmyCount() << endl;

	cout << endl;
	Advance* a1 = new Advance(p1, 3, t1, t3, o1); //Player 1 advances 3 troops from territory 1 to territory 3
	a1->execute();
	cout << *a1 << endl;
	cout << *t1->getArmyCount() << endl;
	cout << *t3->getArmyCount() << endl;

	cout << endl;
	Bomb* b1 = new Bomb(p1, t4, o1); //Player 1 bombs territory 2
	b1->execute();
	cout << *b1 << endl;
	cout << *t4->getArmyCount() << endl;
	
	cout << endl;
	Airlift* al1 = new Airlift(p1, 3, t5, t3, o1); //Player 1 airlifts 3 troops from territory 5 to territory 3
	al1->execute();
	cout << *al1 << endl;
	cout << *t5->getArmyCount() << endl;
	cout << *t3->getArmyCount() << endl;

	cout << endl;
	Blockade* bl1 = new Blockade(p1, t3, o1); //Player 1 blockades territory 3
	bl1->execute();
	cout << *bl1 << endl;
	cout << *t3->getArmyCount() << endl;
	cout << *t3->getOwner()->getId() << endl;

	cout << endl;
	Advance* attack = new Advance(p1, 17, t1, t2, o1); //Player 1 advances 17 troops from territory 1 to territory 2
	attack->execute();
	cout << *attack << endl;
	cout << *t1->getArmyCount() << endl;
	cout << *t2->getArmyCount() << endl;
	cout << *t2->getOwner()->getId() << endl;

    //print player 1 territories ID
    cout << "\nPlayer 1 territories ID: " << endl;
    for (int i = 0; i < p1->getPlayerTerritories()->size(); i++) {
        cout << *p1->getPlayerTerritories()->at(i)->getId() << " ";
    }

    //print player 2 territories ID
    cout << "\nPlayer 2 territories ID: " << endl;
    for (int i = 0; i < p2->getPlayerTerritories()->size(); i++) {
        cout << *p2->getPlayerTerritories()->at(i)->getId() << " ";
    }


	cout << endl;
	Negotiate* n1 = new Negotiate(p1, 2, o1); //Player 1 negotiates with Player 2;
	n1->execute();
	cout << *n1 << endl;

	//creating invalid Orders;
	cout << "\nEXECUTING INVALID ORDERS" << endl;
	cout << endl;
	Deploy* d2 = new Deploy(p2, 10, t1, o1); //Player 2 deploys 10 troops to territory 1 (invalid)
	d2->execute();
	cout << *d2 << endl;

	cout << endl;
	Advance* a2 = new Advance(p2, 3, t6, t5, o1); //Player 2 advances 3 troops from territory 6 to territory 5 (invalid)
	a2->execute();
	cout << *a2 << endl;

	cout << endl;
	Bomb* b2 = new Bomb(p2, t1, o1); //Player 2 bombs territory 1 (invalid)
	b2->execute();
	cout << *b2 << endl;

	cout << endl;
	Negotiate* n2 = new Negotiate(p2, 2, o1); //Player 2 negotiates with Player 2 (invalid)
	n2->execute();
	cout << *n2 << endl;

	cout << "DONE";
	
	return 0;
}




