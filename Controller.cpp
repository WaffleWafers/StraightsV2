#include "Controller.h"
#include "Model.h"


Controller::Controller(Model *m) : model_(m) {}

// set seed and start game
void Controller::startGame(int seed){
	initializeModel();
	model_->setSeed(seed);
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
	model_->clearCardsFromTable();
	model_->shuffle();
	model_->deal();

	for (int i = 0; i < 4; i++){
		model_->getPlayer(i)->newRoundReset();
	}

	model_->setCurrentPlayer(model_->getFirstPlayer()->getPlayerNo()-1);
}