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
        int deckSize;
        int numberOfWins;
        double winRate;
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

        void setTopCard(const Card &playerTopCard);

        int getCardsTaken() const;

        void setCardsTaken(int cardsTaken);

        int getDeckSize() const;

        void setDeckSize(int playerGetSize);

        int getNumberOfWins() const;

        void setNumberOfWins(int playerNumberOfWins);

        double getWinRate() const;

        void setWinRate(double playerWinRate);

        bool isPlaying1() const;

        void setIsPlaying(bool playerIsPlaying);

    };
}
#endif