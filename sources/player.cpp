#include "player.hpp"

#include <utility>
#include "string"
#include "vector"

using namespace ariel;
using namespace std;

Player::Player(std::string playerName) :
        playerName(std::move(playerName)), isPlaying(false),
        winRate(0), deckSize(0), cardsTaken(0), numberOfWins(0) {}

Player::Player() : playerName("DefaultName"), isPlaying(false),
                   winRate(0), deckSize(0), cardsTaken(0), numberOfWins(0) {
}

std::ostream &ariel::operator<<(std::ostream &os, const Player &player) {
    os << "playerName: " << player.playerName << " topCard: " << player.topCard
       << " cardsTaken: " << player.cardsTaken << " deckSize: " << player.deckSize << " numberOfWins: "
       << player.numberOfWins << " winRate: " << player.winRate << " isPlaying: " << player.isPlaying;
    return os;
}

bool Player::operator==(const Player &rhs) const {
    return playerName == rhs.playerName &&
           deck == rhs.deck &&
           topCard == rhs.topCard &&
           cardsTaken == rhs.cardsTaken &&
           deckSize == rhs.deckSize &&
           numberOfWins == rhs.numberOfWins &&
           winRate == rhs.winRate &&
           isPlaying == rhs.isPlaying;
}

bool Player::operator!=(const Player &rhs) const {
    return !(rhs == *this);
}

Player::~Player() = default;


const std::string &Player::getPlayerName() const {
    return playerName;
}

void Player::setPlayerName(const std::string &newPlayerName) {
    Player::playerName = newPlayerName;
}

const std::vector<ariel::Card> &Player::getDeck() const {
    return deck;
}

void Player::setDeck(const std::vector<Card> &newDeck) {
    for (const auto &i: newDeck)
        this->deck.push_back(i);
}

const Card &Player::getTopCard() const {
    return deck.front();
}

void Player::setTopCard(const Card &playerTopCard) {
    Player::topCard = playerTopCard;
}

int Player::getCardsTaken() const {
    return cardsTaken;
}

void Player::setCardsTaken(int playerCardsTaken) {
    Player::cardsTaken = playerCardsTaken;
}

unsigned long Player::getDeckSize() const {
    return this->deck.size();
}

int Player::getNumberOfWins() const {
    return numberOfWins;
}

void Player::setNumberOfWins(int playerNumberOfWins) {
    Player::numberOfWins = playerNumberOfWins;
}

double Player::getWinRate() const {
    return winRate;
}

void Player::setWinRate(double playerWinRate) {
    Player::winRate = playerWinRate;
}

bool Player::getIsPlaying() const {
    return isPlaying;
}

void Player::setIsPlaying(bool playerIsPlaying) {
    Player::isPlaying = playerIsPlaying;
}







