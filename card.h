typedef struct CardRow {
    bool writeVal;
    bool shiftRight;
    int nextCard;
} cardrow;

typedef struct Card {
    cardrow rows[2];
} card;