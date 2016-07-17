#ifndef _PLAYLOG_
#define _PLAYLOG_

#include <gtkmm.h>

#include <string>

class Model;
class View;
class Controller;

class PlayLog : public Gtk::ScrolledWindow {
public:
	PlayLog(Model*, View*, Controller*);
	virtual ~PlayLog();
	void appendWith(std::string);
	void clear();
	void startNewLog();
	void addToLog(std::string);

private:

	Model* model_;
	View* view_;
	Controller* controller_;

	Gtk::TextView textContainer;
  
	Glib::RefPtr<Gtk::TextBuffer> textBuffer;

	std::string log_;

};

#endif