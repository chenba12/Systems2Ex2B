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

std::ostream &ariel::operator<<(std::ostream &pos, const Card &card) {
    pos << card.getValue() << " of " << card.getSymbol();
    return pos;
}

bool Card::operator==(const Card &rhs) const {
    return value == rhs.value &&
           symbol == rhs.symbol;
}

bool Card::operator!=(const Card &rhs) const {
    return !(rhs == *this);
}

Card::~Card() = default;

Card &Card::operator=(const Card &other) {
    if (this != &other) {
        this->value = other.value;
        this->symbol = other.symbol;
    }
    return *this;
}

Card::Card(Card &&other) noexcept {
    this->value = other.value;
    this->symbol = other.symbol;

    other.value = Ace;
    other.symbol = Hearts;
}

Card &Card::operator=(Card &&other) noexcept {
    if (this != &other) {
        this->value = other.value;
        this->symbol = other.symbol;

        other.value = Ace;
        other.symbol = Hearts;
    }
    return *this;
}


int Card::checkWinner(const Card &p2Card) const {
    if (this->value == Ace || p2Card.value == Ace) {
        if (this->value == Ace && p2Card.value == Two) return P2Win;
        else if (this->value == Ace && p2Card.value != Two)return P1Win;
        else if (this->value == Two && p2Card.value == Ace) return P1Win;
        else if (this->value != Two && p2Card.value != Ace)return P2Win;
        else if (this->value == Ace && p2Card.value == Ace) return Tie;
    }
    if (this->value > p2Card.value) return P1Win;
    else if (this->value == p2Card.value)return Tie;
    else return P2Win;
}

std::string Card::getValue() const {
    switch (this->value) {
        case Ace:
            return "Ace";
        case Two:
            return "2";
        case Three:
            return "3";
        case Four:
            return "4";
        case Five:
            return "5";
        case Six:
            return "6";
        case Seven:
            return "7";
        case Eight:
            return "8";
        case Nine:
            return "9";
        case Ten:
            return "10";
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












