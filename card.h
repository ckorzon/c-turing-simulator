#ifndef CARD_H
#define CARD_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct CardRow {
    bool writeVal;
    bool shiftRight;
    int nextCard;
} cardrow;

typedef struct Card {
    cardrow rows[2];
} card;

// cardrow* constructCardRow(bool writeVal, bool shiftRight, int nextCard);

void setCardRow(card* c, bool position, bool writeValue, bool shiftRight, int nextCardNo);

card* constructCard();

card* constructCardWithRows(cardrow* zeroRow, cardrow* oneRow);

void destroyCard(card* c);

void printCardRow(bool n, cardrow crdrow);

void printCard(int crdNum, card * crd);

#endif // CARD_H