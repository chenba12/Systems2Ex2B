#include "game.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <sstream>

using namespace ariel;

Game::Game(Player &player1, Player &player2) : player1(player1),
                                               player2(player2), winner(-1), isPlaying(true), numberOfTurns(0),
                                               numberOfDraws(0) {
    startGame();
}

void Game::startGame() {
    generateDeck();
    shuffleDeck(gameDeck);
    std::vector<Card> player1Deck(gameDeck.begin(), gameDeck.begin() + 26);
    std::vector<Card> player2Deck(gameDeck.begin() + 26, gameDeck.end());
    player1.setDeck(player1Deck);
    player2.setDeck(player2Deck);
    if (player1.getIsPlaying() || player2.getIsPlaying()) {
        throw std::logic_error("Players are already playing another game.");
    }
    player1.setIsPlaying(true);
    player2.setIsPlaying(true);
}

std::ostream &ariel::operator<<(std::ostream &ostream, const Game &game) {
    ostream << "player1: " << game.player1 << " player2: " << game.player2
            << " numberOfTurns: " << game.numberOfTurns << " isPlaying: " << game.isPlaying << " winner: "
            << game.winner
            << " numberOfDraws: " << game.numberOfDraws;
    return ostream;
}

bool Game::operator==(const Game &rhs) const {
    return player1 == rhs.player1 &&
           player2 == rhs.player2 &&
           turnsLog == rhs.turnsLog &&
           numberOfTurns == rhs.numberOfTurns &&
           isPlaying == rhs.isPlaying &&
           winner == rhs.winner &&
           numberOfDraws == rhs.numberOfDraws;
}

bool Game::operator!=(const Game &rhs) const {
    return !(rhs == *this);
}


Player &Game::getPlayer1() const {
    return player1;
}

Player &Game::getPlayer2() const {
    return player2;
}

int Game::getNumberOfTurns() const {
    return numberOfTurns;
}

void Game::setNumberOfTurns(int newNumberOfTurns) {
    Game::numberOfTurns += newNumberOfTurns;
}

bool Game::isPlaying1() const {
    return isPlaying;
}

void Game::setIsPlaying(bool newIsPlaying) {
    Game::isPlaying = newIsPlaying;
}

int Game::getWinner() const {
    return winner;
}

void Game::setWinner(int newWinner) {
    Game::winner = newWinner;
}


void Game::setNumberOfDraws(int newNumberOfDraws) {
    Game::numberOfDraws += newNumberOfDraws;
}

void Game::generateDeck() {
    std::vector<Card> deck;
    for (int i = 1; i <= 13; i++) {
        for (int j = 1; j <= 4; j++) {
            Card card((cardValues(i)), cardSymbols(j));
            deck.push_back(card);
        }
    }
    this->setGameDeck(deck);
}

void Game::shuffleDeck(std::vector<Card> &deck) {
    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(deck.begin(), deck.end(), generator);
}

const std::vector<Card> &Game::getGameDeck() const {
    return gameDeck;
}

void Game::setGameDeck(const std::vector<Card> &newGameDeck) {
    Game::gameDeck = newGameDeck;
}

