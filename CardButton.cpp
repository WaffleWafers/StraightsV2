#include "CardButton.h"
#include "View.h"
#include "Model.h"
#include "Controller.h"

CardButton::CardButton(Model* model, View* view, Controller* controller): model_(model), view_(view), controller_(controller) {

	image_ = new Gtk::Image(view_->getNullCardImage());
	set_image(*image_);

	signal_clicked().connect( sigc::mem_fun( *this, &CardButton::cardPlayed ) );

}

CardButton::~CardButton() {
	delete image_;
}


void CardButton::cardPlayed(){
	controller_->playTurn(currentCard_);
}


void CardButton::setCard(Card* card){
	currentCard_ = card;

	delete image_;

	if (card)
		image_ = new Gtk::Image(view_->getCardImage(card->getSuit(), card->getRank()));
	else
		image_ = new Gtk::Image(view_->getNullCardImage());

	set_image(*image_);
}