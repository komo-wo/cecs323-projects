// Katherine Kim
// Class (CECS 325-01)
// Project Name (Prog 1 – Fibonacci Solitaire)
// Due Date (09/25/2025)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Card {
private:
    char suit;
    char rank;

public:
    Card();
    Card(char r, char s);
    void setCard(char r, char s);
    int getValue();
    void display();
};

Card::Card() {
    suit = ' ';
    rank = ' ';
}

Card::Card(char r, char s) {
    suit = s;
    rank = r;
}

void Card::setCard(char r, char s) {
    suit = s;
    rank = r;
}

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

void Card::display() {
    cout << rank << suit;
}

class Deck {
private:
    Card arr[52];
    int card;

public:
    vector<Card> cards;
    Deck();
    void newDeck();
    Card deal();
    void shuffle();
    bool isEmpty();
    void display();
};

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
    card = -1;
}

void Deck::newDeck() {
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
    card = -1;
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
    return card == 51;
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

bool isFibo(int number) {
    if (number == 1 || number == 2 || number == 3 || number == 5 || number == 8
        || number == 13 || number == 21 || number == 34 || number == 55 || number == 89
        || number == 144 || number == 233 || number == 377) {
        return true;
    } else {
        return false;
    }
}

int playFiboSolitaire(Deck &deck) {
    int sum = 0;
    int pileCount = 0;

    while (!deck.isEmpty()) {
        Card card = deck.deal();
        cout << "Top Card: ";
        card.display();
        sum += card.getValue();
        cout << "Sum: " << sum << endl;

        if (isFibo(sum)) {
            cout << "Sum is a Fibonacci number! Discarding pile." << endl;
            sum = 0;
            pileCount++;
        }
    }

    return pileCount;
}

int main() {
    Deck deck;
    int choice;

    while (true) {
        cout << "1) Create New Deck" << endl;
        cout << "2) Shuffle Deck" << endl;
        cout << "3) Display Deck" << endl;
        cout << "4) Play Fibo Solitaire" << endl;
        cout << "5) Win Fibo Solitaire" << endl;
        cout << "6) Exit" << endl;

        cin >> choice;

        if (choice == 1) {
            deck.newDeck();
        } else if (choice == 2) {
            deck.shuffle();
            cout << "Deck shuffled." << endl;
        } else if (choice == 3) {
            deck.display();
        } else if (choice == 4) {
            cout << "Playing Fibo Solitaire..." << endl;
            int pileCount = playFiboSolitaire(deck);
            cout << "Game over. Total Fibonacci piles created: " << pileCount << endl;
        } else if (choice == 5) {
            cout << "Playing Win Fibo Solitaire..." << endl;
            int gamesPlayed = 0;
            int totalPiles = 0;
            while (true) {
                gamesPlayed++;
                deck.newDeck();
                deck.shuffle();
                int pileCount = playFiboSolitaire(deck);
                if (isFibo(deck.cards.back().getValue())) {
                    cout << "Winner! Found a Fibonacci pile with a total of " << deck.cards.back().getValue() << endl;
                    cout << "Total games played to win: " << gamesPlayed << endl;
                    break;
                } else {
                    totalPiles += pileCount;
                }
            }
            cout << "Total Fibonacci piles created in all games: " << totalPiles << endl;
        } else if (choice == 6) {
            cout << "Goodbye!" << endl;
            return 0;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
