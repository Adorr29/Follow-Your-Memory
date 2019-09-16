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
    Player(World &_world);
    Vector2f getPosition() const;
    void centerView(View &view);
    bool move(const Orientation &way);
    void update();
    void reset();
    void aff(RenderTarget &window) const;

private:
    void generateSoulMove(const size_t &size);
    Vector2i convertToVector(const Orientation &way);

private:
    World &world;
    Vector2u spawnPosition;
    Vector2u position;
    Vector2u nextPosition;
    float moveStatus;
    float speed;
    Orientation orientation;
    size_t movingStep;
    vector<Orientation> soulMove;
    size_t index;
};

#endif
