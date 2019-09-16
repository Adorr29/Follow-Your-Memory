/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Main.cpp
*/

#include <iostream>
#include "World.hpp"
#include "Player.hpp"

using namespace std;
using namespace sf;

int main()
{
    srand(time(nullptr));
    RenderWindow window(VideoMode(900, 900), "Follow Your Memory", Style::Close);
    View view(Vector2f(0, 0), Vector2f(window.getSize().x, window.getSize().y));
    World world(Vector2u(101, 101));
    Player player(world);

    window.setFramerateLimit(30);
    while (window.isOpen()) {
        for (Event event; window.pollEvent(event);) {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::KeyPressed) {
                Orientation way = (Orientation)-1;

                if (event.key.code == Keyboard::Up)
                    way = Up;
                else if (event.key.code == Keyboard::Down)
                    way = Down;
                else if (event.key.code == Keyboard::Left)
                    way = Left;
                else if (event.key.code == Keyboard::Right)
                    way = Right;
                if (way != -1)
                    player.move(way);
            }
        }
        player.update();
        player.centerView(view);
        window.setView(view);
        window.clear();
        world.aff(window);
        player.aff(window);
        window.display();
    }
    return 0;
}
