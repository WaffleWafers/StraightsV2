#ifndef _VIEW_
#define _VIEW_

#include <gtkmm.h>
#include "PlayerFrame.h"
#include "DeckGUI.h"
#include "Observer.h"
#include "Controller.h"
#include "Card.h"


class Controller;
class Model;


class View : public Gtk::Window, public Observer {
public:
	View( Controller*, Model* );
	virtual ~View();
	virtual void update();	// Observer Pattern: concrete update() method

private:
	Model* model_;
	Controller* controller_;

	// Card Images
	DeckGUI deck;

	Gtk::VBox mainContainer;

	Gtk::HBox topToolbar;
	Gtk::Button newGameButton;
	Gtk::Entry randomSeedEntry;
	Gtk::Button endGameButton;

	Gtk::Frame tableFrame;
	Gtk::Table table;
	Gtk::Image* cardsOnTable[4][13];

	Gtk::HBox playerListContainer;
	PlayerFrame* playerFrames[4];

	Gtk::Frame currentHandFrame;
	Gtk::HBox handContainer;
	Gtk::Image* cardsInHand[13];

}; // View

#endif
