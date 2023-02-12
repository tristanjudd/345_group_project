#pragma once
#include <string>
#include <vector>
// #include "Player.h"

// Enum of the different card types
enum CardType
{
	bomb,
	reinforcement,
	blockade,
	airlift,
	diplomacy
};

class Hand;

// Card class header
// Card is an object containing details about a specific instance of a Warzone card
class Card {
private:
	CardType cardType;
	Hand* hand;
public:
	Card();
	Card(CardType t);
	Card(Hand* h);
	void assignHand(Hand* hand);
	void play();
	CardType getType();
};

// Hand class header
// A Hand object is a collection of Card objects
class Hand {
private:
	/*Player* owner;*/
	std::vector<Card *> contents;

public:
	Hand(); // Default constructor with no cards
	std::vector<Card *> getHand(); // Returns the player's hand as a vector of Card objects
	void insert(Card* card); // Inserts a card into the contents vector
	void remove(Card* card); // Used when a card is played, removes card from hand

};

// Deck class header
// A deck is a collection of Card objects
class Deck {
private:
	int count;
	std::vector<Card *> contents;
public:
	Deck();
	Deck(int n);
	Card* draw();
	void insert(Card* card);
	void shuffle();
	int size();
	Card* peek(int n);
};

bool cardTypeSame(Card* c1, Card* c2);