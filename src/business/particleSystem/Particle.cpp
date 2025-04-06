/*
 * Particle.cpp
 *
 *  Created on: 26 de mar. de 2025
 *      Author: aleksander
 */

// Particle.cpp
#include "Particle.hpp"
#include "util/Vector2D.hpp"
#include <cmath>
#include <iostream>
#include <random>
#define _USE_MATH_DEFINES

Particle::Particle(const Vector2D& pos, float radius)
    : Entity(pos), radius(radius), deltaTime(0.f), elasticity(0.999999f), collided(0) {
	predictedPosition.setLocation(pos);
}

float Particle::getRadius() const {
    return radius;
}

void Particle::setRadius(float r) {
    radius = r;
}

float Particle::getHighlighted() const {
    return highlighted;
}

void Particle::setHighlighted(float h) {
	highlighted = h;
}

float Particle::getElasticity() const {
    return elasticity;
}

void Particle::setElasticity(float e) {
    elasticity = e;
}

int Particle::getCollided() const {
    return collided;
}

void Particle::setCollided(int c) {
    collided = c;
}

void Particle::setDeltaTime(float dt) {
    deltaTime = dt;
}

Vector2D Particle::getPredictedPosition() {
	return predictedPosition;
}

void Particle::setViscosityStrenght(float vs) {
	viscosityStrenght = vs;
}

float Particle::getViscosityStrenght() {
	return viscosityStrenght;
}

void Particle::update(float deltaTime) {
    this->deltaTime = deltaTime;
    velocity.addSelf(acceleration.scale(deltaTime));
    if (velocity.isNan()) velocity.setLocation(0.f,0.f);
    velocity.setMagnitude(maxSpeed);
    Vector2D deltaPosition = velocity.add(velocity).scale(deltaTime);
    position.addSelf(deltaPosition);
    predictedPosition = position.add(deltaPosition);
    acceleration.scaleSelf(0.f);
    velocity.scaleSelf(speedDecay);
    if (collided > 0) collided--;
}

void Particle::draw(sf::RenderWindow& window) {
	sf::CircleShape shape(radius);
	shape.setOrigin(radius, radius);
	shape.setPosition(position.toSFML());

	// Cor baseada na velocidade (azul → vermelho)
	float speed = velocity.length();
	float clampedSpeed = std::min(speed, maxSpeed);
	float t = clampedSpeed / maxSpeed;

	sf::Uint8 red = static_cast<sf::Uint8>(255 * t);
	sf::Uint8 blue = static_cast<sf::Uint8>(255 * (1.f - t));
	sf::Color dynamicColor(red, 0, blue);
	shape.setFillColor(dynamicColor);

	if (highlighted) {
       shape.setFillColor(sf::Color::White);
	}


	if (selectedDebbug) {
		sf::CircleShape shape3(radius);
			shape3.setOrigin(radius, radius);
			shape3.setPosition(predictedPosition.toSFML());
			shape3.setFillColor(sf::Color::Cyan);
			window.draw(shape3);

		shape.setFillColor(sf::Color::Magenta);

		sf::CircleShape shape2(smoothingRadius);
				shape2.setOrigin(smoothingRadius, smoothingRadius);
				shape2.setFillColor(sf::Color::Transparent);             // sem preenchimento
				shape2.setOutlineThickness(1.f);                         // espessura da borda
				shape2.setOutlineColor(sf::Color::Magenta);
				shape2.setPosition(position.toSFML());
				window.draw(shape2);
				shape2.setFillColor(sf::Color::Magenta);

		sf::Vertex pressureLine[] = {
		            sf::Vertex(position.toSFML(), sf::Color::Yellow),
		            sf::Vertex((position - pressureVector*10.f).toSFML(), sf::Color::Yellow)
		        };
		        window.draw(pressureLine, 2, sf::Lines);
	}

	window.draw(shape);

    if (drawVectors) {
    // Desenhar o pressureVector como linha amarela
        sf::Vertex pressureLine[] = {
            sf::Vertex(position.toSFML(), sf::Color::Yellow),
            sf::Vertex((position - pressureVector*100).toSFML(), sf::Color::Yellow)
        };
        window.draw(pressureLine, 2, sf::Lines);

        /*// Desenhar o velocity como linha verde
        sf::Vertex velocityLine[] = {
            sf::Vertex(position.toSFML(), sf::Color::Green),
            sf::Vertex((position - velocity).toSFML(), sf::Color::Green)
        };
        window.draw(velocityLine, 2, sf::Lines);*/
    }
}

