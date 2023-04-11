#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "player.hpp"
#include "card.hpp"
#include <vector>
#include "logger.hpp"

namespace ariel {
    class Game {
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

        bool operator==(const Game &rhs) const;

        bool operator!=(const Game &rhs) const;

        void playTurn();

        void playAll();

        void printStats() const;

        void printLog() const;

        void printLastTurn() const;

        void printWiner() const;

        void generateDeck();

        static void shuffleDeck(std::vector<Card> &deck);

        const std::vector<Card> &getGameDeck() const;

        void setGameDeck(const std::vector<Card> &newGameDeck);

        Player &getPlayer1() const;

        Player &getPlayer2() const;

        int getNumberOfTurns() const;

        void setNumberOfTurns(int newNumberOfTurns);

        bool isPlaying1() const;

        void setIsPlaying(bool newIsPlaying);

        void setNumberOfDraws(int newNumberOfDraws);

        void startGame();

        void endGame();
    };
}
#endif