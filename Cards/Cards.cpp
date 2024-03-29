#include "Cards.h"

#include "../Player/Player.h"
#include "../Orders/Orders.h"

// Card class method definitions
Card::Card() {
	int k = rand() % 5;
	cardType = new CardType;
	*cardType = static_cast<CardType>(k);
}

Card::~Card() {
	delete cardType;
}

Card::Card(const Card& c) {
	cardType = new CardType(*c.cardType);
	hand = c.hand;
	deckIssuedFrom = c.deckIssuedFrom;
}

// Card constructor for a specific type (for dev purposes)
Card::Card(CardType t) {
	cardType = new CardType;
	*cardType = t;
}

// Card constructor taking a Hand pointer, the hand to which the card belongs
Card::Card(Hand* h) {
	hand = h;
	int k = rand() % 5;
	cardType = new CardType;
	*cardType = static_cast<CardType>(k);
}

// Card constructor taking a Deck pointer, the deck from which the card was issued
Card::Card(Deck* d) {
	deckIssuedFrom = d;
	int k = rand() % 5;
	cardType = new CardType;
	*cardType = static_cast<CardType>(k);
}

Card& Card::operator=(const Card& c) {
	if (this != &c) {
		cardType = c.cardType;
		hand = c.hand;
	}
	return *this;
}

/* Card constructor taking a Deckand Hand pointer.
Deck is the deck the card was issued from. This is important for returning the card to the 
deck after it has been played. Cards in game are always issued from deck so this is the only 
constructor ever being called in the game */

Card::Card(Deck* d, Hand* h) {
	deckIssuedFrom = d;
	hand = h;
	int k = rand() % 5;
	cardType = new CardType;
	*cardType = static_cast<CardType>(k);
}

Card::Card(Deck* d, CardType t) {
    deckIssuedFrom = d;
    cardType = new CardType;
    *cardType = t;
}

// Stream operator
ostream &operator <<(ostream& os, const Card& c) {
	os << "Card type: " << c.cardType << std::endl;
    return os;
}

// Getter for enum CardType property of card
CardType Card::getType() {
	return *cardType;
}

// Method to assign a card to a hand
void Card::assignHand(Hand* h) {
	hand = h;
}

// Method issues an order to the player who owns the card and card is returned to the deck
CardType Card::play() {
	std::cout << "Playing " << getCardName() << " card\n" << std::endl;

	// Remove this card from hand
    this->hand->remove(this);

	// Insert card back into deck
	// this->deckIssuedFrom->insert(this);

    return *cardType;
	
}

string Card::getCardName() {
    switch(*cardType) {
        case 0:
            return "Bomb";
        case 1:
            return "Reinforcement";
        case 2:
            return "Blockade";
        case 3:
            return "Airlift";
        case 4:
            return "Diplomacy";
    } // end of switch
}

// Hand class method declarations

// Hand default constructor pointing to no player
Hand::Hand() {
    contents = new vector<Card *>;
}

Hand::~Hand() {
	// Return all cards to deck
	for (auto c : *contents) {
		c->deckIssuedFrom->insert(c);
	}

	contents->clear();
}

Hand::Hand(const Hand& h) {
	contents = h.contents;
}

// Hand assignment operator
Hand& Hand::operator=(const Hand& h) {
	if (this != &h) {
		contents = h.contents;
	}
	return *this;
}


// Stream operator
ostream& operator<<(ostream& os, const Hand& h) {
	os << "Cards in hand: " << std::endl;

	for (int i = 0; i < h.contents->size(); i++) {
		os << "Card 1 type: " << h.contents->at(i)->getType() << std::endl;
	}

    return os;
}

// Get contents of hand, returns vector of Card objects
std::vector<Card *> Hand::getHand() {
	return *contents;
}

// Insert a card into a hand
void Hand::insert(Card* card) {
	contents->push_back(card);
	card->assignHand(this);
}

// Remove a card from a hand
void Hand::remove(Card* card) {
    std::vector<Card *>::iterator cardToRemove;

    cardToRemove = std::find(contents->begin(), contents->end(), card);
    if (cardToRemove != contents->end()) {
        contents->erase(cardToRemove);
    }

}

// Get size of hand
int Hand::size() {
	return contents->size();
}

// Deck class method delcarations 

// Default constructor creates 100 cards and adds their pointers to the deck
Deck::Deck() {
    contents = new vector<Card *>;

	for (int i = 0; i < 100; i++) {
		Card* c = new Card(this);
		contents->push_back(c);
	}
}

Deck::~Deck() {
	// Delete all cards in deck
    delete [] contents;

	// Clear vector 
	contents->clear();

    contents = nullptr;
}

// Deck copy constructor
Deck::Deck(const Deck& d) {
	contents = d.contents;
}

// Deck assignment operator
Deck& Deck::operator=(const Deck& d) {
	if (this != &d) {
		contents = d.contents;
	}
	return *this;
}


// Stream operator
ostream& operator<<(ostream& os, const Deck& d) {
	os << "Cards in hand: " << std::endl;

	for (int i = 0; i < d.contents->size(); i++) {
		os << "Card 1 type: " << d.contents->at(i)->getType() << std::endl;
	}
    return os;
}

// Parameterized constructor for custom deck size
// Takes int n input and returns deck of size n
Deck::Deck(int n) {

	for (int i = 0; i < n; i++) {
		Card* c = new Card();
		contents->push_back(c);
	}
}

// Returns last card pointer in contents and removes it from contents
Card* Deck::draw() {
	// Check that deck is not empty
	if (contents->size() == 0) {
		std::cout << "Deck is empty" << std::endl;
	}
	else {
		Card* card = contents->back();
		contents->pop_back();
		return card;
	}
	
}

// Pushes a card pointer to contents and shuffles deck
void Deck::insert(Card* card) {
	contents->push_back(card);
	// shuffleDeck();
}

// Re-arranges pointers in contents vector into random order
void Deck::shuffleDeck() {
	std::shuffle(contents->begin(), contents->end(), std::default_random_engine(time(0)));
}

// Returns number of cards in deck
int Deck::size() {
	return contents->size();
}

// Get nth card in a deck (for dev purposes)
Card* Deck::peek(int n) {
	return contents->at(n);
}