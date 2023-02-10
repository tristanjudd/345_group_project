#include "Orders.h"
#include <iostream>
using std::cout;
#include <vector>
using std::vector;
#include <string>
using namespace std;

//DRIVER TO TEST
int main() {
	//add new
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

	Order invalid = Order("invalid");
	cout << "invalid Order created" << endl;
	
	OrderList L = OrderList();

	negotiate* n = new negotiate("");

	//remove &
	L.Add(&ord);
	L.Add(&dep);
	L.Add(&adv);
	L.Add(&bom);
	L.Add(&blo);
	L.Add(&air);
	L.Add(&neg);

	L.print();

	L.move(0, 1);
	//L.remove(1);

	cout << "After Modification:" << endl;
	L.print();
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

	cout << invalid << endl;
	invalid.execute();
	cout << invalid << endl;
	*/
	
	
	return 0;
}


//void IssueOrder{
//	Order* theOrder = new Order();
//	pointerToTheList->Add(obj);
//	
//}
