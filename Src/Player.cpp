/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Player.cpp
*/

#include "Player.hpp"
#include "Error.hpp"

Player::Player(const World &_world)
    : world(_world), position((_world.getSize().x - 1) / 2.0, (_world.getSize().y - 1) / 2.0), moveStatus(0), speed(0.2), orientation(Down), movingStep(0)
{
    nextPosition = position;
}

Vector2f Player::getPosition() const
{
    const Vector2f diff((int)nextPosition.x - (int)position.x, (int)nextPosition.y - (int)position.y);
    const Vector2f floatPosition(position.x, position.y);

    return floatPosition + diff * moveStatus;
}

void Player::centerView(View &view)
{
    view.setCenter(world.getBlockSize().x * (getPosition().x + 0.5), world.getBlockSize().y * (getPosition().y + 0.5));
}

bool Player::move(const Vector2i &way)
{
    if (position != nextPosition)
        return false;
    nextPosition.x = position.x + way.x;
    nextPosition.y = position.y + way.y;
    updateOrientation(way);
    return true;
}

#include <iostream>
void Player::update()
{
    if (position != nextPosition) {
        if (moveStatus + speed > 1.0) {
            moveStatus = 0;
            position = nextPosition;
        }
        else
            moveStatus += speed;
        movingStep = moveStatus * (float)(5 - 1);
    }
}

void Player::aff(RenderTarget &window) const
{
    RectangleShape sprite(world.getBlockSize());
    Texture texture;
    Vector2f textureSize;

    if (!texture.loadFromFile("Resources/Texture/Player.png"))
        throw Error("Player can't be load");
    textureSize = Vector2f(texture.getSize().x / 5.0, texture.getSize().y / 4.0);
    sprite.setTexture(&texture);
    sprite.setTextureRect(IntRect(textureSize.x * movingStep, textureSize.x * orientation, textureSize.x, textureSize.y));
    sprite.setPosition(world.getBlockSize().x * getPosition().x, world.getBlockSize().y * getPosition().y);
    window.draw(sprite);
}

void Player::updateOrientation(const Vector2i &way)
{
    if (way.x == 0 && way.y == -1)
        orientation = Up;
    else if (way.x == 1 && way.y == 0)
        orientation = Right;
    else if (way.x == 0 && way.y == 1)
        orientation = Down;
    else if (way.x == -1 && way.y == 0)
        orientation = Left;
}
