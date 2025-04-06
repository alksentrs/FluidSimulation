/*
 * QuadTreeOptimizer.hpp
 *
 *  Created on: 29 de mar. de 2025
 *      Author: aleksander
 */

// QuadTreeOptimizer.hpp
#ifndef BUSINESS_PARTICLESYSTEM_SPACEPARTITION_QUADTREEOPTIMIZER_HPP_
#define BUSINESS_PARTICLESYSTEM_SPACEPARTITION_QUADTREEOPTIMIZER_HPP_

#include <vector>
#include <limits>
#include <iostream>
#include "QuadTree.hpp"

class QuadTreeOptimizer {
public:
    QuadTreeOptimizer(int samplesPerCapacity = 32, bool optimizing = true);

    void setQuadTree(QuadTree& quadTree);
    void update(float detectionTime);
    int getBestCapacity() const;
    void setOptimizing(bool optimizing);
    bool getOptimizing();

private:
    QuadTree * quadTree;
    int currentCapacity;
    int direction;
    bool optimizing;

    float lastAvgTime;
    float accumulatedTime;
    int currentSampleCount;
    int samplesPerCapacity;
    int bestCapacity;
};

#endif /* BUSINESS_PARTICLESYSTEM_SPACEPARTITION_QUADTREEOPTIMIZER_HPP_ */
