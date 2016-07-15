#include "Controller.h"
#include "Model.h"

class Card;

Controller::Controller(Model *m) : model_(m) {}

// set seed
void Controller::setSeed(int seed){
	model_->setSeed(seed);
}


// start game
void Controller::startGame(){
	initializeModel();
	startRound();
}


// initialize model for game start
void Controller::initializeModel(){
	model_->initDeck();
	model_->initPlayers();
}


// clean up when game ends
void Controller::endGame(){
	model_->cleanUp();
}


// set up the start of a new round
void Controller::startRound(){
	for (int i = 0; i < 4; i++){
		model_->getPlayer(i)->newRoundReset();
	}
	model_->clearCardsFromTable();
	model_->shuffle();
	model_->deal();

	model_->setCurrentPlayer(model_->getFirstPlayer()->getPlayerNo()-1);
	model_->setState(Model::ROUND_STARTED);
	model_->setState(Model::IN_PROGRESS);
}

void Controller::playTurn(Card* card){
	if (model_->playCard(card)){
		model_->advanceToNextPlayer();
	}

}