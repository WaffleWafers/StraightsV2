#ifndef _CONTROLLER_
#define _CONTROLLER_

#include <gtkmm.h>

class Model;
class Card;

// MVC Architecture "Controller"
// Deals with game system functionality
class Controller {
public:
	Controller( Model* );
	void startGame(); // begin game, calls initializeModel and startRound
	void initializeModel();	// initialize players, deck in model
	void startRound(); // shuffle the deck once and then deal the cards to the players
	void endGame(); // clean up model
	void setSeed(int); // 0 default, start game with a seed for randomization 
	void playTurn(Card*, bool); // user plays a card
	void playComputerTurn(); // CPU controlled turn

private:
	Model* model_;
};


#endif