#pragma once
#include <string>

enum CardType
{
	bomb,
	reinforcement,
	blockade,
	airlift,
	diplomacy
};

class Card {
private:
	CardType cardType;
public:
	Card();
	Card(CardType t);
	void play();
	CardType getType();
};