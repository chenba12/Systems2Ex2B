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
    if (player1.getIsPlaying() || player2.getIsPlaying()) {
        throw std::invalid_argument("Player already in another game");
    }
    generateDeck();
    shuffleDeck(this->gameDeck);
    std::vector<Card> player1Deck(gameDeck.begin(), gameDeck.begin() + 26);
    std::vector<Card> player2Deck(gameDeck.begin() + 26, gameDeck.end());
    this->player1.setDeck(player1Deck);
    this->player2.setDeck(player2Deck);
    this->player1.setIsPlaying(true);
    this->player2.setIsPlaying(true);
}

std::ostream &ariel::operator<<(std::ostream &os, const Game &game) {
    os << "player1: " << game.player1 << " player2: " << game.player2
       << " numberOfTurns: " << game.numberOfTurns << " isPlaying: " << game.isPlaying << " winner: " << game.winner
       << " numberOfDraws: " << game.numberOfDraws;
    return os;
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

Game::~Game() = default;


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
    Game::numberOfTurns = newNumberOfTurns;
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


int Game::getNumberOfDraws() const {
    return numberOfDraws;
}

void Game::setNumberOfDraws(int newNumberOfDraws) {
    Game::numberOfDraws = newNumberOfDraws;
}

void Game::generateDeck() {
    std::vector<Card> deck;
    for (int i = 1; i <= 13; i++) {
        for (int j = 1; j <= 4; j++) {
            auto symbol = static_cast<cardSymbols>(j);
            Card card(cardValues(i), symbol);
            deck.push_back(card);
        }
    }
    std::cout << "Generated deck: " << std::endl;
    for (const auto &card: deck) {
        std::cout << card << std::endl;
    }
    this->setGameDeck(deck);
}

void Game::shuffleDeck(std::vector<Card> &deck) {
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(deck.begin(), deck.end(), g);

    std::cout << "Shuffled deck: " << std::endl;
    for (const auto &card: deck) {
        std::cout << card << std::endl;
    }
}

const std::vector<Card> &Game::getGameDeck() const {
    return gameDeck;
}

void Game::setGameDeck(const std::vector<Card> &newGameDeck) {
    Game::gameDeck = newGameDeck;
}

void Game::playTurn() {

}

void Game::playAll() {

}

void Game::printWinner() {
    std::cout << winner << std::endl;
    if (winner == Tie) std::cout << "The game ended in a Tie " << std::endl;
    else if (winner == P1Win) std::cout << player1.getPlayerName() << std::endl;
    else if (winner == P2Win) std::cout << player2.getPlayerName() << std::endl;
    else if (winner == NoWinner) throw std::invalid_argument("Got has not ended...");
}

void Game::logTurn(const Card &p1CardPlayed, const Card &p2CardPlayed, const std::string &player1Name, const std::string &player2Name,
                   const  std::string &winnerString) {
//    int turnWInner = p1CardPlayed.checkWinner(p2CardPlayed);
//    std::string winner = "";
//    switch (turnWInner) {
//        case P1Win:
//            winner = player1Name + " wins.";
//            break;
//        case P2Win:
//            winner = player2Name + " wins.";
//            break;
//        case Tie:
//            winner = "Draw.";
//            break;
    std::ostringstream ossP1;
    ossP1 << p1CardPlayed;
    std::string p1CardPlayedStr = ossP1.str();
    std::ostringstream ossP2;
    ossP2 << p2CardPlayed;
    std::string p2CardPlayedStr = ossP2.str();
    std::string log =
            player1Name + " played " + p1CardPlayedStr + " " + player2Name + " played " + p2CardPlayedStr + "." +
            winnerString;
    turnsLog.push_back(log);
    // Alice played Queen of Hearts Bob played 5 of Spades. Alice wins.
//    // Alice played 6 of Hearts Bob played 6 of Spades. Draw.
//    Alice played 10 of Clubs Bob played 10 of Diamonds. draw.
//    Alice played Jack of Clubs Bob played King of Diamonds. Bob wins.
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

void Game::printStats() {

}

std::vector<std::string> Game::getTurnsLog() {
    return turnsLog;
}




