#pragma once
//#include "Map.h"
#include "../Hand.h";
#include <vector>;

using namespace std;
class Player {

private:

	//Territory territories[];
	Hand *hand;
	//vector<Order> orders;

public:

	Player();
	//Player(Territory* territories, Hand hand);
	//Territory* toAttack();
	//Territory* toDefend();

	void issueOrder();

	void setHand(Hand);
		Hand getHand();

	//Territory getTerritory();
};
