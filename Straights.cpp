#ifdef _WIN32
#include <iostream>
#include <Windows.h>
#include <MMSystem.h>
#endif

#include <gtkmm.h>

#include "Model.h"
#include "View.h"
#include "Controller.h"

int main( int argc, char * argv[] ) {

	Gtk::Main kit( argc, argv );			// Creates a Gtk::Main object 

	Model model;							// Create model
	Controller controller( &model );		// Create controller
	View view( &controller, &model );		// Create the view

	#ifdef _WIN32
		PlaySound(TEXT("Scarlet_Rose.wav"), NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
	#endif

	Gtk::Main::run( view );					// Show the window and return when it is closed

	return 0;

}
