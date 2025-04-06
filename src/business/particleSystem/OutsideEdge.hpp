/*
 * OutsideEdge.hpp
 *
 *  Created on: 27 de mar. de 2025
 *      Author: aleksander
 */

#ifndef BUSINESS_PARTICLESYSTEM_OUTSIDEEDGE_HPP_
#define BUSINESS_PARTICLESYSTEM_OUTSIDEEDGE_HPP_

#include "Particle.hpp"
#include <SFML/Graphics.hpp>

class OutsideEdge {
public:
    virtual ~OutsideEdge();

    // Aplica restrição física à partícula (ex: colisão com a borda)
    virtual void applyConstraint(Particle& particle) = 0;

    // Desenha a borda no renderizador da SFML
    virtual void draw(sf::RenderWindow& window) = 0;
};

#endif /* BUSINESS_PARTICLESYSTEM_OUTSIDEEDGE_HPP_ */
