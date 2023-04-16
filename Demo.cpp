/**
 * Demo file for the exercise on binary tree
 *
 * @author Evgeny Hershkovitch Neiterman
 * @since 2023-03
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"

using namespace ariel;

int main() {
    // Create two players with their names
    Player p1("Alice");
    Player p2("Bob");

    Game game(p1, p2);
    for (int i = 0; i < 5; i++) {
        game.playTurn();
    }
    game.playAll();
    game.printLog();
    //Play another game after the game ended
    Game game2(p1, p2);
    game2.playAll();

    //shows that both statistics are different according to the turns in the game
    game2.printStats();
    game.printStats();

    game2.printLastTurn();
    game.printLastTurn();
    game.printWiner();
    game2.printWiner();
}