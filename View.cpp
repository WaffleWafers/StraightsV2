#include "View.h"
#include <iostream>

// Creates buttons with labels. Sets butBox elements to have the same size, 
// with 10 pixels between widgets
View::View(Controller *c, Model *m) : model_(m), controller_(c), topToolbar(), newGameButton("Start new game with seed:"), endGameButton("End current game"), table(4, 13, true){

	// Sets some properties of the window.
	set_title( "Straights" );
	set_border_width( 10 );
	set_position(Gtk::WIN_POS_CENTER);


	// Properties of main container of game
	mainContainer.pack_start(topToolbar);
	mainContainer.pack_start(tableFrame);
	mainContainer.pack_start(playerListContainer);
	mainContainer.pack_start(currentHandFrame);


	// Add random seed, new game and end game buttons to the toolbar
	topToolbar.pack_start(newGameButton);
	topToolbar.pack_start(randomSeedEntry);
	topToolbar.pack_start(endGameButton);


	// Set up table for the cards played
	table.set_row_spacings(1);
	table.set_col_spacings(6);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			cardsOnTable[i][j] = new Gtk::Image(deck.getCardImage(static_cast<Suit>(i), static_cast<Rank>(j)));
			table.attach(*cardsOnTable[i][j], j, j+1, i, i+1);
		}
	}

	tableFrame.set_label("Cards on the table");
	tableFrame.add( table );


	// Set up player information + ragequit button
	for (int i = 0; i < 4; i++) {
		playerFrames[i] = new PlayerFrame(i + 1, model_, this, controller_);
		playerListContainer.pack_start(*playerFrames[i]);
	}


	// Set up hand display 
	for (int i = 0; i < 13; i++) {
		cardsInHand[i] = new CardButton(model_, this, controller_);
		handContainer.pack_start(*cardsInHand[i]);
	}


	currentHandFrame.set_label("Your hand");
	currentHandFrame.add(handContainer);


	// Set up signal handlers for buttons
	newGameButton.signal_clicked().connect( sigc::mem_fun( *this, &View::newGameButtonClicked ) );
	endGameButton.signal_clicked().connect( sigc::mem_fun( *this, &View::endGameButtonClicked ) );


	// Add main container to the window
	add( mainContainer );

	// Display everything
	show_all();

	NewGameDialog newGameDialog( *this, model_ );

	// Register view as observer of model
	model_->subscribe(this);

} // View::View


View::~View() {
	for (int i = 0 ; i < 4 ; i++) {
		for (int j = 0; j < 13; j++) 
			delete cardsOnTable[i][j];
	}

	for (int i = 0 ; i < 13 ; i++ )
		delete cardsInHand[i];

	for (int i = 0 ; i < 4 ; i++) {
		delete playerFrames[i];
	}
}


void View::update() {
	setHandDisplayed(model_->getCurrentPlayer()->getHand());
}


void View::newGameButtonClicked() {
	controller_->startGame(0);
}


void View::endGameButtonClicked() {
	controller_->endGame();
}


void View::setHandDisplayed(std::vector<Card*> hand){
	for (int i = 0; i < 13; i++){
		bool cardExists = !hand.empty() && i < hand.size();

		if (cardExists){
			cardsInHand[i]->setCard(hand.at(i));
		}
		else {
			cardsInHand[i]->setCard(NULL);
		}
	}
}


Glib::RefPtr<Gdk::Pixbuf> View::getNullCardImage() const {
	return deck.getNullCardImage();
}


Glib::RefPtr<Gdk::Pixbuf> View::getCardImage(Suit s, Rank r) const {
	return deck.getCardImage(s, r);
}

