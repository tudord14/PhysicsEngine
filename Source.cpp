#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "FallingBall.h"
#include "GravitySource.h"
#include "Particle.h"
#include "Pendulum.h"

int main()
{
    //int number;
    //std::cout << "Choice of experiment -> " << std::endl;
    //std::cout << "Falling Ball (0) -> given already" << std::endl;
    //std::cout << "Physics Pendulum (1)" << std::endl;
    //std::cout << "Gravity source and one particle (2)" << std::endl;
    //std::cout << "Press (1) or (2): ";
    //std::cin >> number;

    Pendulum pendulum(150.0f, PI / 4.0f);
    sf::CircleShape bob(20.0f);
    bob.setFillColor(sf::Color::Red);
    bob.setOrigin(20.0f, 20.0f);

    sf::Vertex line[] = {
    sf::Vertex(sf::Vector2f(400.0f, 300.0f)),
    sf::Vertex(pendulum.getPosition() + sf::Vector2f(400.0f, 300.0f))
    };

    
    //Ball pos, Ball radius, Ball vx vy
    FallingBall ball2(600, 300, 50, 0, 5, 1);
    ball2.semiImplicitEuler();

    //Gravity source
    GravitySource source(800, 500, 70000);
    Particle particle1(400, 800, 6, 0);
    Particle particle2(300, 1000, 6, 0);


    const unsigned width = 800;
    const unsigned height = 600;
    sf::RenderWindow window(sf::VideoMode(width, height), "Player!!!");
    window.setFramerateLimit(120);


    //Create Player for Collision Detection
    const float size = 50.f;
    const float playerVelocity = 100.f;
    const float dt = 0.1;

    sf::RectangleShape player;
    sf::Vector2f playerPosition(size, size);
    sf::Vector2f velocity;
    player.setFillColor(sf::Color::Magenta);
    player.setSize(playerPosition);


    //Create Square for Colision Detection
    sf::RectangleShape sq;
    sf::Vector2f v2f(size, size);
    sq.setFillColor(sf::Color::Blue);
    sq.setSize(v2f);
    sq.setPosition(width / 2, height / 2);

    sf::Clock clock1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        velocity.x = 0.f;
        velocity.y = 0.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            velocity.y = -playerVelocity * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            velocity.y = playerVelocity * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            velocity.x = playerVelocity * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            velocity.x = -playerVelocity * dt;
        }


        player.move(velocity);

        //Wall Collision
        if (player.getPosition().x < 0.f) {
            player.setPosition(0, player.getPosition().y);
            std::cout << "Collision Left" << std::endl;
        }

        if (player.getPosition().y < 0.f) {
            player.setPosition(player.getPosition().x, 0);
            std::cout << "Collision Up" << std::endl;
        }

        if (player.getPosition().x + player.getGlobalBounds().width > width) {
            player.setPosition(width - player.getGlobalBounds().width, player.getPosition().y);
            std::cout << "Collision Right" << std::endl;
        }


        if (player.getPosition().y + player.getGlobalBounds().height > height) {
            player.setPosition(player.getPosition().x, height - player.getGlobalBounds().height);
            std::cout << "Collision Down" << std::endl;
        }

        //Object Collision
        if ((sq.getPosition().x - player.getPosition().x == player.getGlobalBounds().width) 
            && (abs(player.getPosition().y - sq.getPosition().y) <= player.getGlobalBounds().height) 
            && player.getPosition().x + player.getGlobalBounds().width < sq.getPosition().x + sq.getGlobalBounds().width) {
            player.setPosition(350, player.getPosition().y);
            std::cout << "Ceva" << std::endl;
            velocity.x = 0.f;
            std::cout << sq.getPosition().x - player.getGlobalBounds().width << std::endl;
        }

        window.clear();
        //window.draw(player);
        //window.draw(sq);

        float dt = clock1.restart().asSeconds();

        pendulum.update(dt);
        line[1] = sf::Vertex(pendulum.getPosition() + sf::Vector2f(400.0f, 300.0f));
        bob.setPosition(pendulum.getPosition() + sf::Vector2f(400.0f, 300.0f));

        window.draw(line, 2, sf::Lines);
        window.draw(bob);

        //window.draw(wall1);
        //window.draw(wall2);
        //window.draw(square);

        //particle1.updatePhysics(source);
        //particle2.updatePhysics(source);

        //source.Render(window);
        //particle1.Render(window);
        //particle2.Render(window);

        window.display();
    }


    return 0;
}