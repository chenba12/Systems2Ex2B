cmake_minimum_required(VERSION 3.24)
project(Systems2Ex2B)

set(CMAKE_CXX_STANDARD 14)

add_executable(Demo.cpp sources/player.cpp sources/player.hpp sources/game.hpp sources/game.cpp sources/card.cpp sources/card.hpp)