void Game::playTurn() {
    std::string turnLog;
    if (!isPlaying) {
        throw std::invalid_argument("The game has ended");
    }
    if (player1.getID() == player2.getID()) {
        throw std::logic_error("A player can't play with himself.");
    }
    bool sizeFLag;
    bool played = false;
    Card p1Card = player1.removeAndGetTopCard();
    Card p2Card = player2.removeAndGetTopCard();
    std::vector<Card> p1ThrownCards;
    p1ThrownCards.push_back(p1Card);
    std::vector<Card> p2ThrownCards;
    p2ThrownCards.push_back(p2Card);
    int turnWinner = p1Card.checkWinner(p2Card);
    this->setNumberOfTurns(1);
    while (true) {
        if (player1.stacksize() <= 1 || player2.stacksize() <= 1) {
            sizeFLag = true;
        } else sizeFLag = false;
        switch (turnWinner) {
            case P1Win:
                //p1 won
                player1.setCardsTaken((int) (p1ThrownCards.size() + p2ThrownCards.size()));
                player1.setNumberOfWins(1);
                player1.setWinRate(numberOfTurns);
                player2.setWinRate(numberOfTurns);
                player1.setDrawRate(numberOfTurns);
                player2.setDrawRate(numberOfTurns);
                turnLog += logTurn(p1Card, p2Card, player1.getPlayerName(),
                                   player2.getPlayerName(), player1.getPlayerName() + " Wins. ");
                turnsLog.push_back(turnLog);
                turnLog = "";
                break;
            case P2Win:
                //p2 won
                player2.setCardsTaken((int) (p1ThrownCards.size() + p2ThrownCards.size()));
                player2.setNumberOfWins(1);
                player1.setWinRate(numberOfTurns);
                player2.setWinRate(numberOfTurns);
                player1.setDrawRate(numberOfTurns);
                player2.setDrawRate(numberOfTurns);
                turnLog += logTurn(p1Card, p2Card, player1.getPlayerName(),
                                   player2.getPlayerName(), player2.getPlayerName() + " Wins.");
                turnsLog.push_back(turnLog);
                turnLog = "";
                break;
            case Tie:
                //Tie
                if (sizeFLag && (!played)) {
                    if (player1.stacksize() == 0 || player2.stacksize() == 0) {
                        player1.setCardsTaken(1);
                        player2.setCardsTaken(1);
                    } else {
                        player1.setCardsTaken(2);
                        player2.setCardsTaken(2);
                    }
                    endGame();
                    return;
                }
                player1.setNumberOfDraws(1);
                player2.setNumberOfDraws(1);
                player1.setDrawRate(numberOfTurns);
                player2.setDrawRate(numberOfTurns);
                setNumberOfDraws(1);
                turnLog += logTurn(p1Card, p2Card, player1.getPlayerName(), player2.getPlayerName(), "Draw. ");
                if (sizeFLag) {
                    std::vector<Card> p1NewDeck;
                    p1NewDeck.insert(p1NewDeck.end(), player1.getDeck().begin(), player1.getDeck().end());
                    p1NewDeck.insert(p1NewDeck.end(), p1ThrownCards.begin(), p1ThrownCards.end());
                    std::vector<Card> p2NewDeck;
                    p2NewDeck.insert(p2NewDeck.end(), player2.getDeck().begin(), player2.getDeck().end());
                    p2NewDeck.insert(p2NewDeck.end(), p2ThrownCards.begin(), p2ThrownCards.end());
                    player1.setDeck(p1NewDeck);
                    std::vector<Card> gameDeck1 = player1.getDeck();
                    shuffleDeck(gameDeck1);
                    player2.setDeck(p2NewDeck);
                    std::vector<Card> gameDeck2 = player2.getDeck();
                    shuffleDeck(gameDeck2);
                    p1ThrownCards.clear();
                    p2ThrownCards.clear();
                    p1Card = player1.removeAndGetTopCard();
                    p1ThrownCards.push_back(p1Card);
                    p2Card = player2.removeAndGetTopCard();
                    p2ThrownCards.push_back(p2Card);
                    turnWinner = p1Card.checkWinner(p2Card);
                    break;
                }
                p1Card = player1.removeAndGetTopCard();
                p1ThrownCards.push_back(p1Card);
                p2Card = player2.removeAndGetTopCard();
                p2ThrownCards.push_back(p2Card);
                p1Card = player1.removeAndGetTopCard();
                p2Card = player2.removeAndGetTopCard();
                p1ThrownCards.push_back(p1Card);
                p2ThrownCards.push_back(p2Card);
                break;
            default:
                break;
        }
        if (turnWinner != Tie) {
            if (player1.stacksize() == 0 || player2.stacksize() == 0) {
                endGame();
            }
            break;
        }
        turnWinner = p1Card.checkWinner(p2Card);
        played = true;
    }
}

void Game::endGame() {
    if (player1.cardesTaken() > player2.cardesTaken()) {
        setWinner(P1Win);
    } else if (player1.cardesTaken() < player2.cardesTaken()) {
        setWinner(P2Win);
    } else {
        setWinner(Tie);
    }
    player1.setIsPlaying(false);
    player2.setIsPlaying(false);
    setIsPlaying(false);
}

void Game::playAll() {
    while (winner == -1) {
        playTurn();
    }
}

void Game::printWiner() {
    if (winner == Tie) throw std::invalid_argument("Game ended in a tie");
    else if (winner == P1Win) std::cout << player1.getPlayerName() << std::endl;
    else if (winner == P2Win) std::cout << player2.getPlayerName() << std::endl;
    else if (winner == NoWinner) std::cout << "Got has not ended..." << std::endl;
}

std::string Game::logTurn(const Card &p1CardPlayed, const Card &p2CardPlayed, const std::string &player1Name,
                          const std::string &player2Name,
                          const std::string &winnerString) {
    std::ostringstream ossP1;
    ossP1 << p1CardPlayed;
    std::string p1CardPlayedStr = ossP1.str();
    std::ostringstream ossP2;
    ossP2 << p2CardPlayed;
    std::string p2CardPlayedStr = ossP2.str();
    std::string log =
            player1Name + " played " + p1CardPlayedStr + " " + player2Name + " played " + p2CardPlayedStr + ". " +
            winnerString;
    return log;
}

void Game::printLastTurn() {
    std::cout << turnsLog.back() << std::endl;
}

void Game::printLog() {
    std::cout << "----------Printing Logs----------" << std::endl;
    for (const auto &turn: turnsLog) {
        std::cout << turn << std::endl;
    }
}

void Game::printStats() const {
    std::cout << this->getPlayer1() << std::endl;
    std::cout << this->getPlayer2() << std::endl;
}

std::vector<std::string> Game::getTurnsLog() {
    return turnsLog;
}




