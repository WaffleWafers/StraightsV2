#ifndef _DECKGUI_
#define _DECKGUI_

#include <gdkmm/pixbuf.h>
#include <vector>

#include "model.h"

class DeckGUI {
public:
	DeckGUI();
	virtual ~DeckGUI();
	Glib::RefPtr<Gdk::Pixbuf> getCardImage( Suit s, Rank r ) const;	// Returns the image for the specified card.
	Glib::RefPtr<Gdk::Pixbuf> getNullCardImage() const;				// Returns the image to use for the placeholder.

private:
	std::vector< Glib::RefPtr< Gdk::Pixbuf > > deck;		// Contains the pixel buffer images.
};

#endif
