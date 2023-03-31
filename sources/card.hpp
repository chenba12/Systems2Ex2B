#include <iostream>

#ifndef CARD_HPP
#define CARD_HPP
namespace ariel {
    enum cardSymbols {
        Hearts = 1, Diamonds = 2, Clubs = 3, Spades = 4
    };
    enum winState {
        NoWinner = -1, Tie = 0, P1Win = 1, P2Win = 2
    };
    enum cardValues {
        Ace = 1,
        Two = 2,
        Three = 3,
        Four = 4,
        Five = 5,
        Six = 6,
        Seven = 7,
        Eight = 8,
        Nine = 9,
        Ten = 10,
        Jack = 11,
        Queen = 12,
        King = 13
    };

    class Card {
    private:
        cardValues value;
        cardSymbols symbol;
    public:
        Card(cardValues value, cardSymbols symbol);

        Card(const Card &card);

        Card();

        friend std::ostream &operator<<(std::ostream &os, const Card &card);

        bool operator==(const Card &rhs) const;

        bool operator!=(const Card &rhs) const;

        ~Card();


        int checkWinner(const Card &card) const;

        std::string getValue() const;

        void setValue(cardValues newValue);

        std::string getSymbol() const;

        void setSymbol(cardSymbols newSymbol);


    };
}
#endif