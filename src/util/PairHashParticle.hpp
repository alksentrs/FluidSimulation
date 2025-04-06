/*
 * PairHashParticle.hpp
 *
 *  Created on: 27 de mar. de 2025
 *      Author: aleksander
 */

#ifndef UTIL_PAIRHASHPARTICLE_HPP_
#define UTIL_PAIRHASHPARTICLE_HPP_

#include "particleSystem/Particle.hpp"

// Estrutura de hash para pares de ponteiros
struct PairHashParticle {
    std::size_t operator()(const std::pair<Particle*, Particle*>& pair) const {
    return std::hash<Particle*>()(pair.first) ^ std::hash<Particle*>()(pair.second);
    }
};

#endif /* UTIL_PAIRHASHPARTICLE_HPP_ */
