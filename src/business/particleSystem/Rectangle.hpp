/*
 * Rectangle.hpp
 *
 *  Created on: 27 de mar. de 2025
 *      Author: aleksander
 */

// Rectangle.hpp
#ifndef BUSINESS_PARTICLESYSTEM_RECTANGLE_HPP_
#define BUSINESS_PARTICLESYSTEM_RECTANGLE_HPP_

#include "Shape.hpp"
#include "Vector2D.hpp"
#include "Circle.hpp"
#include <SFML/Graphics.hpp>

class Circle; // Forward declaration

class Rectangle : public Shape {
private:
    float x;
    float y;
    float width;
    float height;

public:
    Rectangle(float x, float y, float width, float height);

    float getX() const override;
    float getY() const override;
    float getWidth() const;
    float getHeight() const;

    float getLeft() const override;
    float getRight() const override;
    float getTop() const override;
    float getBottom() const override;

    bool intersects(const Rectangle& rect) const override;
    bool intersects(const Circle& circle) const override;
    bool contains(const Vector2D& point) const override;

    void draw(sf::RenderWindow& window) const override;
};

#endif /* BUSINESS_PARTICLESYSTEM_RECTANGLE_HPP_ */
