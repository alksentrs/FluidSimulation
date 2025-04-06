/*
 * Rectangle.cpp
 *
 *  Created on: 27 de mar. de 2025
 *      Author: aleksander
 */

// Rectangle.cpp
#include "Rectangle.hpp"
#include "Circle.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>

Rectangle::Rectangle(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height) {}

float Rectangle::getX() const {
    return x;
}

float Rectangle::getY() const {
    return y;
}

float Rectangle::getWidth() const {
    return width;
}

float Rectangle::getHeight() const {
    return height;
}

float Rectangle::getLeft() const {
    return x;
}

float Rectangle::getRight() const {
    return x + width;
}

float Rectangle::getTop() const {
    return y + height;
}

float Rectangle::getBottom() const {
    return y;
}

bool Rectangle::intersects(const Rectangle& rect) const {
    return !(getRight() < rect.getLeft() || getLeft() > rect.getRight() ||
             getTop() < rect.getBottom() || getBottom() > rect.getTop());
}

bool Rectangle::intersects(const Circle& circle) const {
    float cx = circle.getX();
    float cy = circle.getY();
    float closestX = std::clamp(cx, getLeft(), getRight());
    float closestY = std::clamp(cy, getBottom(), getTop());

    float dx = cx - closestX;
    float dy = cy - closestY;

    return (dx * dx + dy * dy) <= (circle.getRadius() * circle.getRadius());
}

bool Rectangle::contains(const Vector2D& point) const {
    return (
        getLeft() <= point.x && point.x <= getRight() &&
        getBottom() <= point.y && point.y <= getTop()
    );
}

void Rectangle::draw(sf::RenderWindow& window) const {
    sf::RectangleShape rectShape(sf::Vector2f(width, height));
    rectShape.setPosition(x, y);
    rectShape.setFillColor(sf::Color::Transparent);
    rectShape.setOutlineColor(sf::Color::Red);
    rectShape.setOutlineThickness(1.f);
    window.draw(rectShape);
}



