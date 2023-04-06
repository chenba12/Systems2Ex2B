#include "player.hpp"

#include <utility>

#include "string"
#include "vector"


using namespace ariel;
using namespace std;


Player::Player(std::string playerName) :
        playerName(std::move(playerName)), isPlaying(false),
        winRate(0), cardsTaken(0), numberOfWins(0), drawRate(0), numberOfDraws(0), id(Player::getNextID()) {}

Player::Player() : playerName("DefaultName"), isPlaying(false),
                   winRate(0), cardsTaken(0), numberOfWins(0), drawRate(0), numberOfDraws(0), id(Player::getNextID()) {
}

std::ostream &ariel::operator<<(std::ostream &ostream, const Player &player) {
    ostream << "playerName: " << player.playerName
            << " cardsTaken: " << player.cardsTaken << " numberOfWins: "
            << player.numberOfWins << " winRate: %" << player.winRate << " drawRate: %" << player.drawRate
            << " amountOfDraws: " << player.numberOfDraws << " isPlaying: " << player.isPlaying;
    return ostream;
}

bool Player::operator==(const Player &rhs) const {
    return playerName == rhs.playerName &&
           deck == rhs.deck &&
           cardsTaken == rhs.cardsTaken &&
           numberOfWins == rhs.numberOfWins &&
           winRate == rhs.winRate &&
           isPlaying == rhs.isPlaying;
}

bool Player::operator!=(const Player &rhs) const {
    return !(rhs == *this);
}


const std::string &Player::getPlayerName() const {
    return playerName;
}

const std::vector<ariel::Card> &Player::getDeck() const {
    return deck;
}

void Player::setDeck(const std::vector<Card> &newDeck) {
    for (const Card &i: newDeck)
        this->deck.push_back(i);
}

int Player::cardesTaken() const {
    return cardsTaken;
}

void Player::setCardsTaken(int playerCardsTaken) {
    Player::cardsTaken += playerCardsTaken;
}

int Player::stacksize() const {
    return (int) this->deck.size();
}

int Player::getNumberOfWins() const {
    return numberOfWins;
}

void Player::incrementNumberOfWins(int playerNumberOfWins) {
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
    this->isPlaying = playerIsPlaying;
}


int Player::getNumberOfDraws() const {
    return numberOfDraws;
}

void Player::incrementNumberOfDraws(int newNumberOfDraws) {
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

int Player::getID() const {
    return this->id;
}

int Player::getNextID() {
    static int id = 1;
    return id++;
}









