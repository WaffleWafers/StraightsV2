#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include <vector>
#include "Player.h"

class HumanPlayer: public Player{
public:
	HumanPlayer(int num, Model* model): Player(num, model) {};

	bool playCard(Card*);
	bool discardCard(Card*);

	bool isHuman() {return true;}
};

#endif
