#include "Orders.h"
#include <iostream>
using namespace std;
#include <string>

//DRIVER TO TEST
int main() {
	Order ord = Order("invalid");
	cout << "Order created" << endl;
	deploy dep = deploy("invalid");
	cout << "deploy created" << endl;
	Advance adv = Advance("invalid");
	cout << "advance created" << endl;
	bomb bom = bomb("invalid");
	cout << "bomb created" << endl;
	blockade blo = blockade("invalid");
	cout << "blockade created" << endl;
	airlift air = airlift("invalid");
	cout << "airlift created" << endl;
	negotiate neg = negotiate("invalid");
	cout << "negotiate created" << endl;

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
	
	

	
	//cout << dep.getDesc() << endl;
	//cout << dep.getEffect() << endl;
	//obj.execute();
	//cout << obj;
	return 0;
}

