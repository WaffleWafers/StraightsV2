#ifndef _CONTROLLER_
#define _CONTROLLER_

#include <gtkmm.h>

class Model;
class Card;

class Controller {
public:
	Controller( Model* );
	void startGame();
	void initializeModel();	// initialize players, deck in model
	void startRound(); // shuffle the deck once and then deal the cards to the players
	void endGame();
	void setSeed(int);
	void playTurn(Card*, bool);

private:
	Model* model_;
};


#endif