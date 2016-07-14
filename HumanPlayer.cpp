#include <vector>
#include <algorithm>
#include <iostream>
#include "HumanPlayer.h"

// play a card from the hand
bool HumanPlayer::playCard(Card* card){

	// get position of the discard card in the hand
	int pos = std::find(hand_.begin(), hand_.end(), card) - hand_.begin();

	// remove from hand
	hand_.erase(hand_.begin() + pos);

	return true;
}

// discard a card from the hand and add to the discard vector
bool HumanPlayer::discardCard(Card* discardCard){

	// get position of the discard card in the hand
	int pos = std::find(hand_.begin(), hand_.end(), discardCard) - hand_.begin();

	// remove from hand
	hand_.erase(hand_.begin() + pos);
	discards_.push_back(discardCard);
	setRoundScore(getRoundScore() + discardCard->getRank() + 1);
	setScore(getScore() + discardCard->getRank() + 1);

	return true;
}
