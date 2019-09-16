/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Player.cpp
*/

#include "Player.hpp"
#include "Error.hpp"

Player::Player(World &_world)
    : world(_world), spawnPosition((_world.getSize().x - 1) / 2.0, (_world.getSize().y - 1) / 2.0), moveStatus(0), speed(0.2), orientation(Down), movingStep(0)
{
    generateSoulMove(10);
    reset();
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
            if ((Vector2i)nextPosition - (Vector2i)position == convertToVector(soulMove[index])) {
                index++;
                if (index >= soulMove.size()) {
                    spawnPosition = nextPosition;
                    generateSoulMove(10); // 10 ?
                    index = 0;
                }
            }
            else {
                world.destroy(nextPosition);
                reset();
            }
            moveStatus = 0;
            position = nextPosition;
        }
        else
            moveStatus += speed;
        movingStep = moveStatus * (float)(5 - 1);
    }
}

void Player::reset()
{
    position = spawnPosition;
    nextPosition = spawnPosition;
    moveStatus = 0;
    //speed = 0.2; // ?
    orientation = Down; // ?
    movingStep = 0;
    index = 0;
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
    sprite.setPosition(world.getBlockSize().x * getPosition().x, world.getBlockSize().y * getPosition().y);
    window.draw(sprite);
}

void Player::generateSoulMove(const size_t &size)
{
    soulMove.clear();
    for (size_t i = 0; i < size; i++)
        soulMove.push_back((Orientation)(rand() % 4));
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
