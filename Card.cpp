#include "Card.h"
#include <string>
#include <cassert>
using namespace std;

Card::InvalidCardException::InvalidCardException(const string card){
	message = "ERROR: Invalid card \"" + card + "\" was entered in a command.\n";
	message += "Please enter a new command with a valid card.";
}

Card::Card(Suit s, Rank r){
	suit_ = s;
	rank_ = r;
}

Suit Card::getSuit() const{
	return suit_;
}

Rank Card::getRank() const{
	return rank_;
}

bool operator==(const Card &a, const Card &b){
	return a.getSuit() == b.getSuit() && a.getRank() == b.getRank();
}

ostream &operator<<(ostream &out, const Card &c){
	string suits[SUIT_COUNT] = {"C", "D", "H", "S"};
	string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};

	out << ranks[c.getRank()] << suits[c.getSuit()];

	return out;
}

istream &operator>>(istream &in, Card &c){
	string suits = "CDHS", ranks = "A234567891JQK";

	string str;
	in >> str;
	if ( in.fail() ){
		throw Card::InvalidCardException(str);
	}

	if ( str.size() < 2 ){
		throw Card::InvalidCardException(str);
	}

	//Read in the rank, make sure it's valid
	c.rank_ = (Rank)ranks.find( str.at(0) );
	if ( c.rank_ == string::npos ){
		throw Card::InvalidCardException(str);
	}

	//If it's a 10, make sure the 2nd character is a 0
	if ( c.rank_ == TEN ){
		if (str.at(1) != '0'){
			throw Card::InvalidCardException(str);
		}
		str.at(1) = str.at(2);
	}

	//Read in the suit, make sure it's valid
	c.suit_ = (Suit)suits.find( str.at(1) );
	if ( c.suit_ == string::npos ){
		throw Card::InvalidCardException(str);
	}

	return in;
}
