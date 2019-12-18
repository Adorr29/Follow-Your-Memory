/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Game.cpp
*/

#pragma once

#include "World.hpp"
#include "Player.hpp"

class Game
{
public:
    Game();
    void run();
    void reset();

private:
    void pollEvent();
    void keyPressed(const Keyboard::Key &keyCode);
    void update();
    void display();
    void generateSoulMove(const size_t &size);

private:
    RenderWindow window;
    View view;
    World world;
    Player soul;
    Player player;
    Vector2u spawnPosition;
    vector<Orientation> soulMove;
    size_t soulIndex;
    bool flash;
};
