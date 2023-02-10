#include "Orders.h"
#include <iostream>
using std::cout;
#include <vector>
using std::vector;
#include <string>
using namespace std;

//DRIVER TO TEST

/*
int main() {

	//Creating objects
	Order *ord = new Order("");
	cout << "Order created" << endl;
	Deploy *dep = new Deploy("");
	cout << "Deploy created" << endl;
	Advance *adv =  new Advance("");
	cout << "Advance created" << endl;
	Bomb *bom = new Bomb("");
	cout << "Bomb created" << endl;
	Blockade *blo = new Blockade("");
	cout << "blockade created" << endl;
	Airlift *air = new Airlift("");
	cout << "Airlift created" << endl;
	Negotiate *neg = new Negotiate("");
	cout << "Negotiate created" << endl;

	Order *invalid = new Order("invalid");
	cout << "invalid Order created" << endl;
	
	OrderList L = OrderList();

	//Adding object to the list
	L.Add(ord);
	L.Add(dep);
	L.Add(adv);
	L.Add(bom);
	L.Add(blo);
	L.Add(air);
	L.Add(neg);

	cout << "\nPrinting the list:" << endl;
	L.print();


	L.move(0, 1); //move first order to second
	L.remove(1); //romve second item

	cout << "\nAfter Modification:" << endl;
	L.print();

	//Execution
	cout << "\nExecuting the Orders" << endl;
	for (Order *obj : *L.getList() )
	{
		obj->execute();
		cout << *obj << endl;
	}

	cout << "DONE";
	
	return 0;
}

*/

//void IssueOrder
//{
//	Order* theOrder = new Order();
//	pointerToTheList->Add(obj);
//}
