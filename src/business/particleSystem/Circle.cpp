/*
 * Circle.cpp
 *
 *  Created on: 27 de mar. de 2025
 *      Author: aleksander
 */

// Circle.cpp
#include "Circle.hpp"
#include <cmath>

Circle::Circle(float x, float y, float radius)
    : x(x), y(y), radius(radius), radiusSquared(radius * radius) {}

Circle::Circle(Vector2D pos, float radius)
    : radius(radius), radiusSquared(radius * radius) {
	x = pos.getX();
	y = pos.getY();
}

float Circle::getX() const {
    return x;
}

float Circle::getY() const {
    return y;
}

float Circle::getLeft() const {
    return x - radius;
}

float Circle::getRight() const {
    return x + radius;
}

float Circle::getTop() const {
    return y + radius;
}

float Circle::getBottom() const {
    return y - radius;
}

float Circle::getRadius() const {
    return radius;
}

bool Circle::intersects(const Rectangle& rect) const {
    float xDist = std::abs(rect.getX() + rect.getWidth() / 2 - x);
    float yDist = std::abs(rect.getY() + rect.getHeight() / 2 - y);

    float w = rect.getWidth() / 2;
    float h = rect.getHeight() / 2;

    float edges = std::pow(xDist - w, 2) + std::pow(yDist - h, 2);

    if (xDist >= (radius + w) || yDist >= (radius + h)) return false;
    if (xDist < w || yDist < h) return true;
    return edges < radiusSquared;
}

bool Circle::intersects(const Circle& other) const {
    float dx = x - other.getX();
    float dy = y - other.getY();
    float totalRadius = radius + other.getRadius();
    return (dx * dx + dy * dy) <= (totalRadius * totalRadius);
}

bool Circle::contains(const Vector2D& point) const {
    float dx = point.x - x;
    float dy = point.y - y;
    return (dx * dx + dy * dy) < radiusSquared;
}

void Circle::draw(sf::RenderWindow& window) const {
    sf::CircleShape shape(radius);
    shape.setPosition(x - radius, y - radius);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Green);
    shape.setOutlineThickness(1.f);
    window.draw(shape);
}
