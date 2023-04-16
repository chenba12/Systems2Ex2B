#include "doctest.h"
#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"

using namespace ariel;


TEST_CASE("Test init Game") {
    Player p1("Chen");
    Player p2("Shira");
    Player p3("Beni");
    Game game(p1, p2);
    CHECK((p1.stacksize() + p2.stacksize() == 52));
    CHECK((p1.cardesTaken() == 0));
    CHECK((p2.cardesTaken() == 0));
    CHECK_THROWS(game.printLastTurn());
    CHECK_NOTHROW(game.printWiner());
    CHECK_THROWS(game.printLog());
    CHECK_NOTHROW(game.playTurn());
    Game game1(p1, p3);
    Game game2(p1, p1);
    CHECK_THROWS(game1.playTurn());
    CHECK_THROWS(game2.playTurn());


}

TEST_CASE("Test play turn") {
    Player p1("Chen");
    Player p2("Shira");

    Game game(p1, p2);
    game.playTurn();
    CHECK((p1.cardesTaken() >= 1 || p2.cardesTaken() >= 1));
    CHECK((p1.stacksize() != 26));
    CHECK((p2.stacksize() != 26));
    CHECK_NOTHROW(game.printStats());
    CHECK_NOTHROW(game.printWiner());
    CHECK_NOTHROW(game.printLog());
}

TEST_CASE("Check game ended") {
    Player p1("Chen");
    Player p2("Shira");
    Game game(p1, p2);
    game.playAll();

    CHECK((p1.cardesTaken() + p2.cardesTaken() + p1.stacksize() + p2.stacksize() == 52));
    CHECK_THROWS(game.playTurn());
    CHECK_THROWS(game.playAll());
    CHECK_NOTHROW(game.printWiner());
    CHECK_NOTHROW(game.printLog());
    CHECK_NOTHROW(Game(p1, p2));
}


TEST_CASE("stack size changes") {
    Player p1("Chen");
    Player p2("Shira");
    Game game(p1, p2);
    int startingPoint = 26;
    for (int i = 1; i <= 10; ++i) {
        game.playTurn();
        CHECK((p1.stacksize() <= startingPoint - i));
        CHECK((p2.stacksize() <= startingPoint - i));
        CHECK((p1.cardesTaken() >= i || p2.cardesTaken() >= i));
    }
}