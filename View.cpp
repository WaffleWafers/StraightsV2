#include "View.h"
#include <iostream>
#include <string>

using namespace std;

// Creates buttons with labels. Sets butBox elements to have the same size, 
// with 10 pixels between widgets
View::View(Controller *c, Model *m) : model_(m), controller_(c), topToolbar(), newGameButton("Start new game with seed:"), endGameButton("End current game"), table(4, 13, true){

	// Sets some properties of the window.
	set_title( "Straights" );
	set_border_width( 10 );
	set_position(Gtk::WIN_POS_CENTER);
	set_resizable(false);

	// Properties of main container of game
	mainContainer.pack_start(topToolbar);
	mainContainer.pack_start(tableFrame);
	mainContainer.pack_start(playerListContainer);
	mainContainer.pack_start(turnInstructions);
	mainContainer.pack_start(currentHandFrame);
	mainContainer.pack_start(playLog);


	// Add random seed, new game and end game buttons to the toolbar
	topToolbar.pack_start(newGameButton);
	topToolbar.pack_start(randomSeedEntry);
	randomSeedEntry.set_text(to_string(model_->getSeed()));
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
		cardsInHand[i] = new CardButton(this, controller_);
		handContainer.pack_start(*cardsInHand[i]);
	}


	turnInstructions.set_editable(false);
	turnInstructions.set_alignment(0.5);


	currentHandFrame.set_label("Your hand");
	currentHandFrame.add(handContainer);


	// Set up signal handlers for buttons
	newGameButton.signal_clicked().connect( sigc::mem_fun( *this, &View::newGameButtonClicked ) );
	endGameButton.signal_clicked().connect( sigc::mem_fun( *this, &View::endGameButtonClicked ) );


	// Add main container to the window
	add( mainContainer );

	// Display everything
	show_all();

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
	playLog.addToLog(model_->getLogMessage());
	setHandDisplayed(model_->getCurrentPlayer()->getHand(), model_->getCurrentPlayer()->getLegalCards());
	for (int i = 0 ; i < 4 ; i++){
		playerFrames[i]->update();
	}

	if (model_->getState() == Model::IN_PROGRESS){
		if (model_->getCurrentPlayer()->getLegalCards().empty()){
			turnInstructions.set_text("Player " + to_string(model_->getCurrentPlayer()->getPlayerNo()) + "'s turn - You have no legal plays. Select a card to discard.");
		}
		else {
			turnInstructions.set_text("Player " + to_string(model_->getCurrentPlayer()->getPlayerNo()) + "'s turn - Select a card to play.");
		}

		setTableDisplay();
	}
	else if (model_->getState() == Model::ROUND_ENDED){
		setTableDisplay();
		RoundEndDialog newRoundEndDialog( *this, model_, false );
	}
	else if (model_->getState() == Model::GAME_ENDED){
		turnInstructions.set_text("");
		resetTableDisplay();
		RoundEndDialog newRoundEndDialog( *this, model_, true );
	}
}


void View::newGameButtonClicked() {
	controller_->endGame();
	playLog.startNewLog();
	controller_->setSeed(atoi(static_cast<string>(randomSeedEntry.get_text()).c_str()));
	NewGameDialog newGameDialog( *this, model_ );
	controller_->startGame();
}


void View::endGameButtonClicked() {
	controller_->endGame();
	exit(EXIT_SUCCESS);
}


void View::setHandDisplayed(vector<Card*> hand, vector<Card*> legalCards){

	bool noLegalPlays = legalCards.empty();

	for (int i = 0; i < 13; i++){
		if (noLegalPlays && !hand.empty() && i < hand.size()){
			cardsInHand[i]->setCard(hand.at(i), true, true);
		}
		else if (!hand.empty() && i < hand.size()){
			bool legalCardMatches = false;

			for(unsigned int j = 0; j < legalCards.size(); j++){
				if(hand.at(i)->getSuit() == legalCards[j]->getSuit() &&
					hand.at(i)->getRank() == legalCards[j]->getRank()){
						legalCardMatches = true;
						break;
				}
			}
			cardsInHand[i]->setCard(hand.at(i), legalCardMatches, false);
		}
		else {
			cardsInHand[i]->setCard(NULL, false, false);
		}
	}
}


void View::resetTableDisplay(){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			cardsOnTable[i][j]->set(deck.getCardImage(static_cast<Suit>(i), static_cast<Rank>(j)));
		}
	}
}


void View::setTableDisplay(){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			if (!model_->hasBeenPlayed(static_cast<Suit>(i), static_cast<Rank>(j))) {
				cardsOnTable[i][j]->set(deck.getNullCardImage());
			}
			else {
				cardsOnTable[i][j]->set(deck.getCardImage(static_cast<Suit>(i), static_cast<Rank>(j)));
			}
		}
	}
}


Glib::RefPtr<Gdk::Pixbuf> View::getNullCardImage() const {
	return deck.getNullCardImage();
}


Glib::RefPtr<Gdk::Pixbuf> View::getCardImage(Suit s, Rank r) const {
	return deck.getCardImage(s, r);
}

