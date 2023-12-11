#include <SFML/Graphics.hpp>
#pragma once

class FallingBall {

private:
    sf::Vector2f ballPos;
    sf::CircleShape ball;
    float xVelocity;
    float yVelocity;
    float masss;
    int xInit;
    int yInit;
    int ballRadius;
    float force_y = 1000.f;
    float force_x = 500.f;
    float oldBallPosX;
    float oldBallPosY;

public:

    FallingBall(int bX, int bY, int radius, int vx, int vy, float mass) {
        ballPos.x = bX;
        ballPos.y = bY;
        ballRadius = radius;
        xVelocity = vx;
        yVelocity = vy;
        masss = mass;
        oldBallPosX = bX;
        oldBallPosY = bY;
    }

    void semiImplicitEuler() {
        sf::RenderWindow window(sf::VideoMode(1280, 720), "Physics");
        window.setFramerateLimit(60);
        ball.setPosition(ballPos);
        ball.setRadius(ballRadius);

        sf::Clock clock;

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed())
                    window.close();

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    window.close();
            }

            if (ballPos.x < 0 || ballPos.x > 1280 - 100)
                xVelocity *= -1;

            if (ballPos.y < 0 || ballPos.y > 720 - 100) {
                yVelocity *= -1;
            }

            float dt = clock.restart().asSeconds();

            float acc_x = force_x / masss;
            float acc_y = force_y / masss;

            xVelocity = xVelocity + acc_x * dt;
            yVelocity = yVelocity + acc_y * dt;

            ballPos.x = ballPos.x + xVelocity * dt;
            ballPos.y = ballPos.y + yVelocity * dt;


            ball.setPosition(ballPos);

            window.clear();
            window.draw(ball);
            window.display();

        }
    }

    void verletIntegration() {
        sf::RenderWindow window(sf::VideoMode(1280, 720), "Physics");
        window.setFramerateLimit(60);
        ball.setPosition(ballPos);
        ball.setRadius(ballRadius);

        sf::Clock clock;

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed())
                    window.close();

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    window.close();
            }

            if (ballPos.x < 0) {
                ballPos.x = 0;
                oldBallPosX = ballPos.x + xVelocity;
            }
            else if (ballPos.x > 1280) {
                ballPos.x = 1280;
                oldBallPosX = ballPos.x + xVelocity;
            }
            else if (ballPos.y < 0) {
                ballPos.y = 0;
                oldBallPosY = ballPos.y + yVelocity;
            }
            else if (ballPos.y > 720) {
                ballPos.y = 720;
                oldBallPosY = ballPos.y + yVelocity;
            }
            

            float dt = clock.restart().asSeconds();

            xVelocity = ballPos.x - oldBallPosX;
            yVelocity = ballPos.y - oldBallPosY;

            oldBallPosX = ballPos.x;
            oldBallPosY = ballPos.y;

            float acc_x = force_x / masss;
            float acc_y = force_y / masss;

            ballPos.x = ballPos.x + xVelocity + acc_x * dt * dt;
            ballPos.y = ballPos.y + yVelocity + acc_y * dt * dt;

            ball.setPosition(ballPos);

            window.clear();
            window.draw(ball);
            window.display();

        }
    }
};