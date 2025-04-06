/*
 * QuadTreeOptimizer.cpp
 *
 *  Created on: 29 de mar. de 2025
 *      Author: aleksander
 */

// QuadTreeOptimizer.cpp
#include "QuadTreeOptimizer.hpp"
#include <limits>

QuadTreeOptimizer::QuadTreeOptimizer(int samplesPerCapacity, bool optimizing)
    : quadTree(nullptr), currentCapacity(4), direction(-1), lastAvgTime(std::numeric_limits<float>::max()), bestCapacity(4) {
	this->optimizing = optimizing;
	accumulatedTime = 0;
	currentSampleCount = 0;
	this->samplesPerCapacity = samplesPerCapacity;
}

void QuadTreeOptimizer::setQuadTree(QuadTree& quadTreeRef) {
    quadTree = &quadTreeRef;
    currentCapacity = quadTree->getCapacity();
    bestCapacity = currentCapacity;
}

void QuadTreeOptimizer::setOptimizing(bool optimizing) {
	this->optimizing = optimizing;
}

bool QuadTreeOptimizer::getOptimizing() {
	return optimizing;
}

void QuadTreeOptimizer::update(float detectionTime) {
	if (!optimizing || !quadTree) return;

	accumulatedTime += detectionTime;
	currentSampleCount++;

	if (currentSampleCount >= samplesPerCapacity) {
		float avg = accumulatedTime / static_cast<float>(samplesPerCapacity);

		if (avg < lastAvgTime) {
			lastAvgTime = avg;
		    bestCapacity = currentCapacity;
		} else {
		    direction *= -1; // Inverte a direção se piorou
		}
	    currentCapacity = std::max(1, currentCapacity + direction);
	    quadTree->setCapacity(currentCapacity);
	    currentCapacity = quadTree->getCapacity();

	    accumulatedTime = 0;
	    currentSampleCount = 0;
	}
}

int QuadTreeOptimizer::getBestCapacity() const {
    return bestCapacity;
}




