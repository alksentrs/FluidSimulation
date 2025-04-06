/*
 * Entity.cpp
 *
 *  Created on: 26 de mar. de 2025
 *      Author: aleksander
 */

// Entity.cpp
#include "Entity.hpp"

Entity::Entity()
    : position(), velocity(), acceleration(), mass(1.0f), id(++currId) {}

Entity::Entity(const Vector2D& pos)
    : position(pos), velocity(), acceleration(), mass(1.0f), id(++currId) {}

Entity::Entity(const Vector2D& pos, float mass)
    : position(pos), velocity(), acceleration(), mass(mass), id(++currId) {}

Entity::Entity(const Vector2D& pos, const Vector2D& vel)
    : position(pos), velocity(vel), acceleration(), mass(1.0f), id(++currId) {}

Entity::Entity(const Vector2D& pos, const Vector2D& vel, const Vector2D& acc, float mass)
    : position(pos), velocity(vel), acceleration(acc), mass(mass), id(++currId) {}

std::uint64_t Entity::getId() const {
    return id;
}

const Vector2D& Entity::getPosition() const {
    return position;
}

void Entity::setPosition(const Vector2D& pos) {
    position = pos;
}

const Vector2D& Entity::getVelocity() const {
    return velocity;
}

void Entity::setVelocity(const Vector2D& vel) {
    velocity = vel;
}

void Entity::setVelocity(float x, float y) {
    velocity = Vector2D(x, y);
}

const Vector2D& Entity::getAcceleration() const {
    return acceleration;
}

void Entity::setAcceleration(const Vector2D& acc) {
    acceleration = acc;
}

void Entity::setAcceleration(float x, float y) {
    acceleration = Vector2D(x, y);
}

void Entity::addAcceleration(const Vector2D& acc) {
    acceleration += acc;
}

void Entity::subAcceleration(const Vector2D& acc) {
    acceleration -= acc;
}

float Entity::getMass() const {
    return mass;
}

void Entity::setMass(float m) {
    mass = m;
}

void Entity::applyForce(const Vector2D& force) {
    acceleration.addSelf(force.divide(mass));
}

void Entity::applyAcceleration(const Vector2D& a) {
    acceleration.addSelf(a);
}



