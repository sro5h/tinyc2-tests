#ifndef _TINYC2_DEBUG_HPP
#define _TINYC2_DEBUG_HPP

#include <SFML/Graphics.hpp>

class Tinyc2Debug {
private:
        sf::RenderTarget& mTarget;

public:
        Tinyc2Debug(sf::RenderTarget& target)
                : mTarget(target)
        {

        }

        void draw(const c2Poly& poly, sf::Color color = sf::Color::White)
        {
                sf::Vertex shape[C2_MAX_POLYGON_VERTS];

                for (int i = 0; i < poly.count; i++) {
                        shape[i] = sf::Vertex(sf::Vector2f(poly.verts[i].x, poly.verts[i].y), color);
                }
                // Connect last and first vertex
                shape[poly.count] = sf::Vertex(sf::Vector2f(poly.verts[0].x, poly.verts[0].y), color);

                mTarget.draw(shape, poly.count + 1, sf::LineStrip);
        }

        void draw(const c2Circle& body, sf::Color color = sf::Color::White)
        {
                sf::CircleShape shape(body.r);

                shape.setOrigin(body.r, body.r);
                shape.setPosition(body.p.x, body.p.y);
                shape.setFillColor(sf::Color::Transparent);
                shape.setOutlineColor(color);
                shape.setOutlineThickness(1.0f);

                mTarget.draw(shape);
        }

        void draw(const c2AABB& aabb, sf::Color color = sf::Color::White)
        {
                sf::RectangleShape shape(sf::Vector2f(aabb.max.x - aabb.min.x, aabb.max.y - aabb.min.y));

                shape.setPosition(aabb.min.x, aabb.min.y);
                shape.setFillColor(sf::Color::Transparent);
                shape.setOutlineColor(color);
                shape.setOutlineThickness(1.0f);

                mTarget.draw(shape);
        }

        void draw(const c2Ray& ray, sf::Color color = sf::Color::White)
        {
                sf::Vertex shape[] = {
                        sf::Vertex(sf::Vector2f(ray.p.x, ray.p.y), color),
                        sf::Vertex(sf::Vector2f(ray.p.x + (ray.d.x * ray.t), ray.p.y + (ray.d.y * ray.t)), color)
                };

                mTarget.draw(shape, 2, sf::Lines);
        }

        void draw(const c2Capsule& capsule, sf::Color color = sf::Color::White)
        {
                sf::CircleShape circle(capsule.r);
                circle.setOrigin(capsule.r, capsule.r);
                circle.setFillColor(sf::Color::Transparent);
                circle.setOutlineColor(color);
                circle.setOutlineThickness(1.0f);

                sf::Vertex topLine[] = {
                        sf::Vertex(sf::Vector2f(capsule.a.x, capsule.a.y + capsule.r), color),
                        sf::Vertex(sf::Vector2f(capsule.b.x, capsule.b.y + capsule.r), color)
                };

                sf::Vertex bottomLine[] = {
                        sf::Vertex(sf::Vector2f(capsule.a.x, capsule.a.y - capsule.r), color),
                        sf::Vertex(sf::Vector2f(capsule.b.x, capsule.b.y - capsule.r), color)
                };

                circle.setPosition(capsule.a.x, capsule.a.y);
                mTarget.draw(circle);
                circle.setPosition(capsule.b.x, capsule.b.y);
                mTarget.draw(circle);

                mTarget.draw(topLine, 2, sf::Lines);
                mTarget.draw(bottomLine, 2, sf::Lines);
        }

        void draw(const c2v& point1, const c2v& point2, sf::Color color = sf::Color::White)
        {
                sf::Vertex shape[] = {
                        sf::Vertex(sf::Vector2f(point1.x, point1.y), color),
                        sf::Vertex(sf::Vector2f(point2.x, point2.y), color)
                };

                mTarget.draw(shape, 2, sf::Lines);
        }

        void draw(const c2v& point, sf::Color color = sf::Color::White)
        {
                sf::Vertex shape[] = {
                        sf::Vertex(sf::Vector2f(point.x, point.y), color)
                };

                mTarget.draw(shape, 1, sf::Points);
        }

        void draw(const c2Manifold& manifold, sf::Color color = sf::Color::White)
        {
                for (int i = 0; i < manifold.count; ++i) {
                        c2v n = manifold.normal;
                        c2v p = manifold.contact_points[i];
                        float d = manifold.depths[i];
                        n = c2Mulvs(n, d);

                        draw(p, c2Add(p, n));
                        draw(p, sf::Color::Red);
                }
        }

        void draw(const c2Raycast& cast, const c2Ray& ray, sf::Color color = sf::Color::White)
        {
                if (cast.t > 0) {
                        c2v impact = c2Impact(ray, cast.t);

                        draw(impact, c2Add(impact, c2Mulvs(cast.n, 10)));
                        draw(impact, sf::Color::Red);
                }
        }
};

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

#endif // _TINYC2_DEBUG_HPP
