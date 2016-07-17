#ifndef _PLAYERFRAME_
#define _PLAYERFRAME_

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>

#include <string>

class Model;
class View;
class Controller;

// GUI class for displaying player information
// such as: CPU/Human, score and actions for rage
class PlayerFrame : public Gtk::Frame {
public:
	PlayerFrame(int, Model*, View*, Controller*);
	virtual ~PlayerFrame();
	void update(); // update displayed information

private:
	int playerIndex_; // 1-4

	void rageButtonClicked(); // user clicks rage button (human controlled -> CPU)

	// MVC model
	Model* model_;
	View* view_;
	Controller* controller_;

	Gtk::VBox mainContainer;

	Gtk::Button rageButton;
	Gtk::Label pointsLabel;
	Gtk::Label discardsLabel;

};

#endif