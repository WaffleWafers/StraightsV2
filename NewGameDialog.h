#ifndef _NEWGAMEDIALOG_
#define _NEWGAMEDIALOG_

#include <gtkmm/box.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/dialog.h>
#include <gtkmm/label.h>

#include <string>

class Model;

// GUI related dialog box
// initially appears so user can set which players are computers/user controlled
class NewGameDialog : public Gtk::Dialog {
public:
	NewGameDialog(Gtk::Window& parentWindow, Model*);
	virtual ~NewGameDialog();
private:
	Model* model_;

	Gtk::VBox* buttonContainer;
	Gtk::Label descriptionLabel;
	Gtk::CheckButton* checkButtons[4];
};

#endif