#include <stdio.h>
#include "card.h"

card* constructCard() {
    card* c = malloc(sizeof(card));
    return c;
}

card* constructCardWithRows(cardrow* zeroRow, cardrow* oneRow) {
    card* c = malloc(sizeof(card));
    c->rows[0] = *zeroRow;
    c->rows[1] = *oneRow;
    return c;
}

void setCardRow(card* c, bool position, bool writeValue, bool shiftRight, int nextCardNo) {
    printf("Writing card row %d : %d %d %d\n", position, writeValue, shiftRight, nextCardNo);
    c->rows[position].writeVal = writeValue;
    c->rows[position].shiftRight = shiftRight;
    c->rows[position].nextCard = nextCardNo;
}

void destroyCard(card* c) {
    free(c->rows);
    free(c);
}

void printCardRow(bool n, cardrow crdrow) {
    printf("|%d : %d %d %d|\n", n, crdrow.writeVal, crdrow.shiftRight, crdrow.nextCard);
}

void printCard(int crdNum, card * crd) {
    printf("===========\n");
    printf("|# Card%d #|\n", crdNum);
    printCardRow(0, crd->rows[0]);
    printCardRow(1, crd->rows[1]);
    printf("===========\n");
}
