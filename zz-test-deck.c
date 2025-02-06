#include "card.h"
#include "deck.h"


// Test Deck
int main(int argc, char* argv[]) {

    deck* turingDeck = constructDeck(1);
    
    cardrow zeroRow = { 1, 0, 2 };
    cardrow oneRow = { 0, 0, 2 };
    card cardA = { { &zeroRow, &oneRow } };

    addCard(turingDeck, &cardA);

    cardrow zeroRowB = { 1, 1, 1 };
    cardrow oneRowB = { 0, 1, 0 };
    card cardB = { { &zeroRowB, &oneRowB } };

    addCard(turingDeck, &cardB);

    cardrow zeroRowC = { 1, 1, 1 };
    cardrow oneRowC = { 0, 1, 0 };
    card cardC = { { &zeroRowC, &oneRowC } };

    addCard(turingDeck, &cardC);

    cardrow zeroRowD = { 1, 1, 1 };
    cardrow oneRowD = { 0, 1, 0 };
    card cardD = { { &zeroRowD, &oneRowD } };

    addCard(turingDeck, &cardD);

    cardrow zeroRowE = { 1, 1, 1 };
    cardrow oneRowE = { 0, 1, 0 };
    card cardE = { { &zeroRowE, &oneRowE } };

    addCard(turingDeck, &cardE);

    destroyDeck(turingDeck);
}
