#include "PlayerFrame.h"

PlayerFrame::PlayerFrame(int playerNumber, Model* model, View* view, Controller* controller) : playerNumber(playerNumber-1), model_(model), view_(view), controller_(controller), rageButton("Rage!"), pointsLabel("0 points"), discardsLabel("0 discards") {
	
	mainContainer.pack_start(rageButton);
	mainContainer.pack_start(pointsLabel);
	mainContainer.pack_start(discardsLabel);

	add(mainContainer);

	set_label("Player " + std::to_string(playerNumber));
}

PlayerFrame::~PlayerFrame() {}