#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "player.hpp"
#include "card.hpp"
#include <vector>

namespace ariel {
    class Game {
        std::vector<Card> gameDeck;
        Player &player1;
        Player &player2;
        std::vector<std::string> turnsLog;
        int numberOfTurns;
        bool isPlaying;
        winState winner;
        int numberOfDraws;

    public:

        Game(Player &player1, Player &player2);

        friend std::ostream &operator<<(std::ostream &ostream, const Game &game);

        bool operator==(const Game &rhs) const;

        bool operator!=(const Game &rhs) const;


        static std::string logTurn(const Card &p1CardPlayed, const Card &p2CardPlayed, const std::string &player1Name,
                                   const std::string &player2Name,
                                   const std::string &winnerString);

        void playTurn();

        void printLastTurn();

        void playAll();

        void printWiner();

        void printLog();

        void printStats() const;

        std::vector<std::string> getTurnsLog();

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

        int getWinner() const;

        void setWinner(enum winState newWinner);

        void setNumberOfDraws(int newNumberOfDraws);

        void startGame();

        void endGame();
    };
}
#endif