void Particle::setMaxSpeed(float ms) {
	maxSpeed = ms;
}

void Particle::setSpeedDecay(float sd) {
	speedDecay = sd;
}

float Particle::getLeft() const {
    return position.x - radius;
}

float Particle::getRight() const {
    return position.x + radius;
}

float Particle::getTop() const {
    return position.y + radius;
}

float Particle::getBottom() const {
    return position.y - radius;
}

bool Particle::getSelectedDebbug() const {
	return selectedDebbug;
}

void Particle::setSelectedDebbug(bool sd) {
	selectedDebbug = sd;
}

bool Particle::isCollision(const Particle& other) const {
    return (position - other.position).length() <= (radius + other.radius);
}

bool Particle::applyCollision(Particle& other) {
    Vector2D axis = position - other.position;
    float dist = axis.length();
    float overlap = dist - (radius + other.radius);
    if (overlap >= 0) return false;

    collided = 255;
    other.setCollided(255);

    Vector2D unitAxis = axis / dist;
    Vector2D velDiff = velocity - other.velocity;
    float impulse = velDiff.dotProduct(unitAxis);

    if (mass == other.getMass()) {
        resolveEqualMassCollision(other, unitAxis, overlap, impulse);
    } else {
        resolveUnequalMassCollision(other, unitAxis, overlap, impulse);
    }
    return true;
}

void Particle::resolveEqualMassCollision(Particle& other, const Vector2D& unitAxis, float overlap, float impulse) {
    Vector2D displacement = unitAxis * (overlap / 2.0f);
    position -= displacement;
    other.position += displacement;

    Vector2D impulseVec = unitAxis * (elasticity * impulse);
    velocity -= impulseVec;
    other.velocity += impulseVec;
}

void Particle::resolveUnequalMassCollision(Particle& other, const Vector2D& unitAxis, float overlap, float impulse) {
    float m1 = other.getMass() / (mass + other.getMass());
    float m2 = mass / (mass + other.getMass());

    position -= unitAxis * (m1 * overlap);
    other.position += unitAxis * (m2 * overlap);

    velocity -= unitAxis * (2.0f * elasticity * m1 * impulse);
    other.velocity += unitAxis * (2.0f * elasticity * m2 * impulse);
}

std::string Particle::toString() const {
    std::ostringstream oss;
    oss << "{\"x\": " << position.x << ", \"y\": " << position.y << ", \"radius\": " << radius << "}";
    return oss.str();
}


float Particle::getDensity() const {
    return density;
}

void Particle::setDensity(float d) {
    density = d;
}

float Particle::getSmoothingRadius() const {
    return smoothingRadius;
}

void Particle::setRadiusScale(float rs) {
	radiusScale = rs;
}

void Particle::setSmoothingRadius(float s) {
	smoothingRadius = s;
	smoothingRadiusNormalized = s / radiusScale;
}

void Particle::setTargetDensity(float td) {
	targetDensity = td;
}

void Particle::setPressureMultiply(float pm) {
	pressureMultiply = pm;
}

float Particle::smoothingKernel(float distance) {
	if (distance >= smoothingRadiusNormalized) return 0;
	static const float volume = M_PI * std::pow(smoothingRadiusNormalized, 4) / 6.f;
	float diff = (smoothingRadiusNormalized-distance);
	return std::pow(diff, 2) / volume;
}

float Particle::smoothingKernelDerivative(float distance) {
	if (distance >= smoothingRadiusNormalized) return 0;
	float diff =  (distance-smoothingRadiusNormalized);
	static const float scale = 12.f / ( M_PI * std::pow(smoothingRadiusNormalized, 4) );
	return scale * diff;
}

float Particle::smoothingKernel2(float distance) {
	if (distance >= smoothingRadiusNormalized) return 0;
	static const float volume = M_PI * std::pow(smoothingRadiusNormalized, 8) / 4.f;
	float diff = (smoothingRadiusNormalized * smoothingRadiusNormalized - distance * distance);
	return std::pow(diff, 3) / volume;
}

