#include <stdio.h>
#include "card.h"
#include "deck.h"

// gcc card.c deck.c zz-test-deck.c -o test-deck.exe

void assignCardRows(card* card, int* cardValsArray) {
    setCardRow(card, 0, cardValsArray[0], cardValsArray[1], cardValsArray[2]);
    setCardRow(card, 1, cardValsArray[3], cardValsArray[4], cardValsArray[5]);
}

void generateTestCards(card* cards) {
    card* cardA = constructCard();
    card* cardB = constructCard();
    card* cardC = constructCard();
    card* cardD = constructCard();
    card* cardE = constructCard();

    int cardAArray[6] = {1, 0, 2, 0, 0, 2};
    int cardBArray[6] = {1, 1, 1, 0, 1, 0};
    int cardCArray[6] = {1, 1, 0, 1, 1, 2};
    int cardDArray[6] = {0, 1, 1, 1, 0, 0};
    int cardEArray[6] = {0, 1, 0, 1, 1, 0};

    assignCardRows(cardA, cardAArray);
    assignCardRows(cardB, cardBArray);
    assignCardRows(cardC, cardCArray);
    assignCardRows(cardD, cardDArray);
    assignCardRows(cardE, cardEArray);

    cards[0] = *cardA;
    cards[1] = *cardB;
    cards[2] = *cardC;
    cards[3] = *cardD;
    cards[4] = *cardE;
}

// Test Deck
int main(int argc, char* argv[]) {

    deck* turingDeck = constructDeck(1);

    card cards[5];
    generateTestCards(cards);

    printf("Printing Cards from Array...\n");
    for (int i=0; i<5; i++) {
        printCard(i+1, &cards[i]);
    }

    printf("Adding Cards to Deck...\n");
    for (int i=0; i<5; i++) {
        addCard(turingDeck, &cards[i]);
    }

    printf("Printing Cards from Deck...\n");
    for (int i=0; i<5; i++) {
        printCard(i+1, turingDeck->cards[i]);
    }

    destroyDeck(turingDeck);
    for (int i=0; i<5; i++) {
        destroyCard(&cards[i]);
    }
}
