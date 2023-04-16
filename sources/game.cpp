#include "game.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace ariel;

/**
 * normal constructor that init a new game
 */
Game::Game(Player &player1, Player &player2) : player1(player1),
                                               player2(player2), isPlaying(true), numberOfTurns(0),
                                               numberOfDraws(0) {
    if (!player1.getIsPlaying()) {
        player1.resetStats();
    }
    if (!player2.getIsPlaying()) {
        player2.resetStats();
    }
    if (!player1.getIsPlaying() && !player2.getIsPlaying()) {
        startGame();
    }
}

/**
 * Init a new game
 * setup a deck of 52 cards and shuffle it and then deal each player a deck of 26 cards
 *
 */
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
}

/**
 *  overwrite the << operator to return a string representation of the game
 */
std::ostream &ariel::operator<<(std::ostream &ostream, const Game &game) {
    ostream << "player1: " << game.player1 << " player2: " << game.player2
            << " numberOfTurns: " << game.numberOfTurns << " isPlaying: " << game.isPlaying << " winner: "
            << game.logger.toString()
            << " numberOfDraws: " << game.numberOfDraws;
    return ostream;
}

/**
 * check if 2 games are the same based on their data fields
 * @param otherGame the other game
 * @return true if equal false otherwise
 */
bool Game::operator==(const Game &otherGame) const {
    return player1 == otherGame.player1 &&
           player2 == otherGame.player2 &&
           numberOfTurns == otherGame.numberOfTurns &&
           isPlaying == otherGame.isPlaying &&
           numberOfDraws == otherGame.numberOfDraws;
}

bool Game::operator!=(const Game &otherGame) const {
    return !(otherGame == *this);
}

/**
 * getter and setters
 */

void Game::setNumberOfTurns(int newNumberOfTurns) {
    Game::numberOfTurns += newNumberOfTurns;
}

void Game::setGameDeck(const std::vector<Card> &newGameDeck) {
    Game::gameDeck = newGameDeck;
}

/**
 * generate a starting game deck of 52 cards
 * 4 of each card values 1-13
 */
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

/**
 * Shuffle a given deck using a built in algorithm in c++
 * @param deck reference you want to shuffle
 */
void Game::shuffleDeck(std::vector<Card> &deck) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(deck.begin(), deck.end(), generator);
}

/**
 * play a turn
 * remove the top card from both decks and compare them
 * save the log of that turn
 * if there is a tie between the 2 cards the turn will continue until there is a winner
 * if there is a tie the 2 players will put 1 card on the "back" and one faced up
 * that will be compared against the other player's card
 * that will happen as long as both players have enough cards to play the "war"
 */
