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
	model_->setState(Model::IN_PROGRESS);

	if (!model_->getCurrentPlayer()->isHuman()){
		playComputerTurn();
	}
}

void Controller::playTurn(Card* card, bool isDiscard){
	if (!isDiscard){
		model_->playCard(card);
	} else {
		model_->discardCard(card);
	}

	model_->advanceToNextPlayer();

	if (model_->getState() == Model::GAME_ENDED){
		return;
	}

	if (!model_->getCurrentPlayer()->isHuman()){
		playComputerTurn();
	}

}

void Controller::playComputerTurn(){
	if (model_->getCurrentPlayer()->getLegalCards().empty()){
		playTurn(model_->getCurrentPlayer()->getHand()[0], true);
	} else {
		playTurn(model_->getCurrentPlayer()->getLegalCards()[0], false);
	}
}