#include <stdio.h>
#include "card.h"

card* constructCard() {
    card* c = malloc(sizeof(card));
    c->rows[0] = malloc(sizeof(cardrow));
    c->rows[1] = malloc(sizeof(cardrow));
    return c;
}

card* constructCardWithRows(cardrow* zeroRow, cardrow* oneRow) {
    card* c = malloc(sizeof(card));
    c->rows[0] = zeroRow;
    c->rows[1] = oneRow;
    return c;
}

void setCardRow(card* c, bool position, bool writeValue, bool shiftRight, int nextCardNo) {
    printf("Writing card row %d : %d %d %d\n", position, writeValue, shiftRight, nextCardNo);
    if (c->rows[position] == NULL) {
        c->rows[position] = malloc(sizeof(cardrow));
    }
    c->rows[position]->writeVal = writeValue;
    c->rows[position]->shiftRight = shiftRight;
    c->rows[position]->nextCard = nextCardNo;
}

void destroyCard(card* c) {
    for (int i=0; i<2; i++) {
        free(c->rows[i]);
    }
    free(c);
}

void printCardRow(bool n, cardrow crdrow) {
    printf("|%d : %d %d %d|\n", n, crdrow.writeVal, crdrow.shiftRight, crdrow.nextCard);
}

void printCard(int crdNum, card * crd) {
    printf("===========\n");
    printf("|# Card%d #|\n", crdNum);
    printCardRow(0, *crd->rows[0]);
    printCardRow(1, *crd->rows[1]);
    printf("===========\n");
}
