#include <SFML/Graphics.hpp>
#define TINYC2_IMPL
#include "../tinyc2.h"
#include "../Tinyc2Debug.hpp"

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
        ray.d = c2Norm(c2V(1, 2));
        ray.t = 3000;

        // Create circle
        c2Circle circle;
        circle.p = c2V(200, 200);
        circle.r = 30;

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

                // Raycast
                c2Raycast cast;
                c2RaytoCircle(ray, circle, &cast);

                window.clear(sf::Color(30, 30, 30));

                tinyc2Debug.draw(ray, COLOR_NORMAL);
                tinyc2Debug.draw(circle, COLOR_NORMAL);
                tinyc2Debug.draw(cast, ray);

                window.display();
        }
}
