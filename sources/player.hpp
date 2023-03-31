#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <vector>
#include "card.hpp"

namespace ariel {
    class Player {
    private:
        std::string playerName;
        std::vector<Card> deck;
        Card topCard;
        int cardsTaken;
        int numberOfWins;
        double winRate;
        int numberOfDraws;
        double drawRate;
        bool isPlaying;

    public:
        explicit Player(std::string playerName);

        Player();

        friend std::ostream &operator<<(std::ostream &os, const Player &player);

        bool operator==(const Player &rhs) const;

        bool operator!=(const Player &rhs) const;

        ~Player();

        const std::string &getPlayerName() const;

        void setPlayerName(const std::string &newPlayerName);

        const std::vector<Card> &getDeck() const;

        void setDeck(const std::vector<Card> &newDeck);

        const Card &getTopCard() const;

        int getCardsTaken() const;

        void setCardsTaken(int cardsTaken);

        unsigned long getDeckSize() const;

        int getNumberOfWins() const;

        void setNumberOfWins(int playerNumberOfWins);

        double getWinRate() const;

        void setWinRate(int turnsPlayed);

        bool getIsPlaying() const;

        void setIsPlaying(bool playerIsPlaying);

        void removeTopCard();

        int getNumberOfDraws() const;

        void setNumberOfDraws(int numberOfDraws);

        double getDrawRate() const;

        void setDrawRate(int turnsPlayed);

    };
}
#endif