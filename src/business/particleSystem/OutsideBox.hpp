/*
 * OutsideBox.hpp
 *
 *  Created on: 27 de mar. de 2025
 *      Author: aleksander
 */

// OutsideBox.hpp
#ifndef BUSINESS_PARTICLESYSTEM_OUTSIDEBOX_HPP_
#define BUSINESS_PARTICLESYSTEM_OUTSIDEBOX_HPP_

#include "OutsideEdge.hpp"
#include "Vector2D.hpp"
#include "Particle.hpp"
#include <SFML/Graphics.hpp>

class OutsideBox : public OutsideEdge {
private:
    Vector2D position;
    float width;
    float height;

public:
    OutsideBox(float x, float y, float width, float height);

    float getLeft() const;
    float getRight() const;
    float getTop() const;
    float getBottom() const;

    float getWidth() const;
    void setWidth(float w);

    float getHeight() const;
    void setHeight(float h);

    void applyConstraint(Particle& particle) override;
    void draw(sf::RenderWindow& window) override;
};

#endif /* BUSINESS_PARTICLESYSTEM_OUTSIDEBOX_HPP_ */
