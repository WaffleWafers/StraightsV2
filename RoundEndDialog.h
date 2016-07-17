#ifndef _ROUNDENDDIALOG_
#define _ROUNDENDDIALOG_

#include <gtkmm/box.h>
#include <gtkmm/dialog.h>
#include <gtkmm/label.h>

#include <string>

class Model;

class RoundEndDialog : public Gtk::Dialog {
public:
	RoundEndDialog(Gtk::Window& parentWindow, Model*, bool);
	virtual ~RoundEndDialog();
private:
	Model* model_;
	bool gameEnded_;
	
	int getWinningScore();

	Gtk::VBox* scoreContainer;
	Gtk::Label* playerScoreLabel[4];
	Gtk::Label description;
};

#endif