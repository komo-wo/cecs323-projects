#ifndef PUBLICATION_CARD_H
#define PUBLICATION_CARD_H
#include <iostream>
using namespace std;

class Card
{
    private:
        char suit;
        char rank;
    public:
        Card( ); // create a “default” card
        Card( char r, char s ); // constructor to create a card, setting the rank and suit
        void setCard( char r, char s); //set existing card to new values
        int getValue( ); // return the point value of the card. Ace = 1, 2 thru 10, Jack = 10, Queen = 10, King = 10
        void display( ); // display the card using 2 fields... Ace of Spade
};
#endif