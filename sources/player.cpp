#include "player.hpp"

#include <utility>

#include "string"
#include "vector"


using namespace ariel;
using namespace std;

/**
 * normal constructor
 */
Player::Player(std::string playerName) :
        playerName(std::move(playerName)), isPlaying(false),
        winRate(0), cardsTaken(0), numberOfWins(0), drawRate(0), numberOfDraws(0), id(Player::getNextID()) {}

/**
* empty constructor
*/
Player::Player() : playerName("DefaultName"), isPlaying(false),
                   winRate(0), cardsTaken(0), numberOfWins(0), drawRate(0), numberOfDraws(0), id(Player::getNextID()) {
}

/**
 *  overwrite the << operator to return a string representation of the player
 */
std::ostream &ariel::operator<<(std::ostream &ostream, const Player &player) {
    ostream << "playerName: " << player.playerName
            << " cardsTaken: " << player.cardsTaken << " numberOfWins: "
            << player.numberOfWins << " winRate: %" << player.winRate << " drawRate: %" << player.drawRate
            << " amountOfDraws: " << player.numberOfDraws << " isPlaying: " << player.isPlaying;
    return ostream;
}

/**
 * check if 2 players are the same based on their data fields
 * @param other the other player
 * @return true if equal false otherwise
 */
bool Player::operator==(const Player &other) const {
    return playerName == other.playerName &&
           deck == other.deck &&
           cardsTaken == other.cardsTaken &&
           numberOfWins == other.numberOfWins &&
           winRate == other.winRate &&
           isPlaying == other.isPlaying;
}

/**
 * check if 2 players are not the same
 * @param other player
 * @return true/false
 */
bool Player::operator!=(const Player &other) const {
    return !(other == *this);
}

/**
 * getters and setters
 */

/**
 * @return the player's name
 */
const std::string &Player::getPlayerName() const {
    return playerName;
}

/**
 * @return the player's deck
 */
const std::vector<ariel::Card> &Player::getDeck() const {
    return deck;
}
/**
 * set a new deck for the player
 * @param newDeck
 */
void Player::setDeck(const std::vector<Card> &newDeck) {
    Player::deck = newDeck;
}
/**
 * @return the amount of cards the player won this game
 */
int Player::cardesTaken() const {
    return cardsTaken;
}

/**
 * increase the amount of cards the player won this game
 * @param playerCardsTaken
 */
void Player::setCardsTaken(int playerCardsTaken) {
    Player::cardsTaken += playerCardsTaken;
}
/**
 * @return return the deck.size()
 */
int Player::stacksize() const {
    return (int) this->deck.size();
}

/**
 * @return the number of wins the player had in the game
 */
int Player::getNumberOfWins() const {
    return numberOfWins;
}

/**
 * increment the number of wins by 1
 */
void Player::incrementNumberOfWins() {
    Player::numberOfWins++;
}

/**
 * @return the win rate
 */
double Player::getWinRate() const {
    return winRate;
}

/**
 * Calculate the win rate according to the amount of turns played in the game
 * @param turnsPlayed in the game
 */
void Player::setWinRate(int turnsPlayed) {
    if (numberOfWins == 0 || turnsPlayed == 0) {
        Player::winRate = 0;
        return;
    }
    Player::winRate =  (double) numberOfWins / (double) turnsPlayed * 100.0;
}

/**
 * @return if the player is playing a game or not
 */
bool Player::getIsPlaying() const {
    return isPlaying;
}

/**
 * set if the player is playing a game or not
 * @param playerIsPlaying
 */
void Player::setIsPlaying(bool playerIsPlaying) {
    this->isPlaying = playerIsPlaying;
}

/**
 * @return the number of draws that happened in the game
 */
int Player::getNumberOfDraws() const {
    return numberOfDraws;
}
/**
 * increment the number of draws by 1
 */
void Player::incrementNumberOfDraws() {
    Player::numberOfDraws++;
}

/**
 * @return the draw rate
 */
double Player::getDrawRate() const {
    return drawRate;
}

/**
 * Calculate the draw rate according to the amount of turns played in the game
 * @param turnsPlayed in the game
 */
void Player::setDrawRate(int turnsPlayed) {
    if (numberOfDraws == 0 || turnsPlayed == 0) {
        Player::drawRate = 0;
        return;
    }
    Player::drawRate = (double) numberOfDraws / (double) turnsPlayed * 100.0;
}

/**
 * @return the player's ID
 */
int Player::getID() const {
    return this->id;
}

/**
 * increment the id
 * @return id
 */
int Player::getNextID() {
    static int id = 1;
    return id++;
}

/**
 * return and removed a card from your deck in order to play it
 * @return the card at the top of the deck
 */
Card &Player::removeAndGetTopCard() {
    Card &removedCard = deck.at(0);
    if (!deck.empty()) {
        deck.erase(deck.begin());
    }
    return removedCard;
}

/**
 * clears the player deck
 */
void Player::clearDeck() {
    deck.clear();
}

/**
 * reset all the player stats to default
 * used when a player register to another game after they finished playing a game
 */
void Player::resetStats() {
    deck.clear();
    cardsTaken = 0;
    numberOfWins = 0;
    winRate = 0;
    numberOfDraws = 0;
    drawRate = 0;
}
