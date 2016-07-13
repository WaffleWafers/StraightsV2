#include "model.h"


Model::Model() : topCard_(-1) {}

Suit Model::suit() {
  if (topCard_ == -1) return SUIT_COUNT;
  
  return (Suit) (topCard_ % numSuits);
}

Rank Model::rank() {
  if (topCard_ == -1) return RANK_COUNT;

  return (Rank) (topCard_ / numSuits);
}

void Model::nextCard() {
  if (topCard_ == numCards-1) return;

  topCard_ += 1;
  notify();

}

void Model::resetCards() {
  topCard_ = -1;
  notify();
}
