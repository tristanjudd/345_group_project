#pragma once
#include <string>
#include <vector>


// Enum of the different card types
enum CardType
{
	bomb,
	reinforcement,
	blockade,
	airlift,
	diplomacy
};

// Card class header
// Card is an object containing details about a specific instance of a Warzone card
class Card {
private:
	CardType cardType;
public:
	Card();
	Card(CardType t);
	void play();
	CardType getType();
};

// Hand class header
// A Hand object is a collection of Card objects
class Hand {
private:
	std::vector<Card> contents;

public:
	Hand(); // Default constructor with no cards
	std::vector<Card> getHand(); // Returns the player's hand as a vector of Card objects
	void insert(Card card); // Inserts a card into the contents vector
	void remove(Card card); // Used when a card is played, removes card from hand

};

// Deck class header
// A deck is a collection of Card objects
class Deck {
private:
	std::vector<Card> contents;
public:
	Deck();
	Card draw();
	void insert(Card card);
};