#include <iostream>
#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"

using namespace std;
using namespace ariel;

int main() {
    Player p1("Alice");
    Player p2("Bob");

    Game game(p1, p2);
    for (int i = 0; i < 5; i++) {
        game.playTurn();
    }
    game.printLastTurn();
    game.playAll();
    game.printLog();

    //Play another game after the game ended
    Game game2(p1, p2);
    game2.playAll();

    //shows that both statistics are different according to the turns in the game
    cout << "Game 1 printStats:" << endl;
    game.printStats();
    cout << "Game 2 printStats:" << endl;
    game2.printStats();


    cout << "Game 1 printLastTurn:" << endl;
    game.printLastTurn();
    cout << "Game 2 printLastTurn:" << endl;
    game2.printLastTurn();

    cout << "Game 1 winner:" << endl;
    game.printWiner();
    cout << "Game 2 winner:" << endl;
    game2.printWiner();
    return 0;
}