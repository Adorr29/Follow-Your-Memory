/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "World.hpp"

using namespace sf;

enum Orientation
{
    Up,
    Right,
    Down,
    Left,
};

class Player
{
public:
    Player(const World &_world);
    Vector2f getPosition() const;
    void centerView(View &view);
    bool move(const Vector2i &way); // TODO send Orientation in param
    void update();
    void aff(RenderTarget &window) const;

private:
    void updateOrientation(const Vector2i &way);

private:
    const World &world;
    Vector2u position;
    Vector2u nextPosition;
    float moveStatus;
    float speed;
    Orientation orientation;
    size_t movingStep;
};

#endif
