#include "Cards.h"
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include <random>
#include <iostream>


// Card class method definitions
Card::Card() {
	int k = rand() % 5;
	cardType = static_cast<CardType>(k);
}

Card::Card(CardType t) {
	cardType = t;
}

Card::Card(Hand* h) {
	hand = h;
	int k = rand() % 5;
	cardType = static_cast<CardType>(k);
}

CardType Card::getType() {
	return cardType;
}

void Card::assignHand(Hand* h) {
	hand = h;
}

void Card::play() {
	if (!this->hand) {
		std::cout << "null pointer" << std::endl;
	}
	else {
		this->hand->remove(this);
	}

	// TODO:
	// create order and add it to the list of orders then return card to deck
}

// Hand class method declarations
Hand::Hand() {
	
}

std::vector<Card *> Hand::getHand() {
	return contents;
}

void Hand::insert(Card* card) {
	contents.push_back(card);
	card->assignHand(this);
}

void Hand::remove(Card* card) {
	// std::vector<Card*>::iterator it = contents.begin();
	int i = 0;
	bool cardFound = false;

	for (i; i < contents.size(); i++) {
		if (card == contents[i]) {
			cardFound = true;
			break;
		}
	}

	std::vector<Card*>::iterator it = contents.begin() + i;

	if (cardFound) {
		contents.erase(it);
	}
	else {
		std::cout << "card not found" << std::endl;
	}


}

// Deck class method delcarations 

// Default constructor creates 100 cards and adds their pointers to the deck
Deck::Deck() {
	count = 0;

	for (int i = 0; i < 100; i++) {
		Card* c = new Card();
		contents.push_back(c);
		count++;
	}
}

// Parameterized constructor for custom deck size
// Takes int n input and returns deck of size n
Deck::Deck(int n) {
	count = 0;

	for (int i = 0; i < n; i++) {
		Card* c = new Card();
		contents.push_back(c);
		count++;
	}
}

// Returns last card pointer in contents and removes it from contents
Card* Deck::draw() {
	Card* card = contents[count - 1];
	contents.pop_back();
	return card;
}

// Pushes a card pointer to contents and shuffles deck
void Deck::insert(Card* card) {
	contents.push_back(card);
	count++;
	shuffle();
}

// Re-arranges pointers in contents vector into random order
void Deck::shuffle() {
	std::srand(std::time(0));
	//std::random_shuffle(contents.begin(), contents.end());
	
}

// Returns number of cards in deck
int Deck::size() {
	return count;
}

// Get nth card in a deck, for dev purposes
Card* Deck::peek(int n) {
	return contents.at(n);
}

// Helper function that cmpares the type of two cards and returns boolean
bool cardTypeSame(Card* c1, Card* c2) {
	if (c1 == c2) return true;
}