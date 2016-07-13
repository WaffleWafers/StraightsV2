#ifndef _MODEL_
#define _MODEL_

#include <vector>
#include <string>

#include "Subject.h"
#include "Card.h"

const int numRanks = 13;
const int numSuits = 4;
const int numCards = numRanks * numSuits;

class Model : public Subject {
public:
    Model();
    Rank rank();
    Suit suit();
    void nextCard();
    void resetCards();
private:
    int topCard_;
}; // Model


#endif
