#pragma once
#include <array>
#include "Card.h"

class Deck {
	Card contents[];
	Card draw();
};