float Particle::smoothingKernelDerivative2(float distance) {
	float diff = (smoothingRadiusNormalized * smoothingRadiusNormalized - distance * distance);
	static const float scale = -24.f / ( M_PI * std::pow(smoothingRadiusNormalized, 8) );
	return scale * distance * diff * diff ;
}

float Particle::calculateDensity(const std::vector<Particle*> particles) {
	density = 0;

	int count =0;
	float inc = (particles.size() <= kenerlSize) ? 1.0f : static_cast<float>(particles.size()) / kenerlSize;
	for (float i = 0.0f; i < static_cast<float>(particles.size()); i += inc) {
		std::size_t idx = std::min(static_cast<std::size_t>(i), particles.size() - 1);
		Particle* p = particles[idx];
	    float distance = getPredictedPosition().distance(p->getPredictedPosition()) / radiusScale;
	    float influence = inc * smoothingKernel(distance);
	    density += p->getMass() * influence;
	    if (selectedDebbug) p->setHighlighted(true);
	    count++;
	}
	if (selectedDebbug) {
			std::cout << particles.size() << " " << count << std::endl;
		}
	return density;
}

float Particle::density2pressure() {
	//pressure = std::max(0.f, density - targetDensity) * pressureMultiply;
	pressure = (density - targetDensity) * pressureMultiply;
	if (selectedDebbug) {
		std::cout << "density " << targetDensity << " " << density << std::endl;
		std::cout << "pressure scalar " << pressure << std::endl;
	}
	return pressure;
}

Vector2D Particle::calculatePressure(const std::vector<Particle*> particles) {
	pressureVector.scaleSelf(0.f);
	float pressure1 = density2pressure();
	float inc = (particles.size() <= kenerlSize) ? 1.0f : static_cast<float>(particles.size()) / kenerlSize;
	for (float i = 0.0f; i < static_cast<float>(particles.size()); i += inc) {
		std::size_t idx = std::min(static_cast<std::size_t>(i), particles.size() - 1);
		Particle* p = particles[idx];
		if (getId() == p->getId()) continue;
		Vector2D diff = p->getPredictedPosition().subtract(getPredictedPosition());
		float slope = smoothingKernelDerivative(diff.length()/radiusScale);
		Vector2D direction;
		if (diff.length() != 0) {
			direction = diff.normalized();
		} else {
			direction = Vector2D::ramdon();
		}
		float  sheredPressure = (pressure1 + p->getPressure())/2.f;
		//float  sheredPressure2 = (density2pressure() + p->density2pressure())/2.f;
		if (p->getDensity() != 0) {
			pressureVector.addSelf(direction.scale(inc * sheredPressure * slope * p->getMass() / p->getDensity()));
		}
		//std::cout << "press " << sheredPressure -sheredPressure2 << std::endl;
	}
	if (selectedDebbug) {
				std::cout << "pressure vector " << pressureVector.length() << std::endl;
			}
	return pressureVector;
}

Vector2D Particle::calculateViscosityForce(const std::vector<Particle*> particles) {
	Vector2D force = Vector2D::zero();
	float inc = (particles.size() <= kenerlSize) ? 1.0f : static_cast<float>(particles.size()) / kenerlSize;
	for (float i = 0.0f; i < static_cast<float>(particles.size()); i += inc) {
		std::size_t idx = std::min(static_cast<std::size_t>(i), particles.size() - 1);
		Particle* p = particles[idx];
		if (getId() == p->getId()) continue;
		Vector2D diff = p->getPredictedPosition().subtract(getPredictedPosition());
		float influence = smoothingKernel2(diff.length()/radiusScale);
		force.addSelf(p->getVelocity().subtract(velocity).scale(inc*influence));
	}
	return force.scale(viscosityStrenght);
}

Vector2D Particle::interactionForce(Vector2D forcePosition, float force, float radius) {
	Vector2D diff = forcePosition.subtract(position);
	float dist = diff.length();
	Vector2D direction = diff.normalized();
	float centreT = 1.f - dist/radius;
	if (centreT <0) return Vector2D(0,0);
	Vector2D interactionForce = direction.scale(force).subtract(velocity).scale(centreT);
	return interactionForce;
}

float Particle::getPressure() const {
	return pressure;
}

Vector2D Particle::getPressureVector() const {
	return pressureVector;
}


