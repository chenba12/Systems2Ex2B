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
        int winner;
        int numberOfDraws;

    public:

        Game(Player &player1, Player &player2);

        friend std::ostream &operator<<(std::ostream &os, const Game &game);

        bool operator==(const Game &rhs) const;

        bool operator!=(const Game &rhs) const;

        virtual ~Game();


        void playTurn();

        void printLastTurn();

        void playAll();

        void printWiner();

        void printLog();

        void printStats();

        std::vector<std::string> getTurnsLog();

        void generateDeck();

        void shuffleDeck(std::vector<Card> &deck);

        const std::vector<Card> &getGameDeck() const;

        void setGameDeck(const std::vector<Card> &gameDeck);

        Player &getPlayer1() const;

        void setPlayer1(Player &player1);

        Player &getPlayer2() const;

        void setPlayer2(Player &player2);

        void setTurnsLog(const std::vector<std::string> &turnsLog);

        int getNumberOfTurns() const;

        void setNumberOfTurns(int numberOfTurns);

        bool isPlaying1() const;

        void setIsPlaying(bool isPlaying);

        int getWinner() const;

        void setWinner(int winner);

        int getNumberOfDraws() const;

        void setNumberOfDraws(int numberOfDraws);
    };
}
#endif