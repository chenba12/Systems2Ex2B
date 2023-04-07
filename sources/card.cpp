#include "card.hpp"

using namespace ariel;

/**
 * normal constructor
 */
Card::Card(cardValues value, cardSymbols symbol) {
    this->value = value;
    this->symbol = symbol;
}
/**
 * copy constructor
 */
Card::Card(const Card &card) {
    this->value = card.value;
    this->symbol = card.symbol;
}
/**
 * empty constructor
 */
Card::Card() {
    this->value = Ace;
    this->symbol = Hearts;
}

/**
 *  overwrite the << operator to return a string representation of the card
 */
std::ostream &ariel::operator<<(std::ostream &pos, const Card &card) {
    pos << card.getValue() << " of " << card.getSymbol();
    return pos;
}

/**
 * check if 2 cards are the same based on values/symbols
 * @param rhs the other card
 * @return true if equal false otherwise
 */
bool Card::operator==(const Card &rhs) const {
    return value == rhs.value &&
           symbol == rhs.symbol;
}

bool Card::operator!=(const Card &rhs) const {
    return !(rhs == *this);
}

/**
 * destructor
 */
Card::~Card() = default;

Card &Card::operator=(const Card &other) {
    if (this != &other) {
        this->value = other.value;
        this->symbol = other.symbol;
    }
    return *this;
}
/*
 * Copy and move constructor
 */
Card::Card(Card &&other) noexcept {
    this->value = other.value;
    this->symbol = other.symbol;

    other.value = Ace;
    other.symbol = Hearts;
}
/*
 * = operator constructor
 */
Card &Card::operator=(Card &&other) noexcept {
    if (this != &other) {
        this->value = other.value;
        this->symbol = other.symbol;

        other.value = Ace;
        other.symbol = Hearts;
    }
    return *this;
}

/**
 * Compares 2 cards and decide the winner
 *  Ace wins against everything but Two
 *  using the winState enum
 * @param p2Card the other player's card
 * @return return who won this round using winState enum.
 */
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
/**
 * change the int value of a card into a string
 * @return string representation of the value
 */
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

/**
 * change the enum symbol into a string
 * @return  string representation of the symbol
 */
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












