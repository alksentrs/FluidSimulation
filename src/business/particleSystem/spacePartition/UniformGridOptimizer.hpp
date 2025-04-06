/*
 * UniformGridOptimizer.hpp
 *
 *  Created on: 29 de mar. de 2025
 *      Author: aleksander
 */

// UniformGridOptimizer.hpp
#ifndef BUSINESS_PARTICLESYSTEM_SPACEPARTITION_UNIFORMGRIDOPTIMIZER_HPP_
#define BUSINESS_PARTICLESYSTEM_SPACEPARTITION_UNIFORMGRIDOPTIMIZER_HPP_

#include <vector>
#include <limits>
#include <iostream>
#include "UniformGrid.hpp"

class UniformGridOptimizer {
public:
    UniformGridOptimizer(int samplesPerCapacity = 32, bool optimizing = true);

    void setUniformGrid(UniformGrid& uniformGrid);
    void update(float detectionTime);
    int getBestCellSize() const;
    void setOptimizing(bool optimizing);
    bool getOptimizing();

private:
    UniformGrid * uniformGrid;
    float currentCellSize;
    int direction;
    bool optimizing;

    float lastAvgTime;
    float accumulatedTime;
    int currentSampleCount;
    int samplesPerCapacity;
    float bestTime;
    float bestCellSize;
};

#endif /* BUSINESS_PARTICLESYSTEM_SPACEPARTITION_UniformGridOptimizer_HPP_ */
