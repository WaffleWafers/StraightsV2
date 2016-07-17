#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include <vector>
#include "Player.h"
#include "Card.h"

// CPU controlled player for ragequits/pre-set CPU
class ComputerPlayer: public Player{
public:
	ComputerPlayer(int num, Model* model) : Player(num, model) {};
	ComputerPlayer(const Player& p): Player(p){};

	// player actions for computer
	bool playCard(Card*);
	bool discardCard(Card*);

	bool isHuman() {return false;} // indicate is computer player
};

#endif
