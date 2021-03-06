#include "PlayLog.h"

// constructor
PlayLog::PlayLog() {

	add(textContainer);
	set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

	textBuffer = Gtk::TextBuffer::create();

	textContainer.set_buffer(textBuffer);

	textContainer.set_editable(false);
}

PlayLog::~PlayLog() {}

// initialize game log
void PlayLog::startNewLog(){
	log_ = "A new game has started!";
	textBuffer->set_text(log_);
	textContainer.set_buffer(textBuffer);
}

// add line to history
void PlayLog::addToLog(std::string str){
	log_ += str;
	textBuffer->set_text(log_);
	textContainer.set_buffer(textBuffer);
	get_vadjustment()->set_value(get_vadjustment()->get_upper());
}