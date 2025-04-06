/*
 * ISpacePartition.hpp
 *
 *  Created on: 27 de mar. de 2025
 *      Author: aleksander
 */

// ISpacePartition.hpp
#ifndef BUSINESS_PARTICLESYSTEM_SPACEPARTITION_ISPACEPARTITION_HPP_
#define BUSINESS_PARTICLESYSTEM_SPACEPARTITION_ISPACEPARTITION_HPP_

#include <vector>
#include <SFML/Graphics.hpp>
#include "Particle.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"

class ISpacePartition {
public:
    virtual ~ISpacePartition() = default;

    virtual void clear() = 0;
    virtual bool insert(Particle* particle) = 0;
    virtual void query(const Rectangle& range, std::vector<Particle*>& found) const = 0;
    virtual void query(const Circle& range, std::vector<Particle*>& found) const = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
};

#endif /* BUSINESS_PARTICLESYSTEM_SPACEPARTITION_ISPACEPARTITION_HPP_ */
