/*
 * Shape.hpp
 *
 *  Created on: 27 de mar. de 2025
 *      Author: aleksander
 */

// Shape.hpp
#ifndef BUSINESS_PARTICLESYSTEM_SHAPE_HPP_
#define BUSINESS_PARTICLESYSTEM_SHAPE_HPP_

#include "Vector2D.hpp"
#include <SFML/Graphics.hpp>

class Rectangle; // Forward declaration
class Circle;    // Forward declaration

class Shape {
public:
    virtual ~Shape() = default;

    virtual bool intersects(const Rectangle& rectangle) const = 0;
    virtual bool intersects(const Circle& circle) const = 0;
    virtual bool contains(const Vector2D& point) const = 0;

    virtual float getX() const = 0;
    virtual float getY() const = 0;
    virtual float getLeft() const = 0;
    virtual float getRight() const = 0;
    virtual float getTop() const = 0;
    virtual float getBottom() const = 0;

    virtual void draw(sf::RenderWindow& window) const = 0;
};


#endif /* BUSINESS_PARTICLESYSTEM_SHAPE_HPP_ */
