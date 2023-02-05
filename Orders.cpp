#include "Orders.h"
#include <iostream>
using namespace std;
#include <string>


Order::Order() {
	effect = new string("");
}

Order::Order(string execMessage) {
	effect = new string(execMessage);
}

Order::~Order() {
	delete effect;
}