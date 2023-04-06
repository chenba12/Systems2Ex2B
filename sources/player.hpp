#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <vector>
#include "card.hpp"

namespace ariel {
    class Player {
    private:
        const int id;
        const std::string playerName;
        std::vector<Card> deck;
        int cardsTaken;
        int numberOfWins;
        double winRate;
        int numberOfDraws;
        double drawRate;
        bool isPlaying;

    public:
        explicit Player(std::string playerName);

        Player();

        friend std::ostream &operator<<(std::ostream &ostream, const Player &player);

        bool operator==(const Player &rhs) const;

        bool operator!=(const Player &rhs) const;

        const std::string &getPlayerName() const;

        const std::vector<Card> &getDeck() const;

        void setDeck(const std::vector<Card> &newDeck);

        int cardesTaken() const;

        void setCardsTaken(int cardsTaken);

        int stacksize() const;

        int getNumberOfWins() const;

        void incrementNumberOfWins(int playerNumberOfWins);

        double getWinRate() const;

        void setWinRate(int turnsPlayed);

        bool getIsPlaying() const;

        void setIsPlaying(bool playerIsPlaying);

        Card &removeAndGetTopCard();

        int getNumberOfDraws() const;

        void incrementNumberOfDraws(int numberOfDraws);

        double getDrawRate() const;

        void setDrawRate(int turnsPlayed);

        int getID() const;

        static int getNextID();

    };
}

#endif