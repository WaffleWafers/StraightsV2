#include <gtkmm.h>

#include "Model.h"
#include "View.h"
#include "Controller.h"

using namespace std;

int main( int argc, char * argv[] ) {

	Gtk::Main kit( argc, argv );			// Creates a Gtk::Main object 

	Model model;							// Create model
	Controller controller( &model );		// Create controller
	View view( &controller, &model );		// Create the view

	Gtk::Main::run( view );					// Show the window and return when it is closed

	return 0;

}
