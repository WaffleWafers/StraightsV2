#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Player.h"
#include "Model.h"

Player::Player(int playerNo, Model* model): playerNo_(playerNo), model_(model), score_(0), oldScore_(0), roundScore_(0) {}

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
		this->setModel(p.getModel());
	}

	return *this;
}

// add a card to the hand
void Player::addCard(Card* card){
	hand_.push_back(card);
}


std::vector<Card*> Player::getLegalCards(){

	std::vector<Card*> legalCards = std::vector<Card*>();


	for (unsigned int i = 0; i < hand_.size(); i++){
		int cardRank = (hand_[i])->getRank(); 
		int cardSuit = (hand_[i])->getSuit(); 

		if (cardRank == (7-1)){ // all 7's of any suit are legal

			if (cardSuit == 3){ // 7 of spades
				legalCards.clear();
				legalCards.push_back(hand_[i]); // 7 of spades is the only option
				return legalCards;
			}
			else{
				legalCards.push_back(hand_[i]);
			}
		}
		// we refer to the global 2D array that keeps track of cards played
		else if ((cardRank > 0 && model_->hasBeenPlayed(static_cast<Suit>(cardSuit), static_cast<Rank>(cardRank - 1)))
			|| (cardRank < 12 && model_->hasBeenPlayed(static_cast<Suit>(cardSuit), static_cast<Rank>(cardRank + 1)))){
				legalCards.push_back(hand_[i]);
		}	
	}

	return legalCards;

}


// reset all temporary scores when a new round begins
void Player::newRoundReset(){
	setOldScore(getScore());
	resetRoundScore();
	discards_.clear();
}
