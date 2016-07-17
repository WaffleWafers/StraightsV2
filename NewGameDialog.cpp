#include "NewGameDialog.h"
#include "Model.h"
#include <gtkmm/stock.h>
#include <iostream>

using std::string;

// Specifies the parent window of the dialog box and the title of the dialog box.
NewGameDialog::NewGameDialog( Gtk::Window & parentWindow, Model* model) : Dialog( "Player Sign-In", parentWindow, true, true ), model_(model), descriptionLabel("Select the players who are human.") {
	
	buttonContainer = this->get_vbox();
	buttonContainer->pack_start(descriptionLabel);

	// Set up a group of check buttons
	for ( int i = 0 ; i < 4 ; i++ ) {
		checkButtons[i] = new Gtk::CheckButton("Player " + std::to_string(i+1));
		checkButtons[i]->set_active();
		buttonContainer->pack_start(*checkButtons[i]);
	} 
	
	// Add a standard "ok" button with the appropriate responses when clicked.
	add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
	show_all_children();
	
	// Wait for a response from the dialog box.
	int result = run();
	switch (result) {
		case Gtk::RESPONSE_OK:
			// sets player types based on checkboxes from dialog box
			for ( int i = 0 ; i < 4; i++ ) {
				if ( checkButtons[i]->get_active() ) {
					model_->setPlayerType(i, 'h');
				}
				else{
					model_->setPlayerType(i, 'c');
				}
			}
			break;
  }     	
}

NewGameDialog::~NewGameDialog() {
	for ( int i = 0 ; i < 4 ; i++ )
		delete checkButtons[i];
}