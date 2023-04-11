//
// Created by chen on 4/11/23.
//

#ifndef SYSTEMS2EX2B_LOGGER_H
#define SYSTEMS2EX2B_LOGGER_H

#include <iostream>
#include <vector>
#include "player.hpp"
#include "card.hpp"

namespace ariel {
    class Logger {
    private:
        winState gameWinner;
        std::vector<std::string> turnsLog;
    public:

        Logger();

        std::string logTurn(const Card &p1CardPlayed, const Card &p2CardPlayed, const std::string &player1Name,
                            const std::string &player2Name,
                            const std::string &winnerString) const;

        void printLastTurn() const;

        void printWiner(const Player &player1, const Player &player2) const;

        void printLog() const;

        void printStats(const Player &player1, const Player &player2) const;

        winState getGameWinner() const;

        void setGameWinner(winState newWinner);

        void addTurn(std::string log);

        std::string toString() const;

    };
}
#endif //SYSTEMS2EX2B_LOGGER_H
