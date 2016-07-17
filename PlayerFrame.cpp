#include "Model.h"
#include "Controller.h"
#include "PlayerFrame.h"

PlayerFrame::PlayerFrame(int playerNumber, Model* model, View* view, Controller* controller) : playerIndex_(playerNumber - 1), model_(model), view_(view), controller_(controller), rageButton("Rage!"), pointsLabel("0 points"), discardsLabel("0 discards") {
	
	mainContainer.pack_start(rageButton);
	mainContainer.pack_start(pointsLabel);
	mainContainer.pack_start(discardsLabel);

	add(mainContainer);

	set_label("Player " + std::to_string(playerIndex_ + 1));

	rageButton.signal_clicked().connect( sigc::mem_fun( *this, &PlayerFrame::rageButtonClicked ) );

	rageButton.set_sensitive(false);
}

PlayerFrame::~PlayerFrame() {}

void PlayerFrame::update(){
	int score = model_->getPlayer(playerIndex_)->getScore();
	int numDiscards = model_->getPlayer(playerIndex_)->getDiscards().size();

	if (model_->getPlayer(playerIndex_)->isHuman()){
		set_label("Player " + std::to_string(playerIndex_ + 1));
	}
	else{
		set_label("CPU " + std::to_string(playerIndex_ + 1));
	}

	pointsLabel.set_label(std::to_string(score) + " points");
	discardsLabel.set_label(std::to_string(numDiscards) + " discards");

	if (model_->getCurrentPlayer()->getPlayerNo() == playerIndex_ + 1 && model_->getState() != Model::GAME_ENDED){
		rageButton.set_sensitive(true);
	} 
	else {
		rageButton.set_sensitive(false);
	}
}

void PlayerFrame::rageButtonClicked(){
	model_->setHumanToComputer();
	controller_->playComputerTurn();
}