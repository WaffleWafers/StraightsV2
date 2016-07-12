#ifndef _MODEL_
#define _MODEL_

#include <vector>
#include <string>

#include "subject.h"

const int numFaces = 6;
const int numSuits = 4;
const int numCards = numFaces * numSuits;

enum Faces { NINE, TEN, JACK, QUEEN, KING, ACE, NOFACE };
enum Suits { DIAMOND, CLUB, HEART, SPADE, NOSUIT };

class Model : public Subject {
public:
    Model();
    Suits suit();
    Faces face();
    void nextCard();
    void resetCards();
private:
    int topCard_;
}; // Model


#endif