void Game::playTurn() {
    if (player1.getID() == player2.getID() || &player1 == &player2) {
        throw std::logic_error("A player can't play with himself.");
    }
    if (!isPlaying) {
        throw std::invalid_argument("The game has ended");
    }
    if (numberOfTurns == 0 && (player1.getIsPlaying() || player2.getIsPlaying())) {
        throw std::logic_error("Player already registered to another game");
    } else {
        player1.setIsPlaying(true);
        player2.setIsPlaying(true);
    }
    std::string turnLog;
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
                //p1 won updates the winRate,Cards Taken and add the log
                P1WinTurn(p1ThrownCards, p2ThrownCards, p1Card, p2Card, turnLog);
                break;
            case P2Win:
                //p2 won updates the winRate,Cards Taken and add the log
                P2WinTurn(p1ThrownCards, p2ThrownCards, p1Card, p2Card, turnLog);
                break;
            case Tie:
                //Tie
                if (sizeFLag && (!played)) {
                    //tie with not enough cards to play war
                    // add the hand+thrown card size to cardsTaken and finish the game
                    if (player1.stacksize() == 0 || player2.stacksize() == 0) {
                        player1.setCardsTaken(1);
                        player2.setCardsTaken(1);
                    } else {
                        player1.setCardsTaken(2);
                        player2.setCardsTaken(2);
                        player1.removeAndGetTopCard();
                        player2.removeAndGetTopCard();
                    }
                    endGame();
                    return;
                }
                player1.incrementNumberOfDraws();
                player2.incrementNumberOfDraws();
                player1.setDrawRate(numberOfTurns);
                player2.setDrawRate(numberOfTurns);
                numberOfDraws++;
                turnLog += logger.logTurn(p1Card, p2Card, player1.getPlayerName(), player2.getPlayerName(), "Draw. ");
                if (sizeFLag) {
                    //Not enough cards to play war but there have been wars previously
                    // shuffle the cards thrown with the cards in hand and restart the turn
                    std::vector<Card> p1NewDeck;
                    p1NewDeck.insert(p1NewDeck.end(), player1.getDeck().begin(), player1.getDeck().end());
                    p1NewDeck.insert(p1NewDeck.end(), p1ThrownCards.begin(), p1ThrownCards.end());
                    std::vector<Card> p2NewDeck;
                    p2NewDeck.insert(p2NewDeck.end(), player2.getDeck().begin(), player2.getDeck().end());
                    p2NewDeck.insert(p2NewDeck.end(), p2ThrownCards.begin(), p2ThrownCards.end());
                    player1.setDeck(p1NewDeck);
                    shuffleDeck(p1NewDeck);
                    player2.setDeck(p2NewDeck);
                    shuffleDeck(p2NewDeck);
                    p1ThrownCards.clear();
                    p2ThrownCards.clear();
                    p1Card = player1.removeAndGetTopCard();
                    p1ThrownCards.push_back(p1Card);
                    p2Card = player2.removeAndGetTopCard();
                    p2ThrownCards.push_back(p2Card);
                    turnWinner = p1Card.checkWinner(p2Card);
                    break;
                }
                //tie play throw each player throw 2 cards
                p1ThrownCards.push_back(player1.removeAndGetTopCard());
                p2ThrownCards.push_back(player2.removeAndGetTopCard());
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

void Game::P1WinTurn(const std::vector<Card> &p1ThrownCards, const std::vector<Card> &p2ThrownCards, const Card &p1Card,
                     const Card &p2Card,
                     std::string &turnLog) {
    player1.setCardsTaken((int) (p1ThrownCards.size() + p2ThrownCards.size()));
    player1.incrementNumberOfWins();
    player1.setWinRate(numberOfTurns);
    player2.setWinRate(numberOfTurns);
    player1.setDrawRate(numberOfTurns);
    player2.setDrawRate(numberOfTurns);
    turnLog += logger.logTurn(p1Card, p2Card, player1.getPlayerName(),
                              player2.getPlayerName(), player1.getPlayerName() + " Wins. ");
    logger.addTurn(turnLog);
    turnLog = "";
}

void Game::P2WinTurn(const std::vector<Card> &p1ThrownCards, const std::vector<Card> &p2ThrownCards, const Card &p1Card,
                     const Card &p2Card, std::string &turnLog) {
    player2.setCardsTaken((int) (p1ThrownCards.size() + p2ThrownCards.size()));
    player2.incrementNumberOfWins();
    player1.setWinRate(numberOfTurns);
    player2.setWinRate(numberOfTurns);
    player1.setDrawRate(numberOfTurns);
    player2.setDrawRate(numberOfTurns);
    turnLog += logger.logTurn(p1Card, p2Card, player1.getPlayerName(),
                              player2.getPlayerName(), player2.getPlayerName() + " Wins.");
    logger.addTurn(turnLog);
    turnLog = "";
}

/**
 * set the winner of the game and finish it
 * after this method is called you can't call playAll() or playTurn() any more
 */
void Game::endGame() {
    if (player1.cardesTaken() > player2.cardesTaken()) {
        logger.setGameWinner(P1Win, player1, player2);
    } else if (player1.cardesTaken() < player2.cardesTaken()) {
        logger.setGameWinner(P2Win, player1, player2);
    } else {
        logger.setGameWinner(Tie, player1, player2);
    }
    player1.clearDeck();
    player2.clearDeck();
    player1.setIsPlaying(false);
    player2.setIsPlaying(false);
    isPlaying = false;
}

/**
 * Play the game until there is a winner
 */
void Game::playAll() {
    if (logger.getGameWinner() != NoWinner) throw std::logic_error("game has ended");
    while (logger.getGameWinner() == NoWinner) {
        playTurn();
    }
}

/**
 * Calling the logger function printWiner()
 */
void Game::printWiner() const {
    logger.printWiner(player1, player2);
}

/**
 * Calling the logger function printLastTurn()
 */
void Game::printLastTurn() const {
    logger.printLastTurn();
}

/**
 * Calling the logger function printLog()
 */
void Game::printLog() const {
    logger.printLog();
}

/**
 * Calling the logger function printStats() with player 1 and player2
 */
void Game::printStats() {
    logger.printStats(player1, player2);
}



