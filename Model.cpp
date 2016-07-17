#include <random>
#include <iostream>
#include <sstream>
#include "Model.h"

//initialize with 0 seed
Model::Model(): seed_(0){}

// initialize model with given seed
Model::Model(int seed): seed_(seed){}

// destructor
Model::~Model(){
	deleteCardsAndPlayers();
}

// manually set the current player given player number
void Model::setCurrentPlayer(int playerNumber){
	currentPlayer_ = playerNumber;
}

Player* Model::getFirstPlayer() const{
	return players_[firstPlayer_];
}

Player* Model::getCurrentPlayer() const{
	return players_[currentPlayer_];
}

Player* Model::getPlayer(int index) const{
	return players_[index];
}

std::vector<Card*> Model::getDeck() const{
	return deck_;
}

std::string Model::getLogMessage() const{
	return logMessage_;
}

void Model::setPlayerType(int playerIndex, char type){
	playerTypes_[playerIndex] = type;
}

// initialize every card of a 52 card deck
void Model::initDeck(){
	for (int suit = 0 ; suit < Suit::SUIT_COUNT ; suit++){
		for (int rank = 0 ; rank < Rank::RANK_COUNT ; rank++){
			Card* newCard = new Card(static_cast<Suit>(suit), static_cast<Rank>(rank));
			deck_.push_back(newCard);
		}
	}
}

// initialize player type as human or computer
void Model::initPlayers(){
	for (int i = 0 ; i < 4 ; i++){
		if (playerTypes_[i] == 'h'){
			HumanPlayer* hPlayer = (new HumanPlayer(i+1, this));
			players_.push_back((Player*) hPlayer);
		} else {
			ComputerPlayer* cPlayer = (new ComputerPlayer(i+1, this));
			players_.push_back((Player*) cPlayer);
		}
	}
}


int Model::getSeed() const{
	return seed_;
}


void Model::setSeed(int seed){
	seed_ = seed;
}

// shuffle using given randomize algorithm
void Model::shuffle(){

	static std::mt19937 rng(seed_);

	int n = deck_.size();

	while ( n > 1 ) {
		int k = (int) (rng() % n);
		--n;
		Card *c = deck_[n];
		deck_[n] = deck_[k];
		deck_[k] = c;
	}
}

// assign 13 cards to each of the 4 players
void Model::deal(){
	for (int i = 0; i < 52; i++){
		players_[i/13]->addCard(deck_.at(i));

		if ((deck_[i])->getSuit() == Suit::SPADE && (deck_[i])->getRank() == Rank::SEVEN){
			firstPlayer_ = i/13;
		}
	}
}

// play card for curr. player
bool Model::playCard(Card* card){
	currentCardsOut_[card->getSuit()][card->getRank()] = true;
	return players_[currentPlayer_]->playCard(card);
}

// discard card for curr. player
bool Model::discardCard(Card* card){
	return players_[currentPlayer_]->discardCard(card);
}

// new player turn
void Model::advanceToNextPlayer(){
	currentPlayer_ = (currentPlayer_ + 1) % 4;

	if (getCurrentPlayer()->getHand().size() == 0){

		if (playerReachedPointLimit()){
			setLogMessage("\nGame over. A winner(s) has been crowned!");
			setState(GAME_ENDED);
			cleanUp();
			return;
		}

		setLogMessage("\nRound ended!");

		clearCardsFromTable();
		shuffle();
		deal();

		for (int i = 0; i < 4; i++){
			getPlayer(i)->newRoundReset();
		}

		setCurrentPlayer(getFirstPlayer()->getPlayerNo()-1);
		setState(ROUND_ENDED);
		return;
	}

	setState(IN_PROGRESS);
}

// when player ragequits, replace with computer player
void Model::setHumanToComputer(){
	Player* player = players_[currentPlayer_];
	ComputerPlayer* computerPlayer = new ComputerPlayer(*player);
	delete player;
	players_[currentPlayer_] = (Player*) computerPlayer;
}

// when game ends, delete all players and cards
void Model::deleteCardsAndPlayers(){
	for (std::vector<Card*>::iterator it = deck_.begin() ; it != deck_.end() ; it++){
		delete *it;
	}

	for (std::vector<Player*>::iterator it = players_.begin() ; it != players_.end() ; it++){
		delete *it;
	}

	deck_.clear();
	players_.clear();
}

// reset played cards array for new round
void Model::clearCardsFromTable(){
	for (int suit = 0 ; suit < Suit::SUIT_COUNT ; suit++){
		for (int rank = 0 ; rank < Rank::RANK_COUNT ; rank++){
			currentCardsOut_[suit][rank] = false;
		}
	}
}

// delete everything 
void Model::cleanUp(){
	clearCardsFromTable();
	deleteCardsAndPlayers();
}

// retrieve card pointer from deck
Card* Model::getCard(Card card){
	Card* c = nullptr;

	for (unsigned int i = 0 ; i < deck_.size() ; i++){
		if (*deck_[i] == card){
			c = deck_[i];
		}
	}

	return c;
}


Model::State Model::getState() const{
	return state_;
}


void Model::setState(State state) {
	state_ = state;
	notify();
}

// checks if a card has been played
bool Model::hasBeenPlayed(Suit s, Rank r) const{
	return currentCardsOut_[s][r];
}

bool Model::playerReachedPointLimit() const{
	for (int i = 0 ; i < 4 ; i++){
		if (getPlayer(i)->getScore() >= 80){
			return true;
		}
	}
	return false;
}

// sets a log message on which card has been played/discarded
void Model::setLogMessage(Card* card, bool isDiscard){
	logMessage_ = "\n";

	if (getCurrentPlayer()->isHuman()){
		logMessage_ += "Player " + std::to_string(currentPlayer_ + 1) + " ";
	} else {
		logMessage_ += "CPU " + std::to_string(currentPlayer_ + 1) + " ";
	}

	std::stringstream ss;
    ss << *card;
	std::string cardPlayed = ss.str();

	if (isDiscard){
		logMessage_ += "discards " + cardPlayed + ".";
	} else {
		logMessage_ += "plays " + cardPlayed + ".";
	}

}

void Model::setLogMessage(std::string message){
	logMessage_ = message;
}
