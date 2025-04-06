/*
 * CollisionDetector.cpp
 *
 *  Created on: 27 de mar. de 2025
 *      Author: aleksander
 */

#include "CollisionDetector.hpp"
#include "Circle.hpp"

std::size_t CollisionDetector::PairHash::operator()(const std::pair<Particle*, Particle*>& pair) const {
    auto h1 = std::hash<Particle*>{}(pair.first);
    auto h2 = std::hash<Particle*>{}(pair.second);
    return h1 ^ h2;
}

bool CollisionDetector::alreadyChecked(Particle* a, Particle* b) {
    if (a > b) std::swap(a, b);
    auto p = std::make_pair(a, b);
    return !checkedPairs.insert(p).second;
}

void CollisionDetector::detect(std::vector<Particle>& particles, ISpacePartition& space) {
    checkedPairs.clear();
    for (auto& p : particles) {
        Circle range(p.getPosition().x, p.getPosition().y, p.getRadius());
        std::vector<Particle*> nearby;
        space.query(range, nearby);

        for (auto& pt : nearby) {
            if (&p == pt || alreadyChecked(&p, pt)) continue;

            if (p.isCollision(*pt)) {
                p.applyCollision(*pt);
            }
        }
    }
}



