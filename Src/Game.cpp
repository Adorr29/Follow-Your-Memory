/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Game.cpp
*/

#include <iostream> // tmp
#include "Game.hpp"

Game::Game()
    : window(VideoMode(900, 900), "Follow Your Memory", Style::Close),
      view(Vector2f(0, 0), Vector2f(window.getSize().x, window.getSize().y)),
      world(Vector2u(100, 100)),
      soul(world, true),
      player(world)
{
    window.setFramerateLimit(30);
    spawnPosition = Vector2u(world.getSize() / (Uint32)2);
    generateSoulMove(10);
    reset();
}

void Game::run()
{
    while (window.isOpen()) {
        pollEvent();
        update();
        window.clear();
        display();
        window.display();
    }
}

void Game::reset()
{
    soul.setPosition(spawnPosition);
    player.setPosition(spawnPosition);
    soulIndex = 0;
}

void Game::pollEvent()
{
    for (Event event; window.pollEvent(event);)
        if (event.type == Event::Closed)
            window.close();
        else if (event.type == Event::KeyPressed)
            keyPressed(event.key.code);
}

void Game::keyPressed(const Keyboard::Key &keyCode)
{
    Orientation way;

    if (keyCode == Keyboard::Up)
        way = Up;
    else if (keyCode == Keyboard::Down)
        way = Down;
    else if (keyCode == Keyboard::Left)
        way = Left;
    else if (keyCode == Keyboard::Right)
        way = Right;
    else
        return;
    if (player.move(way))
        soul.move(soulMove[soulIndex++]);
}

void Game::update()
{
    soul.update();
    player.update();
    player.centerView(view);
    window.setView(view);
    if (player.getPosition() != soul.getPosition()) {
        flash = true;
        world.destroy(player.getPosition());
        reset();
    }
    else if (player.getPosition() == player.getNextPosition() && soulIndex == soulMove.size()) {
        spawnPosition = player.getPosition();
        generateSoulMove(10);
    }
}

void Game::display()
{
    world.aff(window);
    soul.aff(window);
    player.aff(window);

    if (flash) {
        RectangleShape flashRect(Vector2f(window.getSize()));

        flashRect.setOrigin(Vector2f(flashRect.getSize() / (float)2));
        flashRect.setPosition(view.getCenter());
        window.draw(flashRect);
        flash = false;
    }
}

void Game::generateSoulMove(const size_t &size)
{
    soulIndex = 0;
    soulMove.resize(size);
    for (size_t i = 0; i < size; i++)
        soulMove[i] = (Orientation)(rand() % 4);
}
