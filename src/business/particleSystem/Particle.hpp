/*
 * Particle.hpp
 *
 *  Created on: 26 de mar. de 2025
 *      Author: aleksander
 */

// Particle.hpp
#ifndef BUSINESS_PARTICLESYSTEM_PARTICLE_HPP_
#define BUSINESS_PARTICLESYSTEM_PARTICLE_HPP_

#include "Entity.hpp"
#include "Circle.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

class Particle : public Entity {
public:

private:
    float radius;
    float radiusScale = 1.f;
    float deltaTime;
    float elasticity;
    int collided;
    bool highlighted;
    float maxSpeed = 50.f;
    float speedDecay = 0.9995f;
    float viscosityStrenght = 50.f;
    float smoothingRadiusNormalized;
    float smoothingRadius;
    float density = 1;
    float targetDensity;
    float pressureMultiply;
    Vector2D pressureVector = Vector2D::zero();
    float pressure;
    Vector2D predictedPosition = Vector2D::zero();
    bool drawVectors = false;
    bool selectedDebbug;
    float kenerlSize = 20.f;

public:
    Particle(const Vector2D& pos, float radius);

    float getRadius() const;
    void setRadius(float r);

    void setRadiusScale(float rs);

    float getHighlighted() const;
    void setHighlighted(float h);

    float getElasticity() const;
    void setElasticity(float e);

    int getCollided() const;
    void setCollided(int c);

    bool getSelectedDebbug() const;
    void setSelectedDebbug(bool sd);

    void setMaxSpeed(float ms);
    void setSpeedDecay(float sd);
    void setViscosityStrenght(float vs);
    float getViscosityStrenght();

    void setDeltaTime(float dt);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    float getLeft() const override;
    float getRight() const override;
    float getTop() const override;
    float getBottom() const override;

    bool isCollision(const Particle& other) const;
    bool applyCollision(Particle& other);

    std::string toString() const;

    Vector2D getPredictedPosition();
    void setTargetDensity(float td);
    void setPressureMultiply(float pm);
    float getDensity() const;
    void setDensity(float d);
    float getProperty() const;
    void setProperty(float p);
    float getSmoothingRadius() const;
    void setSmoothingRadius(float s);
    float getPressure() const;
    Vector2D getPressureVector() const;
    float smoothingKernel(float distance);
    float smoothingKernelDerivative(float distance);
    float smoothingKernel2(float distance);
    float smoothingKernelDerivative2(float distance);
    float calculateDensity(const std::vector<Particle*> particles);
    float density2pressure();
    Vector2D calculatePressure(const std::vector<Particle*> particles);
    Vector2D calculateViscosityForce(const std::vector<Particle*> particles);
    Vector2D interactionForce(Vector2D forcePosition, float force, float radius);

private:
    void resolveEqualMassCollision(Particle& other, const Vector2D& unitAxis, float overlap, float impulse);
    void resolveUnequalMassCollision(Particle& other, const Vector2D& unitAxis, float overlap, float impulse);
};


#endif /* BUSINESS_PARTICLESYSTEM_PARTICLE_HPP_ */
