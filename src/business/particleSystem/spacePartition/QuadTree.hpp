/*
 * QuadTree.hpp
 *
 *  Created on: 27 de mar. de 2025
 *      Author: aleksander
 */

// QuadTree.hpp
#ifndef BUSINESS_PARTICLESYSTEM_SPACEPARTITION_QUADTREE_HPP_
#define BUSINESS_PARTICLESYSTEM_SPACEPARTITION_QUADTREE_HPP_

#include <vector>
#include <memory>
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Shape.hpp"
#include "Particle.hpp"
#include "QuadTreePoint.hpp"
#include "ISpacePartition.hpp"

class QuadTree : public ISpacePartition {
public:
    QuadTree(const Rectangle& boundary, int capacity = 8);
    void clear() override;
    bool insert(Particle* particle) override;
    void query(const Rectangle& range, std::vector<Particle*>& found) const override;
    void query(const Circle& range, std::vector<Particle*>& found) const override;
    void draw(sf::RenderWindow& window) const override;
    void setCapacity(int capacity);
    int getCapacity();

private:
    Rectangle boundary;
    int capacity;
    std::vector<QuadTreePoint> points;
    bool divided = false;
    int minCapacity = 1;

    std::unique_ptr<QuadTree> northeast;
    std::unique_ptr<QuadTree> northwest;
    std::unique_ptr<QuadTree> southeast;
    std::unique_ptr<QuadTree> southwest;

    void subdivide();
};

#endif /* BUSINESS_PARTICLESYSTEM_SPACEPARTITION_QUADTREE_HPP_ */
