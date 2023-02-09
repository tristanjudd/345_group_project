#include "Orders.h"
#include <iostream>
using std::cout;
#include <vector>
using std::vector;
#include <string>
using namespace std;

//DRIVER TO TEST
int main() {
	Order ord = Order("");
	cout << "Order created" << endl;
	deploy dep = deploy("");
	cout << "deploy created" << endl;
	Advance adv = Advance("");
	cout << "advance created" << endl;
	bomb bom = bomb("");
	cout << "bomb created" << endl;
	blockade blo = blockade("");
	cout << "blockade created" << endl;
	airlift air = airlift("");
	cout << "airlift created" << endl;
	negotiate neg = negotiate("");
	cout << "negotiate created" << endl;
	
	OrderList L = OrderList();
	
	L.Add(ord);
	L.Add(dep);
	L.Add(adv);
	L.Add(bom);
	L.Add(blo);
	L.Add(air);
	L.Add(neg);

	L.print();

	//L.theList->erase(L.theList->begin());
	//L.remove(0);
	//cout<<"index 0:"<<L.theList->at(0);

	//L.move(0, 1);
	//L.print();
	//L.remove(0);
	//L.print();
	cout << "DONE";


	/*
	cout << "\n\n PRINTING OBJECTS:" << endl;
	cout << ord << endl;
	ord.execute();
	cout << ord << endl;

	cout << dep << endl;
	dep.execute();
	cout << dep << endl;

	
	cout << adv << endl;
	adv.execute();
	cout << adv << endl;
	
	cout << bom << endl;
	bom.execute();
	cout << bom << endl;

	cout << blo << endl;
	blo.execute();
	cout << blo << endl;

	cout << air << endl;
	air.execute();
	cout << air << endl;

	cout << neg << endl;
	neg.execute();
	cout << neg << endl;
	*/
	
	
	return 0;
}

