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

        // Create ray
        c2Ray ray;
        ray.p = c2V(100, 100);
        ray.d = c2Norm(c2V(2, 1));
        ray.t = 300;

        // Create polygon
        c2Poly poly;
        poly.count = 4;
        poly.verts[0] = c2V(200, 150);
        poly.verts[1] = c2V(350, 180);
        poly.verts[2] = c2V(380, 250);
        poly.verts[3] = c2V(180, 280);
        c2MakePoly(&poly);

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
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                }

                // Raycast
                c2Raycast cast;
                int hit = c2RaytoPoly(ray, &poly, NULL, &cast);

                window.clear(sf::Color(30, 30, 30));

                tinyc2Debug.draw(ray, COLOR_NORMAL);
                tinyc2Debug.draw(poly, COLOR_NORMAL);
                if (hit) {
                        tinyc2Debug.draw(cast, ray);
                }

                window.display();
        }
}
