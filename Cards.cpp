#include "Cards.h"
#include <cstdlib>
#include <chrono>

// Card class method definitions
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

void Card::play() {
	// TODO:
	// create order and add it to the list of orders then return card to deck
}

// Hand class method declarations
Hand::Hand() {
	
}

std::vector<Card> Hand::getHand() {
	return contents;
}

void Hand::insert(Card card) {
	contents.push_back(card);
}

void Hand::remove(Card card) {
	int index = -1;

	for (Card c : contents) {
		if
	}
}

// Deck class method delcarations 
Deck::Deck() {

}

Card Deck::draw() {
	// TODO
}

void Deck::insert(Card card) {
	// TODO
}
