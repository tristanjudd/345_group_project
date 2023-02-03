#include <iostream>
#include <cstdlib>
#include <chrono>
#include "Card.h"
using namespace std;

int main()
{
	Card c = Card(bomb);

	cout << (c.getType() == bomb) << endl;

}

