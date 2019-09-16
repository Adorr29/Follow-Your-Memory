/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** World.cpp
*/

#include "World.hpp"
#include "Error.hpp"

World::World(const Vector2u &_size)
    : blockSize(100, 100)
{
    create(_size);
    generate();
}

const Vector2u &World::getSize() const
{
    return size;
}

const Vector2f &World::getBlockSize() const
{
    return blockSize;
}

void World::destroy(const Vector2u &position)
{
    // TODO
    tab[position.x][position.y].hole = true;
}

void World::aff(RenderTarget &window) const
{
    VertexArray vertexArray(Quads);
    Texture texture;
    size_t textureSize;

    if (!texture.loadFromFile("Resources/Texture/Tilemap.png"))
        throw Error("Tilemap can't be load");
    textureSize = texture.getSize().y;
    for (Uint32 i = 0; i < size.x; i++)
        for (Uint32 j = 0; j < size.y; j++) {
            Vertex vertex[4];
            size_t nb = tab[i][j].idx;

            if (tab[i][j].hole)
                nb = 14;
            vertex[0].position = Vector2f(blockSize.x * i, blockSize.y * j);
            vertex[1].position = Vector2f(blockSize.x * (i + 1), blockSize.y * j);
            vertex[2].position = Vector2f(blockSize.x * (i + 1), blockSize.y * (j + 1));
            vertex[3].position = Vector2f(blockSize.x * i, blockSize.y * (j + 1));

            vertex[0].texCoords = Vector2f(nb * textureSize, 0);
            vertex[1].texCoords = Vector2f((nb + 1) * textureSize, 0);
            vertex[2].texCoords = Vector2f((nb + 1) * textureSize, textureSize);
            vertex[3].texCoords = Vector2f(nb * textureSize, textureSize);
            for (size_t n = 0; n < 4; n++)
                vertexArray.append(vertex[n]);
        }
    window.draw(vertexArray, RenderStates(&texture));
}

void World::create(const Vector2u &_size)
{
    size = _size;
    tab = new Block* [size.x];
    for (Uint32 i = 0; i < size.x; i++)
        tab[i] = new Block [size.y];
}

void World::generate()
{
    for (Uint32 i = 0; i < size.x; i++)
        for (Uint32 j = 0; j < size.y; j++) {
            tab[i][j] = {0, false};
            if (rand() % 2)
                tab[i][j].idx = rand() % 13 + 1; // ??
        }
}
