#include "view.h"
#include <iostream>

// Creates buttons with labels. Sets butBox elements to have the same size, 
// with 10 pixels between widgets
View::View(Controller *c, Model *m) : model_(m), controller_(c), topToolbar(), newGameButton("Start new game with seed:"), endGameButton("End current game"), table(4, 13, true){

	// Sets some properties of the window.
	set_title( "Straights" );
	set_border_width( 10 );

	mainContainer.pack_start(topToolbar);
	mainContainer.pack_start(tableFrame);
	mainContainer.pack_start(playerListContainer);
	mainContainer.pack_start(currentHandFrame);


	topToolbar.pack_start(newGameButton);
	topToolbar.pack_start(randomSeedEntry);
	topToolbar.pack_start(endGameButton);


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


	for (int i = 0; i < 4; i++) {
		playerFrames[i] = new PlayerFrame(i + 1, model_, this, controller_);
		playerListContainer.pack_start(*playerFrames[i]);
	}


	for (int i = 0; i < 13; i++) {
		cardsInHand[i] = new Gtk::Image(deck.getNullCardImage());
		handContainer.pack_start(*cardsInHand[i]);
	}

	currentHandFrame.set_label("Your hand");
	currentHandFrame.add(handContainer);


	add( mainContainer );

	// The final step is to display the buttons (they display themselves)
	show_all();

	// Register view as observer of model
	model_->subscribe(this);

} // View::View

View::~View() {}


void View::update() {

}
