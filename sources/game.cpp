#include "game.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace ariel;


Game::Game(Player &player1, Player &player2) : player1(player1),
                                               player2(player2), winner(0), isPlaying(true), numberOfTurns(0),
                                               numberOfDraws(0) {
    generateDeck();
    shuffleDeck(this->gameDeck);
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

void Game::setPlayer1(Player &player1) {
    Game::player1 = player1;
}

Player &Game::getPlayer2() const {
    return player2;
}

void Game::setPlayer2(Player &player2) {
    Game::player2 = player2;
}

void Game::setTurnsLog(const std::vector<std::string> &turnsLog) {
    Game::turnsLog = turnsLog;
}

int Game::getNumberOfTurns() const {
    return numberOfTurns;
}

void Game::setNumberOfTurns(int numberOfTurns) {
    Game::numberOfTurns = numberOfTurns;
}

bool Game::isPlaying1() const {
    return isPlaying;
}

void Game::setIsPlaying(bool isPlaying) {
    Game::isPlaying = isPlaying;
}

int Game::getWinner() const {
    return winner;
}

void Game::setWinner(int winner) {
    Game::winner = winner;
}


int Game::getNumberOfDraws() const {
    return numberOfDraws;
}

void Game::setNumberOfDraws(int numberOfDraws) {
    Game::numberOfDraws = numberOfDraws;
}

void Game::generateDeck() {
    std::vector<Card> deck;
    for (int i = 1; i <= 13; i++) {
        for (int j = 1; j <= 4; j++) {
            cardSymbols symbol = static_cast<cardSymbols>(j);
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

void Game::setGameDeck(const std::vector<Card> &gameDeck) {
    Game::gameDeck = gameDeck;
}

void Game::playTurn() {

}

void Game::printLastTurn() {

}

void Game::playAll() {

}

void Game::printWiner() {

}

void Game::printLog() {

}

void Game::printStats() {

}

std::vector<std::string> Game::getTurnsLog() {
    return std::vector<std::string>();
}




