#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>


const float PI = 3.14159265f;
const float g = 1000;


class Pendulum {

private:
    float length;
    float angle;
    float angularVelocity = 0.0f;

public:
    Pendulum(float length, float initialAngle) : length(length), angle(initialAngle) {}

    void update(float dt) {
        float angularAcceleration = -g / length * std::sin(angle);
        angularVelocity += angularAcceleration * dt;
        angle += angularVelocity * dt;
    }

    sf::Vector2f getPosition() const {
        float x = length * std::sin(angle);
        float y = length * std::cos(angle);
        return sf::Vector2f(x, y);
    }
};
