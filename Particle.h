#include <SFML/Graphics.hpp>

#pragma once

class Particle {
private:
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::CircleShape s;

public:
    Particle(float pos_x, float pos_y, float vel_x, float vel_y) {
        pos.x = pos_x;
        pos.y = pos_y;
        vel.x = vel_x;
        vel.y = vel_y;

        s.setPosition(pos);
        s.setFillColor(sf::Color::White);
        s.setRadius(10);

    }

    void Render(sf::RenderWindow& wind) {
        s.setPosition(pos);
        wind.draw(s);
    }

    void updatePhysics(GravitySource& s) {
        float distX = s.getPosition().x - pos.x;
        float distY = s.getPosition().y - pos.y;

        //Ipotenuza = distanta de la punct la centru de forta
        float distance = sqrt(distX * distX + distY * distY);

        //Normare
        float inverse_dist = 1.f / distance;

        float normX = inverse_dist * distX;
        float normY = inverse_dist * distY;

        float inverse_sq_dropoff = inverse_dist * inverse_dist;

        float accX = normX * s.getStrength() * inverse_sq_dropoff;
        float accY = normY * s.getStrength() * inverse_sq_dropoff;

        vel.x += accX;
        vel.y += accY;

        pos.x += vel.x;
        pos.y += vel.y;


    }

};