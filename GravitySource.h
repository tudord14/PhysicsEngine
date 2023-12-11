#include <SFML/Graphics.hpp>

#pragma once

class GravitySource {
private:
    sf::Vector2f pos;
    float strength;
    sf::CircleShape s;
    sf::Vector2f posWall1;
    sf::RectangleShape wall;


public:
    GravitySource(float pos_x, float pos_y, float strength) {
        pos.x = pos_x;
        pos.y = pos_y;
        //pentru a fi sigur ca imi atribuie valoarea ceruta in functie
        this->strength = strength;

        s.setPosition(pos);
        s.setFillColor(sf::Color::Red);
        s.setRadius(10);

        posWall1.x = pos_x * 2;
        posWall1.y = 20;

        wall.setFillColor(sf::Color::White);
        wall.setPosition(pos_x, 10);
        wall.setOrigin(pos_x / 2, pos_y / 2);


    }

    void Render(sf::RenderWindow& wind) {
        wind.draw(s);
        wind.draw(wall);
    }

    sf::Vector2f getPosition() {
        return pos;
    }

    float getStrength() {
        return strength;
    }

};