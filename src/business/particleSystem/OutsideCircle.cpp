/*
 * OutsideCircle.cpp
 *
 *  Created on: 27 de mar. de 2025
 *      Author: aleksander
 */

// OutsideCircle.cpp
#include "OutsideCircle.hpp"
#include <cmath>

OutsideCircle::OutsideCircle(float x, float y, float radius)
    : position(x, y), radius(radius) {}

float OutsideCircle::getRadius() const {
    return radius;
}

void OutsideCircle::setRadius(float r) {
    radius = r;
}

void OutsideCircle::applyConstraint(Particle& particle) {
    Vector2D axis = particle.getPosition() - position;
    float distance = axis.length();

    if (distance > radius - particle.getRadius()) {
        Vector2D unitAxis = axis / distance;
        Vector2D newPos = position + unitAxis * (radius - particle.getRadius());
        particle.setPosition(newPos);

        float velAlongNormal = particle.getVelocity().dotProduct(unitAxis);
        particle.setVelocity(particle.getVelocity() - unitAxis * (1.8f * velAlongNormal));
    }
}

void OutsideCircle::draw(sf::RenderWindow& window) {
    sf::CircleShape circle(radius);
    circle.setPosition(position.toSFML() - sf::Vector2f(radius, radius));
    circle.setFillColor(sf::Color(50, 50, 50));
    window.draw(circle);
}



