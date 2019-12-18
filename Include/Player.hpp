/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Player.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "World.hpp"

using namespace std;
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
    Player(World &_world, const bool &_isSoul = false);
    const Vector2u &getPosition() const;
    const Vector2u &getNextPosition() const;
    Vector2f getFloatPosition() const;
    void setPosition(const Vector2u &_position);
    void centerView(View &view);
    bool move(const Orientation &way);
    void update();
    void aff(RenderTarget &window) const;

private:
    Vector2i convertToVector(const Orientation &way);

private:
    World &world;
    Vector2u position;
    Vector2u nextPosition;
    float moveStatus;
    float speed;
    Orientation orientation;
    size_t movingStep;
    bool isSoul;
};
