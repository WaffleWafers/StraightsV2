#include "CardButton.h"
#include "View.h"
#include "Controller.h"

// constructor for a card to act as a button in GUI
CardButton::CardButton(View* view, Controller* controller): view_(view), controller_(controller), isDiscard_(false) {

	image_ = new Gtk::Image(view_->getNullCardImage());
	set_image(*image_);
	set_sensitive(false);

	// event listener
	signal_clicked().connect( sigc::mem_fun( *this, &CardButton::cardPlayed ) );
}

CardButton::~CardButton() {
	delete image_;
}

// player plays a card
void CardButton::cardPlayed(){
	controller_->playTurn(currentCard_, isDiscard_);
}

// sets the card in hand in GUI
void CardButton::setCard(Card* card, bool enableButton, bool isDiscard){
	currentCard_ = card;
	isDiscard_ = isDiscard;
	set_sensitive(enableButton);

	delete image_;

	if (card){
		image_ = new Gtk::Image(view_->getCardImage(card->getSuit(), card->getRank()));
	}
	else{
		image_ = new Gtk::Image(view_->getNullCardImage());
	}

	set_image(*image_);
}