#include "Card.h"
#include "Deck.h"
#include <iostream>

using namespace std;

// Constructor for a Card with default values
Card::Card() {
    suit = ' ';
    rank = ' ';
}

// Constructor for a Card with specified rank and suit
Card::Card(char r, char s) {
    suit = s;
    rank = r;
}

// Setter method to set the rank and suit of a card
void Card::setCard(char r, char s) {
    suit = s;
    rank = r;
}

// Getter method to get the value of a card (Ace = 1, 2-10 = 2-10, J/Q/K = 10)
int Card::getValue() {
    int num[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    char pen[5] = {'A', 'J', 'Q', 'K', 'T'};
    int value = 0;

    for (int i = 0; i < 5; i++) {
        if (rank == pen[i]) {
            value = num[i];
            break;
        }
    }

    return value;
}

// Display the card (e.g., "7H" for 7 of Hearts)
void Card::display() {
    cout << rank << suit;
}