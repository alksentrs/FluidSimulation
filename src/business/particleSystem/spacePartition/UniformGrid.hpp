/*
 * UniformGrid.hpp
 *
 *  Created on: 27 de mar. de 2025
 *      Author: aleksander
 */

// UniformGrid.hpp
#ifndef BUSINESS_PARTICLESYSTEM_SPACEPARTITION_UNIFORMGRID_HPP_
#define BUSINESS_PARTICLESYSTEM_SPACEPARTITION_UNIFORMGRID_HPP_

#include <unordered_map>
#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>
#include "Particle.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "ISpacePartition.hpp"
#include "../../util/PairHash.hpp"

class UniformGrid : public ISpacePartition {
public:
    UniformGrid(float cellSize);
    void clear() override;
    bool insert(Particle* particle) override;
    void query(const Rectangle& range, std::vector<Particle*>& found) const override;
    void query(const Circle& range, std::vector<Particle*>& found) const override;
    void draw(sf::RenderWindow& window) const override;
    void setCellSize(float cellSize);
    float getCellSize();

private:
    float cellSize;
    std::unordered_map<std::pair<int, int>, std::vector<Particle*>, PairHash> grid;

    std::pair<int, int> getCellCoordinates(float x, float y) const;
};

#endif /* BUSINESS_PARTICLESYSTEM_SPACEPARTITION_UNIFORMGRID_HPP_ */
