/*
 * QuadTreePoint.hpp
 *
 *  Created on: 27 de mar. de 2025
 *      Author: aleksander
 */

// QuadTreePoint.hpp
#ifndef BUSINESS_PARTICLESYSTEM_SPACEPARTITION_QUADTREEPOINT_HPP_
#define BUSINESS_PARTICLESYSTEM_SPACEPARTITION_QUADTREEPOINT_HPP_

#include "Circle.hpp"

class QuadTreePoint {
public:
    Circle shape;
    void* data;

    QuadTreePoint(const Circle& shape, void* data)
        : shape(shape), data(data) {}
};

#endif /* BUSINESS_PARTICLESYSTEM_SPACEPARTITION_QUADTREEPOINT_HPP_ */
