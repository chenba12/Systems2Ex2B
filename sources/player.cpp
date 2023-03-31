#include "player.hpp"

#include <utility>

#include "string"
#include "vector"


using namespace ariel;
using namespace std;

Player::Player(std::string playerName) :
        playerName(std::move(playerName)), isPlaying(false),
        winRate(0), cardsTaken(0), numberOfWins(0), drawRate(0), numberOfDraws(0) {}

Player::Player() : playerName("DefaultName"), isPlaying(false),
                   winRate(0), cardsTaken(0), numberOfWins(0), drawRate(0), numberOfDraws(0) {
}

std::ostream &ariel::operator<<(std::ostream &os, const Player &player) {
    os << "playerName: " << player.playerName
       << " cardsTaken: " << player.cardsTaken << " numberOfWins: "
       << player.numberOfWins << " winRate: %" << player.winRate << " drawRate: %" << player.drawRate
       << " amountOfDraws: " << player.numberOfDraws << " isPlaying: " << player.isPlaying;
    return os;
}

bool Player::operator==(const Player &rhs) const {
    return playerName == rhs.playerName &&
           deck == rhs.deck &&
           topCard == rhs.topCard &&
           cardsTaken == rhs.cardsTaken &&
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

int Player::getCardsTaken() const {
    return cardsTaken;
}

void Player::setCardsTaken(int playerCardsTaken) {
    Player::cardsTaken += playerCardsTaken;
}

unsigned long Player::getDeckSize() const {
    return this->deck.size();
}

int Player::getNumberOfWins() const {
    return numberOfWins;
}

void Player::setNumberOfWins(int playerNumberOfWins) {
    Player::numberOfWins += playerNumberOfWins;
}

double Player::getWinRate() const {
    return winRate;
}

void Player::setWinRate(int turnsPlayed) {
    if (numberOfWins == 0 || turnsPlayed == 0) {
        Player::winRate = 0;
        return;
    }
    double newWinRate = (double) numberOfWins / (double) turnsPlayed * 100.0;
    Player::winRate = newWinRate;
}


bool Player::getIsPlaying() const {
    return isPlaying;
}

void Player::setIsPlaying(bool playerIsPlaying) {
    Player::isPlaying = playerIsPlaying;
}


int Player::getNumberOfDraws() const {
    return numberOfDraws;
}

void Player::setNumberOfDraws(int newNumberOfDraws) {
    Player::numberOfDraws += newNumberOfDraws;
}

double Player::getDrawRate() const {
    return drawRate;
}

void Player::setDrawRate(int turnsPlayed) {
    if (numberOfDraws == 0 || turnsPlayed == 0) {
        Player::drawRate = 0;
        return;
    }
    double newDrawRate = (double) numberOfDraws / (double) turnsPlayed * 100.0;
    Player::drawRate = newDrawRate;
}


Card &Player::removeAndGetTopCard() {
    Card &removedCard = deck.at(0);
    if (!deck.empty()) {
        deck.erase(deck.begin());
    }
    return removedCard;
}








