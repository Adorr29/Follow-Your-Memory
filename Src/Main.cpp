/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Main.cpp
*/

#include <iostream> // ?
#include "Game.hpp"

using namespace std;
using namespace sf;

int main()
{
    srand(time(nullptr));
    Game game;

    game.run();
    return 0;
}
