/*
 * QuadTree.cpp
 *
 *  Created on: 27 de mar. de 2025
 *      Author: aleksander
 */

// QuadTree.cpp
#include "QuadTree.hpp"

QuadTree::QuadTree(const Rectangle& boundary, int capacity)
    : boundary(boundary), capacity(capacity) {}

void QuadTree::clear() {
    points.clear();
    if (divided) {
        northeast->clear();
        northwest->clear();
        southeast->clear();
        southwest->clear();
        northeast.reset();
        northwest.reset();
        southeast.reset();
        southwest.reset();
        divided = false;
    }
}

void QuadTree::setCapacity(int capacity) {
	this->capacity = std::max(minCapacity, capacity);
}

int QuadTree::getCapacity() {
	return this->capacity;
}

bool QuadTree::insert(Particle* particle) {
    Circle area(particle->getPosition().x, particle->getPosition().y, particle->getRadius());
    if (!boundary.intersects(area)) return false;

    if (static_cast<int>(points.size()) < capacity) {
    	points.push_back(QuadTreePoint(area, static_cast<void*>(particle)));
        return true;
    }

    if (!divided) subdivide();

    bool inNortheast = northeast->insert(particle);
    bool inNortwest  = northwest->insert(particle);
    bool inSoutheast = southeast->insert(particle);
    bool inSouthwest = southwest->insert(particle);

    return inNortheast || inNortwest ||inSoutheast || inSouthwest;
}

void QuadTree::subdivide() {
    float x = boundary.getX();
    float y = boundary.getY();
    float w = boundary.getWidth() / 2.f;
    float h = boundary.getHeight() / 2.f;

    northeast = std::make_unique<QuadTree>(Rectangle(x + w, y, w, h), capacity);
    northwest = std::make_unique<QuadTree>(Rectangle(x, y, w, h), capacity);
    southeast = std::make_unique<QuadTree>(Rectangle(x + w, y + h, w, h), capacity);
    southwest = std::make_unique<QuadTree>(Rectangle(x, y + h, w, h), capacity);

    divided = true;
}

void QuadTree::query(const Rectangle& range, std::vector<Particle*>& found) const {
    if (!boundary.intersects(range)) return;

    for (const auto& point : points) {
    	if (point.shape.intersects(range)) {
    	    found.push_back(static_cast<Particle*>(point.data));
    	}
    }

    if (divided) {
        northeast->query(range, found);
        northwest->query(range, found);
        southeast->query(range, found);
        southwest->query(range, found);
    }
}

void QuadTree::query(const Circle& range, std::vector<Particle*>& found) const {
    if (!boundary.intersects(range)) return;

    for (const auto& point : points) {
    	if (point.shape.intersects(range)) {
    	    found.push_back(static_cast<Particle*>(point.data));
    	}
    }

    if (divided) {
        northeast->query(range, found);
        northwest->query(range, found);
        southeast->query(range, found);
        southwest->query(range, found);
    }
}

void QuadTree::draw(sf::RenderWindow& window) const {
    sf::RectangleShape rect(sf::Vector2f(boundary.getWidth(), boundary.getHeight()));
    rect.setPosition(boundary.getLeft(), boundary.getBottom());
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Yellow);
    rect.setOutlineThickness(0.4f);
    window.draw(rect);

    if (divided) {
        northeast->draw(window);
        northwest->draw(window);
        southeast->draw(window);
        southwest->draw(window);
    }
}
