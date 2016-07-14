#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include <vector>
#include "Player.h"

class HumanPlayer: public Player{
public:
	HumanPlayer(int num): Player(num) {};

	bool playCard(Card*);
	bool discardCard(Card*);

	bool isHuman() {return true;}
};

#endif
