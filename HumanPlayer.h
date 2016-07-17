#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include <vector>
#include "Player.h"

// Inherits player
// User controlled player
// actions include discard or play a card
class HumanPlayer: public Player{
public:
	HumanPlayer(int num, Model* model): Player(num, model) {};

	// player controlled actions
	bool playCard(Card*);
	bool discardCard(Card*);

	// indicate player is user controlled
	bool isHuman() {return true;}
};

#endif
