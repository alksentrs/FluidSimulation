/*
 * Entity.hpp
 *
 *  Created on: 26 de mar. de 2025
 *      Author: aleksander
 */

// Entity.hpp
#ifndef BUSINESS_PARTICLESYSTEM_ENTITY_HPP_
#define BUSINESS_PARTICLESYSTEM_ENTITY_HPP_

#include "util/Vector2D.hpp"
#include <cstdint>

class Entity {
protected:
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    float mass;

private:
    std::uint64_t id;
    static inline std::uint64_t currId = 0;

public:
    Entity();
    Entity(const Vector2D& pos);
    Entity(const Vector2D& pos, float mass);
    Entity(const Vector2D& pos, const Vector2D& vel);
    Entity(const Vector2D& pos, const Vector2D& vel, const Vector2D& acc, float mass = 1.0f);

    std::uint64_t getId() const;

    const Vector2D& getPosition() const;
    void setPosition(const Vector2D& pos);

    const Vector2D& getVelocity() const;
    virtual void setVelocity(const Vector2D& vel);
    virtual void setVelocity(float vx, float vy);

    const Vector2D& getAcceleration() const;
    void setAcceleration(const Vector2D& acc);
    void setAcceleration(float x, float y);
    void addAcceleration(const Vector2D& acc);
    void subAcceleration(const Vector2D& acc);

    float getMass() const;
    void setMass(float m);

    void applyForce(const Vector2D& force);
    void applyAcceleration(const Vector2D& a);

    virtual void update(float deltaTime) = 0;

    virtual float getLeft() const = 0;
    virtual float getRight() const = 0;
    virtual float getTop() const = 0;
    virtual float getBottom() const = 0;
};

#endif /* BUSINESS_PARTICLESYSTEM_ENTITY_HPP_ */
