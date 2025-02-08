#ifndef DECK_H
#define DECK_H

#include <stdlib.h>
#include "card.h"

typedef struct Deck {
    int capacity;
    int size;
    card** cards;
} deck;

deck* constructDeck(int initialCapacity);

void addCard(deck* deck, card* newCard);

void expandDeckCapacity(deck* deck, int capacityFactor);

void destroyDeck(deck* deck);

#endif // DECK_H