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
        ray.d = c2Norm(c2V(2, 1));
        ray.t = 200;

        // Create aabb
        c2AABB aabb;
        aabb.min = c2V(180, 180);
        aabb.max = c2V(220, 220);

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
                        aabb.min.x -= SPEED * elapsed;
                        aabb.max.x -= SPEED * elapsed;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                        aabb.min.x += SPEED * elapsed;
                        aabb.max.x += SPEED * elapsed;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                        aabb.min.y -= SPEED * elapsed;
                        aabb.max.y -= SPEED * elapsed;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                        aabb.min.y += SPEED * elapsed;
                        aabb.max.y += SPEED * elapsed;
                }

                // Raycast
                c2Raycast cast;
                int hit = c2RaytoAABB(ray, aabb, &cast);

                window.clear(sf::Color(30, 30, 30));

                tinyc2Debug.draw(ray, COLOR_NORMAL);
                tinyc2Debug.draw(aabb, COLOR_NORMAL);
                if (hit) {
                        tinyc2Debug.draw(cast, ray);
                }

                window.display();
        }
}
