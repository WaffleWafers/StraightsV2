#ifndef _CARDBUTTON_
#define _CARDBUTTON_

#include <gtkmm/button.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>

#include <string>
#include "Card.h"

class Model;
class View;
class Controller;

class CardButton : public Gtk::Button {
public:
	CardButton(Model*, View*, Controller*);
	virtual ~CardButton();
	void setCard(Card*, bool enableButton, bool discard);

private:
	Model* model_;
	View* view_;
	Controller* controller_;

	void cardPlayed();

	Gtk::Image* image_;
	Card* currentCard_;
	bool isDiscard_;
};

#endif