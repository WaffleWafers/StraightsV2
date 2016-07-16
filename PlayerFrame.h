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

class PlayerFrame : public Gtk::Frame {
public:
	PlayerFrame(int, Model*, View*, Controller*);
	virtual ~PlayerFrame();
	void update();

private:
	int playerIndex_;

	Model* model_;
	View* view_;
	Controller* controller_;

	Gtk::VBox mainContainer;

	Gtk::Button rageButton;
	Gtk::Label pointsLabel;
	Gtk::Label discardsLabel;

};

#endif