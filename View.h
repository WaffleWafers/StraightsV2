#ifndef _VIEW_
#define _VIEW_

#include <gtkmm.h>
#include "DeckGUI.h"
#include "observer.h"

class Controller;
class Model;


class View : public Gtk::Window, public Observer {
public:
	View( Controller*, Model* );
	virtual ~View();
	virtual void update();	// Observer Pattern: concrete update() method

private:
	// Observer Pattern: to access Model accessors without having to downcast subject
	Model *model_;
	
	// Strategy Pattern member (plus signal handlers)
	Controller *controller_;

	// Card Images
	DeckGUI deck;

	// Member widgets:
	Gtk::HBox panels;      // Main window divided into two horizontal panels
	Gtk::VBox butBox;      // Vertical boxes for stacking buttons vertically
	Gtk::Button next_button;
	Gtk::Button reset_button;
	Gtk::Image card;

	// Signal handlers:
	void nextButtonClicked();
	void resetButtonClicked();

}; // View

#endif
