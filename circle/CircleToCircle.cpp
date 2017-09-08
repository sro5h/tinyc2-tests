#include <SFML/Graphics.hpp>
#define TINYC2_IMPL
#include "tinyc2.h"
#include "Tinyc2Debug.hpp"

#define SPEED 70.0f
#define COLOR_NORMAL sf::Color(41, 128, 185)
#define COLOR_HIT sf::Color(231, 76, 60)

int main()
{
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;

        sf::RenderWindow window(sf::VideoMode(500, 500), "App", sf::Style::Default, settings);

        // Create debug object
        Tinyc2Debug tinyc2Debug(window);

        // Create circle
        c2Circle circle;
        circle.p = c2V(200, 200);
        circle.r = 20;

        // Create other circle
        c2Circle other;
        other.p = c2V(300, 300);
        other.r = 50;

        sf::Clock clock;
        while (window.isOpen()) {
                // Get elapsed time
                float elapsed = clock.restart().asSeconds();

                sf::Event event;
                while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                                window.close();

                        } else if (event.type == sf::Event::KeyPressed &&
                                        event.key.code == sf::Keyboard::Q) {
                                window.close();
                        }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                        circle.p.x -= SPEED * elapsed;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                        circle.p.x += SPEED * elapsed;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                        circle.p.y -= SPEED * elapsed;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                        circle.p.y += SPEED * elapsed;
                }

                // Check for collision
                c2Manifold manifold;
                c2CircletoCircleManifold(circle, other, &manifold);

#ifdef SOLVE_COLLISION
                if (manifold.count > 0) {
                        circle.p.x -= manifold.normal.x * manifold.depths[0];
                        circle.p.y -= manifold.normal.y * manifold.depths[0];
                }
#endif

                window.clear(sf::Color(30, 30, 30));

                tinyc2Debug.draw(circle, COLOR_NORMAL);
                tinyc2Debug.draw(other, COLOR_NORMAL);
                tinyc2Debug.draw(manifold);

                window.display();
        }
}
