/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Player.cpp
*/

#include "Player.hpp"
#include "Error.hpp"

Player::Player(World &_world, const bool &_isSoul)
    : world(_world), position(_world.getSize() / (Uint32)2), moveStatus(0), speed(0.2), orientation(Down), movingStep(0), isSoul(_isSoul)
{
}

const Vector2u &Player::getPosition() const
{
    return position;
}

const Vector2u &Player::getNextPosition() const
{
    return nextPosition;
}

Vector2f Player::getFloatPosition() const
{
    const Vector2f diff((int)nextPosition.x - (int)position.x, (int)nextPosition.y - (int)position.y);
    const Vector2f floatPosition(position.x, position.y);

    return floatPosition + diff * moveStatus;
}

void Player::setPosition(const Vector2u &_position)
{
    position = _position;
    nextPosition = _position;
    moveStatus = 0;
    orientation = Down; // ?
    movingStep = 0;
}

void Player::centerView(View &view)
{
    view.setCenter(world.getBlockSize().x * (getFloatPosition().x + 0.5), world.getBlockSize().y * (getFloatPosition().y + 0.5));
}

bool Player::move(const Orientation &way)
{
    if (position != nextPosition)
        return false;
    orientation = way;
    nextPosition.x = position.x + convertToVector(way).x;
    nextPosition.y = position.y + convertToVector(way).y;
    return true;
}

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
    //RectangleShape soulSprite(world.getBlockSize());
    Texture texture;
    Vector2f textureSize;

    if (!texture.loadFromFile("Resources/Texture/Player.png"))
        throw Error("Player can't be load");
    textureSize = Vector2f(texture.getSize().x / 5.0, texture.getSize().y / 4.0);
    sprite.setTexture(&texture);
    sprite.setTextureRect(IntRect(textureSize.x * movingStep, textureSize.x * orientation, textureSize.x, textureSize.y));
    sprite.setPosition(world.getBlockSize().x * getFloatPosition().x, world.getBlockSize().y * getFloatPosition().y);
    if (isSoul)
        sprite.setFillColor(Color(255, 255, 255, 100));
    window.draw(sprite);
}

Vector2i Player::convertToVector(const Orientation &way)
{
    if (way == Up)
        return Vector2i(0, -1);
    if (way == Right)
        return Vector2i(1, 0);
    if (way == Down)
        return Vector2i(0, 1);
    if (way == Left)
        return Vector2i(-1, 0);
    return Vector2i(0, 0);
}
