#pragma once
#include <string>
#include <vector>
#include <ostream>
//#include "../Player/Player.h"
#include "../Orders/Orders.h"

// class Player; // foreward declaration to avoid circular dependency


// Enum of the different card types
enum CardType
{
	bomb,
	reinforcement,
	blockade,
	airlift,
	diplomacy
};

class Hand; // Foreward declaration
class Deck; // Foreward declaration

// Card class header
// Card is an object containing details about a specific instance of a Warzone card
class Card {
private:
	CardType* cardType;
	
public:
	Deck* deckIssuedFrom;
	Hand* hand;
	Card();
	~Card(); // destructor
	Card(const Card& c); //copy constructor
	Card(CardType t);
	Card(Hand* h);
	Card(Deck* d);
	Card(Deck* d, Hand* h);
    Card(Deck* d, CardType t);
	Card &operator=(const Card& c); // Assignment operator
	friend std::ostream& operator<<(std::ostream& os, const Card& c);
	void assignHand(Hand* hand);
	CardType play();
	CardType getType();
    string getCardName();
};

// Hand class header
// A Hand object is a collection of Card objects
class Hand {
private:
	
	std::vector<Card *>* contents;

public:
	Hand(); // Default constructor with no cards
	~Hand();
	Hand(const Hand& h); // copy constructor
	Hand(Player* p);
	Hand& operator=(const Hand& c); // Assignment operator
	friend std::ostream& operator<<(std::ostream& os, const Hand& c); // Stream operator
	std::vector<Card *> getHand(); // Returns the player's hand as a vector of Card objects
	void insert(Card* card); // Inserts a card into the contents vector
	void remove(Card* card); // Used when a card is played, removes card from hand
	int size();

};

// Deck class header
// A deck is a collection of Card objects
class Deck {
private:
	std::vector<Card *>* contents;
public:
	Deck();
	~Deck();
	Deck(const Deck& d); // copy constructor
	Deck(int n);
	Deck& operator=(const Deck& c); // Assignment operator
	friend std::ostream& operator<<(std::ostream& os, const Deck& c); // Stream operator
	Card* draw();
	void insert(Card* card);
	void shuffleDeck();
	int size();
	Card* peek(int n);
};

