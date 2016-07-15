#ifndef _MODEL_
#define _MODEL_

#include <vector>
#include <string>

#include "Subject.h"
#include "Card.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"

class Model: public Subject{
public:
	Model();
	Model(int);
	~Model();

	void setCurrentPlayer(int);
	// modifies this.currentPlayer_

	// getters
	Player* getFirstPlayer() const;
	Player* getCurrentPlayer() const;
	Player* getPlayer(int) const;
	std::vector<Card*> getDeck() const;
	int getSeed() const;

	void setPlayerType(int, char); // Populates playerTypes_ array with types of players (int playerNumber, char playerType)
	void initDeck(); // Initialize the deck (populates deck_ with New Card's)
	void initPlayers(); // Initialize players (populates players_ with New Player's)
	void setSeed(int); // Setms seed for the shuffle
	void shuffle(); // Shuffles the deck
	void deal(); // Deal 13 Card*'s to each player
	bool playCard(Card); // Plays card from hand
	bool discardCard(Card); // Removes card from hand and adds to discard pile
	void advanceToNextPlayer(); // Change to next player
	void setHumanToComputer(); // Create new computer player with assignment and delete old human player
	void deleteCardsAndPlayers();
	void clearCardsFromTable(); // Empties table of all cards (sets all of 2D array to false)
	void cleanUp();
	void updateView();

private:
	Card* getCard(Card);
	std::vector<Player*> players_;
	std::vector<Card*> deck_;
	bool currentCardsOut_[4][13] = {{false}};
	int firstPlayer_;
	int currentPlayer_;
	int seed_;
	char playerTypes_[4];
};

#endif
