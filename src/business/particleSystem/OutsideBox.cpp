/*
 * OutsideBox.cpp
 *
 *  Created on: 27 de mar. de 2025
 *      Author: aleksander
 */

// OutsideBox.cpp
#include "OutsideBox.hpp"
#include <limits>

OutsideBox::OutsideBox(float x, float y, float width, float height)
    : position(x, y), width(width), height(height) {}

float OutsideBox::getLeft() const {
    return position.x;
}

float OutsideBox::getRight() const {
    return position.x + width;
}

float OutsideBox::getTop() const {
    return position.y + height;
}

float OutsideBox::getBottom() const {
    return position.y;
}

float OutsideBox::getWidth() const {
    return width;
}

void OutsideBox::setWidth(float w) {
    width = w;
}

float OutsideBox::getHeight() const {
    return height;
}

void OutsideBox::setHeight(float h) {
    height = h;
}

void OutsideBox::applyConstraint(Particle& particle) {
    const float eps = std::numeric_limits<float>::epsilon();

    if (particle.getBottom() <= getBottom()) {
        particle.setPosition(Vector2D(particle.getPosition().x, getBottom() + particle.getRadius() + eps));
        particle.setVelocity(particle.getVelocity().x, -particle.getVelocity().y);
        // particle.setInfinityMassDirection(Vector2D(0, -1)); // opcional
    }
    if (particle.getTop() >= getTop()) {
        particle.setPosition(Vector2D(particle.getPosition().x, getTop() - particle.getRadius() - eps));
        particle.setVelocity(particle.getVelocity().x, -particle.getVelocity().y);
        // particle.setInfinityMassDirection(Vector2D(0, 1));
    }
    if (particle.getLeft() <= getLeft()) {
        particle.setPosition(Vector2D(getLeft() + particle.getRadius() + eps, particle.getPosition().y));
        particle.setVelocity(-particle.getVelocity().x, particle.getVelocity().y);
        // particle.setInfinityMassDirection(Vector2D(-1, 0));
    }
    if (particle.getRight() >= getRight()) {
        particle.setPosition(Vector2D(getRight() - particle.getRadius() - eps, particle.getPosition().y));
        particle.setVelocity(-particle.getVelocity().x, particle.getVelocity().y);
        // particle.setInfinityMassDirection(Vector2D(1, 0));
    }
}

void OutsideBox::draw(sf::RenderWindow& window) {
    sf::RectangleShape box(sf::Vector2f(width, height));
    box.setPosition(position.toSFML());
    box.setFillColor(sf::Color(50, 50, 50)); // cor escura
    window.draw(box);
}



