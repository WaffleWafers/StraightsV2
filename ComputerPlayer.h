#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include <vector>
#include "Player.h"
#include "Card.h"

class ComputerPlayer: public Player{
public:
	ComputerPlayer(int num) : Player(num) {};
	ComputerPlayer(const Player& p): Player(p){};

	bool playCard(Card*);
	bool discardCard(Card*);

	Card* getCardToPlay();
	Card* getCardToDiscard();

	bool isHuman() {return false;}
};

#endif
