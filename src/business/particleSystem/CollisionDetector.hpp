/*
 * CollisionDetector.hpp
 *
 *  Created on: 27 de mar. de 2025
 *      Author: aleksander
 */

#ifndef BUSINESS_PARTICLESYSTEM_COLLISIONDETECTOR_HPP_
#define BUSINESS_PARTICLESYSTEM_COLLISIONDETECTOR_HPP_

#include "Particle.hpp"
#include <unordered_set>
#include "spacePartition/QuadTree.hpp"

class CollisionDetector {
public:
	void detect(std::vector<Particle>& particles, ISpacePartition& spacePartition);

private:
    struct PairHash {
        std::size_t operator()(const std::pair<Particle*, Particle*>& pair) const;
    };

    std::unordered_set<std::pair<Particle*, Particle*>, PairHash> checkedPairs;

    bool alreadyChecked(Particle* a, Particle* b);
};

#endif /* BUSINESS_PARTICLESYSTEM_COLLISIONDETECTOR_HPP_ */
