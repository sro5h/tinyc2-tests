#include <SFML/Graphics.hpp>
#define TINYC2_IMPLEMENTATION
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

        // Create other circle
        c2Circle circle;
        circle.p = c2V(300, 300);
        circle.r = 50;

        // Create capsule
        c2Capsule capsule;
        capsule.a = c2V(200, 200);
        capsule.b = c2V(250, 200);
        capsule.r = 20;

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
                c2CircletoCapsuleManifold(circle, capsule, &manifold);

#ifdef SOLVE_COLLISION
                if (manifold.count > 0) {
                        circle.p.x -= manifold.normal.x * manifold.depths[0];
                        circle.p.y -= manifold.normal.y * manifold.depths[0];
                }
#endif

                window.clear(sf::Color(30, 30, 30));

                tinyc2Debug.draw(circle, COLOR_NORMAL);
                tinyc2Debug.draw(capsule, COLOR_NORMAL);
                tinyc2Debug.draw(manifold);

                window.display();
        }
}

/*
        zlib license:

        Copyright (c) 2017 Paul Meffle http://github.com/sro5h
        This software is provided 'as-is', without any express or implied
        warranty.  In no event will the authors be held liable for any damages
        arising from the use of this software.
        Permission is granted to anyone to use this software for any purpose,
        including commercial applications, and to alter it and redistribute it
        freely, subject to the following restrictions:
          1. The origin of this software must not be misrepresented; you must
             not claim that you wrote the original software. If you use this
             software in a product, an acknowledgment in the product
             documentation would be appreciated but is not required.
          2. Altered source versions must be plainly marked as such, and must
             not be misrepresented as being the original software.
          3. This notice may not be removed or altered from any source
             distribution.
*/
