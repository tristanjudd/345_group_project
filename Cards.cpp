#include "Card.h"
#include <cstdlib>
#include <chrono>

Card::Card() {
	srand(time(NULL));
	cardType = (CardType)(rand() % 5);
}

Card::Card(CardType t) {
	cardType = t;
}

CardType Card::getType() {
	return cardType;
}

