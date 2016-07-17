#ifndef _PLAYLOG_
#define _PLAYLOG_

#include <gtkmm.h>

#include <string>

class PlayLog : public Gtk::ScrolledWindow {
public:
	PlayLog();
	virtual ~PlayLog();
	void startNewLog();
	void addToLog(std::string);

private:

	Gtk::TextView textContainer;
  
	Glib::RefPtr<Gtk::TextBuffer> textBuffer;

	std::string log_;

};

#endif