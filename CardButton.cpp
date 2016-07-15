#include "CardButton.h"
#include "View.h"
#include "Model.h"
#include "Controller.h"

CardButton::CardButton(Model* model, View* view, Controller* controller): model_(model), view_(view), controller_(controller), isDiscard_(false) {

	image_ = new Gtk::Image(view_->getNullCardImage());
	set_image(*image_);
	set_sensitive(false);

	signal_clicked().connect( sigc::mem_fun( *this, &CardButton::cardPlayed ) );

}

CardButton::~CardButton() {
	delete image_;
}


void CardButton::cardPlayed(){
	controller_->playTurn(currentCard_, isDiscard_);
}


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