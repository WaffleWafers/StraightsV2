#include "RoundEndDialog.h"
#include "Model.h"
#include <gtkmm/stock.h>
#include <vector>

using std::string;
using std::vector;

// Specifies the parent window of the dialog box and the title of the dialog box.
RoundEndDialog::RoundEndDialog( Gtk::Window & parentWindow, Model* model, bool gameEnded) : Dialog( "Player Scores", parentWindow, true, true ), model_(model), gameEnded_(gameEnded) {
	
	int bestScore = getWinningScore();

	scoreContainer = this->get_vbox();

	// Set up a group of score labels
	for ( int i = 3 ; i >=0 ; i-- ) {
		int score = model_->getPlayer(i)->getScore();

		if (score == bestScore && gameEnded){
			playerScoreLabel[i] = new Gtk::Label("<b>★Player " + std::to_string(i+1) + "★: " + std::to_string(score) + "</b>");
			playerScoreLabel[i]->set_use_markup(true);
		}
		else if (score == bestScore) {
			playerScoreLabel[i] = new Gtk::Label("<b>Player " + std::to_string(i+1) + ": " + std::to_string(score) + "</b>");
			playerScoreLabel[i]->set_use_markup(true);
		} 
		else{
			playerScoreLabel[i] = new Gtk::Label("Player " + std::to_string(i+1) + ": " + std::to_string(score));
		}

		playerScoreLabel[i]->set_justify(Gtk::JUSTIFY_LEFT);
		scoreContainer->pack_end(*playerScoreLabel[i]);
	} 
	
	string descriptionMessage;

	if (gameEnded){
		descriptionMessage = "Congratulations to the winner(s)!";
	}
	else {
		descriptionMessage = "The current round has ended!";
	}

	Gtk::Label description(descriptionMessage);
	scoreContainer->pack_start(description);


	// Add a standard "ok" button with the appropriate responses when clicked.
	add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
	show_all_children();
	
	// Wait for a response from the dialog box.
	int result = run();
	switch (result) {
		case Gtk::RESPONSE_OK:
			break;
	}     	
}

RoundEndDialog::~RoundEndDialog() {
	for ( int i = 0 ; i < 4 ; i++ )
		delete playerScoreLabel[i];
}

int RoundEndDialog::getWinningScore(){
	int lowest = model_->getPlayer(0)->getScore();

	for (int i = 1 ; i < 4 ; i++){
		if (model_->getPlayer(i)->getScore() < lowest){
			lowest = model_->getPlayer(i)->getScore();
		}
	}

	return lowest;
}