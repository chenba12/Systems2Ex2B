#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "player.hpp"
#include "card.hpp"
#include <vector>
#include "logger.hpp"

namespace ariel {
    class Game {
    private:
        std::vector<Card> gameDeck;
        Player &player1;
        Player &player2;
        int numberOfTurns;
        bool isPlaying;
        Logger logger;
        int numberOfDraws;

    public:

        Game(Player &player1, Player &player2);

        friend std::ostream &operator<<(std::ostream &ostream, const Game &game);

        bool operator==(const Game &otherGame) const;

        bool operator!=(const Game &otherGame) const;

        void playTurn();

        void playAll();

        void printStats();

        void printLog() const;

        void printLastTurn() const;

        void printWiner() const;

    private:
        void generateDeck();

        static void shuffleDeck(std::vector<Card> &deck);

        void setGameDeck(const std::vector<Card> &newGameDeck);

        void setNumberOfTurns(int newNumberOfTurns);

        void startGame();

        void endGame();

        void
        P1WinTurn(const std::vector<Card> &p1ThrownCards, const std::vector<Card> &p2ThrownCards, const Card &p1Card,
                  const Card &p2Card,
                  std::string &turnLog);

        void
        P2WinTurn(const std::vector<Card> &p1ThrownCards, const std::vector<Card> &p2ThrownCards, const Card &p1Card,
                  const Card &p2Card,
                  std::string &turnLog);
    };
}
#endif