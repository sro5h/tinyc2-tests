#include <SFML/Graphics.hpp>

class Tiny2cDebug {
private:
    sf::RenderTarget& mTarget;

public:
    Tiny2cDebug( sf::RenderTarget& target )
        : mTarget( target )
    {

    }

    void draw( const c2Poly& poly, sf::Color color = sf::Color::White ) {
        sf::Vertex shape[poly.count + 1];
        for( int i = 0; i < poly.count; i++ ) {
            shape[i] = sf::Vertex( sf::Vector2f( poly.verts[i].x, poly.verts[i].y ), color );
        }
        // Connect last and first vertex
        shape[poly.count] = sf::Vertex( sf::Vector2f( poly.verts[0].x, poly.verts[0].y ), color );
        mTarget.draw( shape, poly.count + 1, sf::LineStrip );
    }
    void draw( const c2Circle& body, sf::Color color = sf::Color::White ) {
        sf::CircleShape shape( body.r );
        shape.setOrigin( body.r, body.r );
        shape.setPosition( body.p.x, body.p.y );
        shape.setFillColor( sf::Color::Transparent );
        shape.setOutlineColor( color );
        shape.setOutlineThickness( 1.0f );
        mTarget.draw( shape );
    }

    void draw( const c2AABB& aabb, sf::Color color = sf::Color::White ) {
        sf::RectangleShape shape( sf::Vector2f( aabb.max.x - aabb.min.x, aabb.max.y - aabb.min.y ) );
        shape.setPosition( aabb.min.x, aabb.min.y );
        shape.setFillColor( sf::Color::Transparent );
        shape.setOutlineColor( color );
        shape.setOutlineThickness( 1.0f );
        mTarget.draw( shape );
    }

    void draw( const c2Ray& ray, sf::Color color = sf::Color::White ) {
        sf::Vertex shape[] = {
            sf::Vertex( sf::Vector2f( ray.p.x, ray.p.y ), color ),
            sf::Vertex( sf::Vector2f( ray.p.x + (ray.d.x * ray.t), ray.p.y + (ray.d.y * ray.t) ), color )
        };
        mTarget.draw( shape, 2, sf::Lines );
    }

    void draw( const c2v& point1, const c2v& point2, sf::Color color = sf::Color::White ) {
            sf::Vertex shape[] = {
                    sf::Vertex( sf::Vector2f( point1.x, point1.y ), color ),
                    sf::Vertex( sf::Vector2f( point2.x, point2.y ), color )
            };
            mTarget.draw( shape, 2, sf::Lines );
    }

    void draw( const c2v& point, sf::Color color = sf::Color::White ) {
        sf::Vertex shape[] = {
            sf::Vertex( sf::Vector2f( point.x, point.y ), color )
        };
        mTarget.draw( shape, 1, sf::Points );
    }

    void draw( const c2Manifold& manifold, sf::Color color = sf::Color::White ) {
            c2v normalScaled;

            normalScaled.x = manifold.normal.x * manifold.depths[0];
            normalScaled.y = manifold.normal.y * manifold.depths[0];

            if (manifold.count > 0) {
                    draw( manifold.contact_points[0], c2Add( manifold.contact_points[0], normalScaled));
                    draw( manifold.contact_points[0], sf::Color::Red );
            }

            if (manifold.count > 1) {
                    draw( manifold.contact_points[1], c2Add( manifold.contact_points[1], normalScaled));
                    draw( manifold.contact_points[1], sf::Color::Red );
            }
    }
};
