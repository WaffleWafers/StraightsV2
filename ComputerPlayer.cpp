#include <vector>
#include <algorithm>

#include "ComputerPlayer.h"

// play a card from the hand
bool ComputerPlayer::playCard(Card* card){
	// remove from hand
	int pos = find(hand_.begin(), hand_.end(), card) - hand_.begin();

	hand_.erase(hand_.begin() + pos);

	return true;
}

// discard a card from the hand and add to the discard vector
bool ComputerPlayer::discardCard(Card* card){

	// remove from hand the first card
	discards_.push_back(card);
	setRoundScore(getRoundScore() + card->getRank() + 1);
	setScore(getScore() + card->getRank() + 1);

	hand_.erase(hand_.begin());

	return true;
}
