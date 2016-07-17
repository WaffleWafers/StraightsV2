#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include <string>
#include "Card.h"

class Model;

// Player class: inherited by ComputerPlayer and HumanPlayer
// Base for all player related actions for the game
// and information getters/setters
class Player{
public:
	explicit Player(int, Model*);
	virtual ~Player();
	Player(const Player&);
	Player& operator=(const Player&);

	void setHand(std::vector<Card*> cards)				{hand_ = cards;}
	void setDiscards(std::vector<Card*> cards)			{discards_ = cards;}
	void setScore(int score)							{score_	= score;}
	void setOldScore(int score)							{oldScore_ = score;}
	void setRoundScore(int score)						{roundScore_ = score;}
	void setPlayerNo(int num)							{playerNo_ = num;}
	void setValidPlay(bool isValid)						{validPlay_ = isValid;}
	void setModel(Model* model)							{model_ = model;}
	void resetRoundScore()								{roundScore_ = 0;}

	void addCard(Card*);
	std::vector<Card*> getLegalCards();

	virtual bool playCard(Card*) = 0;
	virtual bool discardCard(Card*) = 0;
	virtual bool isHuman() = 0;

	std::vector<Card*> getHand() const					{return hand_;}
	std::vector<Card*> getDiscards() const				{return discards_;}
	int getScore() const								{return score_;}
	int getOldScore() const								{return oldScore_;}	
	int getRoundScore() const							{return roundScore_;}
	int getPlayerNo() const								{return playerNo_;}
	Model* getModel() const								{return model_;}

	void newRoundReset();

protected:
	Model* model_; // MVC model
	std::vector<Card*> hand_;	// player hand
	std::vector<Card*> discards_; // player discard pile
	bool validPlay_; // player has a valid play
	int score_;
	int oldScore_; // score from previous round
	int roundScore_; // score obtained from round
	int playerNo_; // 1-4
};

#endif