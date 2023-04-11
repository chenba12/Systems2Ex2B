//
// Created by chen on 4/11/23.
//


#include "logger.hpp"
#include <sstream>

using namespace ariel;

/**
 * print the player's statistics like win rate cards taken win rate and so on...
 */
void Logger::printStats(const Player &player1, const Player &player2) {
    if (gameWinner != NoWinner) {
        std::cout << "---------Game Stats---------" << std::endl;
        std::cout << player1Stats << std::endl;
        std::cout << player2Stats << std::endl;
        std::cout << "------------Done------------" << std::endl;
    } else {
        std::cout << "---------Game Stats---------" << std::endl;
        std::cout << player1 << std::endl;
        std::cout << player2 << std::endl;
        std::cout << "------------Done------------" << std::endl;
    }

}

/**
 * print the full logs of the game
 */
void Logger::printLog() const {
    std::cout << "----------Printing Logs----------" << std::endl;
    for (const auto &turn: turnsLog) {
        std::cout << turn << std::endl;
    }
    std::cout << "--------------Done-------------" << std::endl;
}

/**
 * print the last turn
 */
void Logger::printLastTurn() const {
    std::cout << turnsLog.back() << std::endl;
}

/**
 * Build a string log of the turn and return it
 * @param p1CardPlayed the card that player1 played this turn
 * @param p2CardPlayed the card that player2 played this turn
 * @param player1Name  the name of player 1
 * @param player2Name the name of player 1
 * @param winnerString a string that says who won this turn
 * @return a string that represent what happened this turn
 */
std::string Logger::logTurn(const Card &p1CardPlayed, const Card &p2CardPlayed, const std::string &player1Name,
                            const std::string &player2Name,
                            const std::string &winnerString) const {
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

/**
 * Print the winner of the game
 * using the winState enum
 */
void Logger::printWiner(const Player &player1, const Player &player2) const {
    if (gameWinner == Tie) std::cout << "Game ended in a tie" << std::endl;
    else if (gameWinner == P1Win) std::cout << "Winner:" << player1.getPlayerName() << std::endl;
    else if (gameWinner == P2Win) std::cout << "Winner:" << player2.getPlayerName() << std::endl;
    else if (gameWinner == NoWinner) std::cout << "Got has not ended..." << std::endl;
}

winState Logger::getGameWinner() const {
    return gameWinner;
}

void Logger::setGameWinner(winState newWinner, const Player &player1,const Player &player2) {
    if (newWinner != NoWinner) {
        std::ostringstream ossP1;
        ossP1 << player1;
        player1Stats = ossP1.str();
        std::ostringstream ossP2;
        ossP2 << player2;
        player2Stats = ossP2.str();
    }
    Logger::gameWinner = newWinner;
}

void Logger::addTurn(std::string log) {
    turnsLog.push_back(log);
}

std::string Logger::toString() const {
    std::string str;
    if (gameWinner == Tie) {
        str = "Tie";
    } else if (gameWinner == P1Win) {
        str = "Player 1 Won";
    } else if (gameWinner == P2Win) {
        str = "Player 2 Won";
    } else if (gameWinner == NoWinner) {
        str = "No winner yet";
    }
    return str;
}

Logger::Logger() : gameWinner(NoWinner) {}
