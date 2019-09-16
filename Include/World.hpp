/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** World.hpp
*/

#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

struct Block
{
    size_t idx;
    bool hole;
};

class World
{
public:
    World(const Vector2u &_size);
    const Vector2u &getSize() const;
    const Vector2f &getBlockSize() const;
    void destroy(const Vector2u &position);
    void aff(RenderTarget &window) const;

private:
    void create(const Vector2u &_size);
    void generate();

private:
    Vector2u size;
    Block **tab;
    const Vector2f blockSize;
};

#endif
