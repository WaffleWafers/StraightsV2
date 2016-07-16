#include "Model.h"
#include "PlayerFrame.h"

PlayerFrame::PlayerFrame(int playerNumber, Model* model, View* view, Controller* controller) : playerIndex_(playerNumber - 1), model_(model), view_(view), controller_(controller), rageButton("Rage!"), pointsLabel("0 points"), discardsLabel("0 discards") {
	
	mainContainer.pack_start(rageButton);
	mainContainer.pack_start(pointsLabel);
	mainContainer.pack_start(discardsLabel);

	add(mainContainer);

	set_label("Player " + std::to_string(playerIndex_ + 1));
}

PlayerFrame::~PlayerFrame() {}

void PlayerFrame::update(){
	int score = model_->getPlayer(playerIndex_)->getScore();
	int numDiscards = model_->getPlayer(playerIndex_)->getDiscards().size();

	pointsLabel.set_label(std::to_string(score) + " points");
	discardsLabel.set_label(std::to_string(numDiscards) + " discards");
}