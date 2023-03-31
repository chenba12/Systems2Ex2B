#include "card.hpp"

using namespace ariel;

Card::Card(cardValues value, cardSymbols symbol) {
    this->value = value;
    this->symbol = symbol;
}

Card::Card(const Card &card) {
    this->value = card.value;
    this->symbol = card.symbol;
}

Card::Card() {
    this->value = Ace;
    this->symbol = Hearts;
}

std::ostream &ariel::operator<<(std::ostream &os, const Card &card) {
    os << card.getValue() << " of " << card.getSymbol();
    return os;
}

bool Card::operator==(const Card &rhs) const {
    return value == rhs.value &&
           symbol == rhs.symbol;
}

bool Card::operator!=(const Card &rhs) const {
    return !(rhs == *this);
}

Card::~Card() = default;


int Card::checkWinner(Card &p2Card) {
    if (this->value == Ace || p2Card.value == Ace) {
        if (this->value == Ace && p2Card.value == Two) return P2WIN;
        else if (this->value == Ace && p2Card.value != Two)return P1WIN;
        else if (this->value == Two && p2Card.value == Ace) return P1WIN;
        else if (this->value != Two && p2Card.value != Ace)return P2WIN;
        else if (this->value == Ace && p2Card.value == Ace) return TIE;
    }
    if (this->value > p2Card.value) return P1WIN;
    else if (this->value == p2Card.value)return TIE;
    else return P2WIN;
}

std::string Card::getValue() const {
    switch (this->value) {
        case Ace:
            return "Ace";
        case Two:
            return "Two";
        case Three:
            return "Three";
        case Four:
            return "Four";
        case Five:
            return "Five";
        case Six:
            return "Six";
        case Seven:
            return "Seven";
        case Eight:
            return "Eight";
        case Nine:
            return "Nine";
        case Ten:
            return "Ten";
        case Jack:
            return "Jack";
        case Queen:
            return "Queen";
        case King:
            return "King";
        default:
            return "UNKNOWN";
    }

}

void Card::setValue(cardValues newValue) {
    Card::value = newValue;
}

std::string Card::getSymbol() const {
    switch (this->symbol) {
        case Hearts:
            return "Hearts";
        case Diamonds:
            return "Diamonds";
        case Clubs:
            return "Clubs";
        case Spades:
            return "Spades";
        default:
            return "UNKNOWN";
    }
}

void Card::setSymbol(cardSymbols newSymbol) {
    Card::symbol = newSymbol;
}






