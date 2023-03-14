#include "CardsDriver.h"
#include "../Player/Player.h"

int cardDriver()
{
	std::srand(time(0));

	// Create deck
	Deck deck = Deck();

	// Create player
	Player p = Player();

	// Get hand 
	Hand* h = p.getHand();

	// Check deck and hand sizes before drawing
	std::cout << "Deck size: " <<  deck.size() << std::endl;
	std::cout << "Hand size: " << h->size() << "\n" << std::endl;

	// Draw cards from deck
	for (int i = 0; i < 7; i++) {
		h->insert(deck.draw());
	}

	// Check deck and hand sizes
	std::cout << "Deck and hand sizes after drawing cards: " << std::endl;
	std::cout << "Deck size: " << deck.size() << std::endl;
	std::cout << "Hand size: " << h->size() << "\n" << std::endl;

	// Show that cards are of different types
	std::cout << "Showing types of cards in hand: " << std::endl;
	std::vector<Card*> handContents = h->getHand();
	for (int i = 0; i < 7; i++) {
		std::cout << handContents[i]->getType() << std::endl;
	}

	// Play all cards
	std::cout << "\n" << "Playing all cards..." << std::endl;
	for (int i = 0; i < 7; i++) {
		handContents[i]->play();
	}

	// Check deck and hand sizes
	std::cout << "\n" << "Hand and deck sizes after playing cards: " << std::endl;
	std::cout << "Deck size: " << deck.size() << std::endl;
	std::cout << "Hand size: " << h->size() << std::endl;


	return 0;
}

