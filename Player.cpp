#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Player.h"

Player::Player(int playerNo): score_(0), oldScore_(0), roundScore_(0), playerNo_(playerNo) {}

// destructor
Player::~Player(){
	hand_.clear();
	discards_.clear();
}

// copy constructor
Player::Player(const Player& p){
	*this = p;
}

Player& Player::operator= ( const Player& p){
	// don't really need to deep copy, since only pointers are cards

	// check for self-assignment
	if (this != &p){
		this->setHand(p.getHand());
		this->setDiscards(p.getDiscards());
		this->setScore(p.getScore());
		this->setOldScore(p.getOldScore());
		this->setRoundScore(p.getRoundScore());
		this->setPlayerNo(p.getPlayerNo());
	}

	return *this;
}


// add a card to the hand
void Player::addCard(Card* card){
	hand_.push_back(card);
}


// reset all temporary scores when a new round begins
void Player::newRoundReset(){
	setOldScore(getScore());
	resetRoundScore();
	discards_.clear();
}
