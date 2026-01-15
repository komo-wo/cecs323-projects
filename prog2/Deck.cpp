#include "Deck.h"
#include "Card.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Deck.h"
#include <cstdlib>
#include <ctime>

int card = 0;

Deck::Deck() {
    int counter = 0;
    char suit[4] = {'S', 'H', 'D', 'C'};
    char rank[13] = {'A', '2', '3', '4', '5', '6', '7',
                    '8', '9', 'T', 'J', 'Q', 'K'};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            arr[counter] = Card(rank[j], suit[i]);
            counter++;
        }
    }
    card = -1; // Initialize card to -1
}

void Deck::newDeck() { 
    // Reinitialize the deck in the same way as the constructor
    int counter = 0;
    char suit[4] = {'S', 'H', 'D', 'C'};
    char rank[13] = {'A', '2', '3', '4', '5', '6', '7',
                    '8', '9', 'T', 'J', 'Q', 'K'};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            arr[counter] = Card(rank[j], suit[i]);
            counter++;
        }
    }
    card = -1; // Reset card to -1
}

Card Deck::deal() {
    card++;
    return arr[card];
}

void Deck::shuffle() {
    srand(static_cast<unsigned>(time(NULL)));
    for (int i = 0; i < 52; i++) {
        int r = i + (rand() % (52 - i));
        Card temp = arr[i];
        arr[i] = arr[r];
        arr[r] = temp;
    }
}

bool Deck::isEmpty() {
    return card == 51; // Deck is empty when all cards have been dealt
}

void Deck::display() {
    int count = 0;
    for (int i = 0; i < 52; i++) {
        arr[i].display();
        count++;
        if (count % 13 == 0) {
            cout << endl;
        } else {
            cout << " ";
        }
    }
}
