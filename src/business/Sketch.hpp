/*
 * Sketch.hpp
 *
 *  Created on: 18 de mar. de 2025
 *      Author: aleksander
 */

// Sketch.hpp
#ifndef BUSINESS_SKETCH_HPP_
#define BUSINESS_SKETCH_HPP_

#include <vector>
#include <utility>
#include <unordered_set>
#include <memory>
#include <SFML/Graphics.hpp>
#include "engine/ILogic.hpp"
#include "util/Vector2D.hpp"
#include "particleSystem/Particle.hpp"
#include "particleSystem/OutsideBox.hpp"
#include "particleSystem/CollisionDetector.hpp"
#include "particleSystem/spacePartition/QuadTree.hpp"
#include "particleSystem/spacePartition/UniformGrid.hpp"
#include "particleSystem/spacePartition/ISpacePartition.hpp"
#include "particleSystem/spacePartition/QuadTreeOptimizer.hpp"
#include "particleSystem/spacePartition/UniformGridOptimizer.hpp"


class Sketch : public ILogic {
public:
	Sketch();
	virtual ~Sketch();
	void init() override;
	void input(const sf::Event& event, sf::RenderWindow& window) override;
	void update(float dt) override;
	void draw(sf::RenderWindow& window) override;
	const char* getWindowName() const override;
	int getWidth() const override;
	int getHeight() const override;

private:
	const char* windowName = "Simulação em C++";
	int windowWidth = 450;
	int windowHeight = 280;

	Particle* particleSelected = nullptr;

	void updateSequentially(float dt);
	void updateParalell(float dt);

	std::vector<Particle> particles;
	OutsideBox box;
	QuadTreeOptimizer quadTreeOptimizer;
	UniformGridOptimizer uniformGridOptimizer;

	ISpacePartition* spacePartition = nullptr;
	std::vector<Particle*> foundShapes;
	CollisionDetector collisionDetector;

	sf::Vector2f mousePosition;
	bool mouseInSide = false;;
	float queryRadius = 20.f;
	bool queryShapeCircle = true;

	bool dragging = false;
	Vector2D dragOffset;

	bool usingQuadTree = false;
	std::unique_ptr<QuadTree> quadTree;
	std::unique_ptr<UniformGrid> uniformGrid;

	float detectionTimeMs = 0.f;
	sf::Font font;
	sf::Text debugText;

	int quadTreeCapacity = 4;
	float uniformGridCellSize = 8.f;
	bool configChanged = false;

	Vector2D gravity = Vector2D(0.f, 20.f);
	bool withGraity = false;
	bool parallel = false;
	bool collision = true;
	bool stoped = false;
	bool applyForce = true;
	int forceSignal = -1;
	float forceStreng = 300;
	float forceRadius = 30.f;

	void buildSpacePartition();
	void reBuildSpacePartition();
};

#endif /* BUSINESS_SKETCH_HPP_ */
