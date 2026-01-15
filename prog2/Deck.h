#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <iostream>
#include <vector>

using namespace std; 

class Deck {
private:
    Card arr[52];

public:
    vector<Card> cards;
    Deck();
    void newDeck();
    Card deal();
    void shuffle();
    bool isEmpty();
    void display();
};

#endif