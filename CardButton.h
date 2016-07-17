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
	View* view_;
	Controller* controller_;

	void cardPlayed();

	Gtk::Image* image_;
	Card* currentCard_;
	bool isDiscard_;
};

#endif