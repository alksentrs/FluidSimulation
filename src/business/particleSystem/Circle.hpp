/*
 * Circle.hpp
 *
 *  Created on: 27 de mar. de 2025
 *      Author: aleksander
 */

// Circle.hpp
#ifndef BUSINESS_PARTICLESYSTEM_CIRCLE_HPP_
#define BUSINESS_PARTICLESYSTEM_CIRCLE_HPP_

#include "Shape.hpp"
#include "Vector2D.hpp"
#include "Rectangle.hpp"
#include <SFML/Graphics.hpp>

class Rectangle; // Forward declaration

class Circle : public Shape {
private:
    float x;
    float y;
    float radius;
    float radiusSquared;

public:
    Circle(float x, float y, float radius);
    Circle(Vector2D pos, float radius);

    float getX() const override;
    float getY() const override;
    float getLeft() const override;
    float getRight() const override;
    float getTop() const override;
    float getBottom() const override;

    float getRadius() const;

    bool intersects(const Rectangle& rect) const override;
    bool intersects(const Circle& circle) const override;
    bool contains(const Vector2D& point) const override;

    void draw(sf::RenderWindow& window) const override;
};

#endif /* BUSINESS_PARTICLESYSTEM_CIRCLE_HPP_ */
