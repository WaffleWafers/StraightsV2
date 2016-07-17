#ifndef _CARDBUTTON_
#define _CARDBUTTON_

#include <gtkmm/button.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>

#include <string>
#include "Card.h"

class View;
class Controller;

class CardButton : public Gtk::Button {
public:
	CardButton(View*, Controller*);
	virtual ~CardButton();
	void setCard(Card*, bool enableButton, bool discard);

private:
	// MVC architecture
	View* view_;
	Controller* controller_;

	void cardPlayed(); // plays card when pressed

	Gtk::Image* image_;
	Card* currentCard_; // current card information of button
	bool isDiscard_; // if card was discarded
};

#endif