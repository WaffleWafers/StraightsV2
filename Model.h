#ifndef _MODEL_
#define _MODEL_

#include <vector>
#include <string>

#include "Subject.h"
#include "Card.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"

// MVC Architecture "Model"
// Handles all the information from controller and the game
class Model: public Subject{
public:
	Model();
	Model(int);
	~Model();

	// Game has 3 states
	// 1) in progress ( all players have cards, no one has reached 80 points)
	// 2) round end (all players are out of cards, no one has reached 80 points)
	// 3) game ended (80 points have been reached)
	enum State { IN_PROGRESS, ROUND_ENDED, GAME_ENDED };

	// modifies this.currentPlayer_ directly
	void setCurrentPlayer(int);
	

	// getters
	Player* getFirstPlayer() const;
	Player* getCurrentPlayer() const;
	Player* getPlayer(int) const;
	std::vector<Card*> getDeck() const;
	int getSeed() const;
	State getState() const;
	// Get the message of player move for display on game log
	std::string getLogMessage() const;

	void setState(State);
	void setPlayerType(int, char); // Populates playerTypes_ array with types of players (int playerNumber, char playerType)
	void initDeck(); // Initialize the deck (populates deck_ with New Card's)
	void initPlayers(); // Initialize players (populates players_ with New Player's)
	void setSeed(int); // Setms seed for the shuffle
	void shuffle(); // Shuffles the deck
	void deal(); // Deal 13 Card*'s to each player
	bool playCard(Card*); // Plays card from hand
	bool discardCard(Card*); // Removes card from hand and adds to discard pile
	void advanceToNextPlayer(); // Change to next player
	void setHumanToComputer(); // Create new computer player with assignment and delete old human player
	void deleteCardsAndPlayers();
	void clearCardsFromTable(); // Empties table of all cards (sets all of 2D array to false)
	void cleanUp();

	bool hasBeenPlayed(Suit, Rank) const; // check if card has been played
	bool playerReachedPointLimit() const;

	// functions for log messages ( either a string, or card information)
	void setLogMessage(Card*, bool); // bool = is move a discard
	void setLogMessage(std::string);

private:
	Card* getCard(Card);

	std::vector<Player*> players_; // holds all players
	std::vector<Card*> deck_; // holds all card obj's

	bool currentCardsOut_[4][13] = {{false}}; // array for cards played

	State state_; // game state (3 states)
	int firstPlayer_;
	int currentPlayer_; // current player's turn
	int seed_;
	char playerTypes_[4];

	std::string logMessage_;
};

#endif
