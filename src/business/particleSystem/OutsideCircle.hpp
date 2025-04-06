/*
 * OutsideCircle.hpp
 *
 *  Created on: 27 de mar. de 2025
 *      Author: aleksander
 */

// OutsideCircle.hpp
#ifndef BUSINESS_PARTICLESYSTEM_OUTSIDECIRCLE_HPP_
#define BUSINESS_PARTICLESYSTEM_OUTSIDECIRCLE_HPP_

#include "OutsideEdge.hpp"
#include "Vector2D.hpp"
#include "Particle.hpp"
#include <SFML/Graphics.hpp>

class OutsideCircle : public OutsideEdge {
private:
    Vector2D position;
    float radius;

public:
    OutsideCircle(float x, float y, float radius);

    float getRadius() const;
    void setRadius(float r);

    void applyConstraint(Particle& particle) override;
    void draw(sf::RenderWindow& window) override;
};

#endif /* BUSINESS_PARTICLESYSTEM_OUTSIDECIRCLE_HPP_ */
