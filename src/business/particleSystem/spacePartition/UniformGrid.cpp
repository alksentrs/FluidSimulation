/*
 * UniformGrid.cpp
 *
 *  Created on: 27 de mar. de 2025
 *      Author: aleksander
 */

// UniformGrid.cpp
#include "UniformGrid.hpp"
#include <cmath>

UniformGrid::UniformGrid(float cellSize)
    : cellSize(cellSize) {
}

void UniformGrid::clear() {
    grid.clear();
}

void UniformGrid::setCellSize(float cellSize) {
	this->cellSize = cellSize;
}

float UniformGrid::getCellSize() {
	return cellSize;
}

std::pair<int, int> UniformGrid::getCellCoordinates(float x, float y) const {
    int col = static_cast<int>(x / cellSize);
    int row = static_cast<int>(y / cellSize);
    return {col, row};
}

bool UniformGrid::insert(Particle* particle) {
    auto coords = getCellCoordinates(particle->getPosition().x, particle->getPosition().y);
    grid[coords].push_back(particle);
    return true;
}

void UniformGrid::query(const Rectangle& range, std::vector<Particle*>& found) const {
    int startCol = static_cast<int>(range.getLeft() / cellSize);
    int endCol = static_cast<int>(range.getRight() / cellSize);
    int startRow = static_cast<int>(range.getBottom() / cellSize);
    int endRow = static_cast<int>(range.getTop() / cellSize);

    for (int col = startCol; col <= endCol; ++col) {
        for (int row = startRow; row <= endRow; ++row) {
            auto it = grid.find({col, row});
            if (it != grid.end()) {
                for (auto* p : it->second) {
                	Circle circle(p->getPosition().x, p->getPosition().y, p->getRadius());
                	if (range.intersects(circle)) {
                	    found.push_back(p);
                	}
                }
            }
        }
    }
}

void UniformGrid::query(const Circle& range, std::vector<Particle*>& found) const {
    int startCol = static_cast<int>((range.getX() - range.getRadius()) / cellSize);
    int endCol = static_cast<int>((range.getX() + range.getRadius()) / cellSize);
    int startRow = static_cast<int>((range.getY() - range.getRadius()) / cellSize);
    int endRow = static_cast<int>((range.getY() + range.getRadius()) / cellSize);

    for (int col = startCol; col <= endCol; ++col) {
        for (int row = startRow; row <= endRow; ++row) {
            auto it = grid.find({col, row});
            if (it != grid.end()) {
                for (auto* p : it->second) {
                	Circle circle(p->getPosition().x, p->getPosition().y, p->getRadius());
                	if (range.intersects(circle)) {
                	    found.push_back(p);
                	}
                }
            }
        }
    }
}

void UniformGrid::draw(sf::RenderWindow& window) const {
    for (const auto& cell : grid) {
        int col = cell.first.first;
        int row = cell.first.second;

        sf::RectangleShape rect(sf::Vector2f(cellSize, cellSize));
        rect.setPosition(col * cellSize, row * cellSize);
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::Yellow);
        rect.setOutlineThickness(0.4f);
        window.draw(rect);
    }
}
