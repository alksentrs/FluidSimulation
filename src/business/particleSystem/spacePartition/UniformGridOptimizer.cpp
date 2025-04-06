/*
 * QuadTreeOptimizer.cpp
 *
 *  Created on: 29 de mar. de 2025
 *      Author: aleksander
 */

// QuadTreeOptimizer.cpp
#include "UniformGridOptimizer.hpp"
#include <limits>

UniformGridOptimizer::UniformGridOptimizer(int samplesPerCapacity, bool optimizing)
    : uniformGrid(nullptr), currentCellSize(5), direction(-1), lastAvgTime(std::numeric_limits<float>::max()), bestCellSize(50) {
	this->optimizing = optimizing;
	accumulatedTime = 0;
	currentSampleCount = 0;
	this->samplesPerCapacity = samplesPerCapacity;
}

void UniformGridOptimizer::setUniformGrid(UniformGrid& uniformGridRef) {
	uniformGrid = &uniformGridRef;
	currentCellSize = uniformGrid->getCellSize();
	bestCellSize = currentCellSize;
}

void UniformGridOptimizer::setOptimizing(bool optimizing) {
	this->optimizing = optimizing;
}

bool UniformGridOptimizer::getOptimizing() {
	return optimizing;
}

void UniformGridOptimizer::update(float detectionTime) {
	if (!optimizing || !uniformGrid) return;

	accumulatedTime += detectionTime;
	currentSampleCount++;

	if (currentSampleCount >= samplesPerCapacity) {
		float avg = accumulatedTime / static_cast<float>(samplesPerCapacity);

		if (avg < lastAvgTime) {
			lastAvgTime = avg;
			bestCellSize = currentCellSize;
		} else {
		    direction *= -1; // Inverte a direção se piorou
		}
		currentCellSize = std::max(2.f, currentCellSize + direction);
		uniformGrid->setCellSize(currentCellSize);
		currentCellSize = uniformGrid->getCellSize();

	    accumulatedTime = 0;
	    currentSampleCount = 0;

		//std::cout << "Tamanho da célula UniformGrid: " << currentCellSize << "    Tempo médio: " <<  avg << std::endl;
	}
}

int UniformGridOptimizer::getBestCellSize() const {
    return bestCellSize;
}




