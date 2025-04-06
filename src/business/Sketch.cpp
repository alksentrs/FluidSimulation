/*
 * Sketch.cpp
 *
 *  Created on: 18 de mar. de 2025
 *      Author: aleksander
 */

// Sketch.cpp
#include "Sketch.hpp"
#include <random>
#include <memory>
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <chrono>
#include <execution>
#include <vector>
#include <thread>
#include <omp.h>

Sketch::Sketch()
: box(0, 0, static_cast<float>(getWidth()), static_cast<float>(getHeight())),
  quadTreeOptimizer(64),
  uniformGridOptimizer(64) {

	float r = 110.f;

	withGraity = false;
	parallel = true;
	collision = true;
	stoped = true;
	usingQuadTree = false;

    std::mt19937 rng(std::random_device{}()); // @suppress("Type cannot be resolved")
    std::uniform_real_distribution<float> posX(r, getWidth()  - r); // @suppress("Type cannot be resolved")
    std::uniform_real_distribution<float> posY(r, getHeight() - r); // @suppress("Type cannot be resolved")
    std::uniform_real_distribution<float> radius(2.f, 8.f); // @suppress("Type cannot be resolved")
    std::uniform_real_distribution<float> vel(-200.f, 200.f); // @suppress("Type cannot be resolved")

    buildSpacePartition();

    if (!withGraity) {
    	gravity.scaleSelf(0);
    } else {
    	gravity.setLocation(0,10);
    }

    int nx = getWidth()/8, ny = getHeight()/9;
    float particleRadius = 1.2;
    float smoothingRadius = 32.f;
    float radiusScale = 1;
    float pressureMultiply = 1500.f;
    float mass = 1.f;
    float speedDecay = 0.9995f;
    float maxSpeed = 50;
    float viscosityStrenght = 50.f;

    float density = 0.6f*mass*nx*ny/(getWidth()*getHeight()/(radiusScale*radiusScale));

    for (int j = 0; j < ny; ++j) {
    	for (int i = 0; i < nx; ++i) {
    		Vector2D position(r+i*(getWidth()-2*r)/(nx-1), r+j*(getHeight()-2*r)/(ny-1));
    		//Vector2D position(posX(rng), posY(rng));
    		Particle p(position, particleRadius);
    		p.setRadiusScale(radiusScale);
    		p.setTargetDensity(density);
    		p.setDensity(density);
    		p.setPressureMultiply(pressureMultiply);
    		p.setSmoothingRadius(smoothingRadius);
    		p.setMass(mass);
    		p.setMaxSpeed(maxSpeed);
    		p.setSpeedDecay(speedDecay);
    		p.setViscosityStrenght(viscosityStrenght);
    		particles.push_back(p);
    		p.setSelectedDebbug(p.getId() == 180);
    	}
    }

    			/*Vector2D position(getWidth()/2.f, getHeight()/2.f);
        		Particle p(position, particleRadius);
        		p.setRadiusScale(radiusScale);
        		p.setTargetDensity(density);
        		p.setDensity(density);
        		p.setPressureMultiply(pressureMultiply);
        		p.setSmoothingRadius(smoothingRadius);
        		p.setMass(mass);
        		particles.push_back(p);

        						Vector2D position1(getWidth()*2.f/3.f, getHeight()/2.f);
        		        		Particle p1(position1, particleRadius);
        		        		p1.setRadiusScale(radiusScale);
        		        		p1.setTargetDensity(density);
        		        		p1.setDensity(density);
        		        		p1.setPressureMultiply(pressureMultiply);
        		        		p1.setSmoothingRadius(smoothingRadius);
        		        		p1.setMass(mass);
        		        		particles.push_back(p1);*/

    if (!font.loadFromFile("data/Arial.ttf")) {
        std::cerr << "Erro ao carregar fonte!" << std::endl;
    }

    debugText.setFont(font);
    debugText.setCharacterSize(14);
    debugText.setFillColor(sf::Color::White);
    debugText.setPosition(10.f, 10.f);
}
void Sketch::init() {

}

void Sketch::buildSpacePartition() {
	quadTree = std::make_unique<QuadTree>(Rectangle(0, 0, static_cast<float>(getWidth()), static_cast<float>(getHeight())),quadTreeCapacity);
	quadTreeOptimizer.setQuadTree(*quadTree.get());

	uniformGrid = std::make_unique<UniformGrid>(uniformGridCellSize);
	uniformGridOptimizer.setUniformGrid(*uniformGrid.get());

	if (usingQuadTree) {
	    spacePartition = static_cast<ISpacePartition*>(quadTree.get());
	} else {
	    spacePartition = static_cast<ISpacePartition*>(uniformGrid.get());
	}
	configChanged = false;
}

void Sketch::reBuildSpacePartition() {
	if (usingQuadTree) {
		(static_cast<QuadTree*>(spacePartition))->setCapacity(quadTreeCapacity);
		quadTreeCapacity = (static_cast<QuadTree*>(spacePartition))->getCapacity();
		std::cout << "Capacidade do QuadTree: " << quadTreeCapacity << std::endl;
	} else {
		(static_cast<UniformGrid*>(spacePartition))->setCellSize(uniformGridCellSize);
		uniformGridCellSize = (static_cast<UniformGrid*>(spacePartition))->getCellSize();
		std::cout << "CellSize do UniformGrid: " << uniformGridCellSize << std::endl;
	}
	configChanged = false;
}

void Sketch::input(const sf::Event& event, sf::RenderWindow& window) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::C) {
			collision = !collision;
		}
		if (event.key.code == sf::Keyboard::F) {
			forceSignal = -1*forceSignal;
		}
		if (event.key.code == sf::Keyboard::Space) {
			stoped = !stoped;
		}
		if (event.key.code == sf::Keyboard::G) {
			if (withGraity) {
				gravity.scaleSelf(0);
			} else {
				gravity.setLocation(0,10);
			}
			withGraity = !withGraity;
		}
		if (event.key.code == sf::Keyboard::P) {
			parallel = !parallel;
		}
		if (event.key.code == sf::Keyboard::S) {
			usingQuadTree = !usingQuadTree;
			if (usingQuadTree) {
				spacePartition = quadTree.get();
			} else {
				spacePartition = uniformGrid.get();
			}
			std::cout << "Estrutura atual: " << (usingQuadTree ? "QuadTree" : "UniformGrid") << std::endl;
		}
		if (event.key.code == sf::Keyboard::Hyphen) {
			if (usingQuadTree) {
				// Ajusta capacidade da QuadTree
				quadTreeCapacity = quadTreeCapacity - 1;
				configChanged = true;
			} else {
				// Ajusta tamanho da célula do UniformGrid
				uniformGridCellSize = std::max(5.f, uniformGridCellSize - 1.f);
				configChanged = true;
			}
		}
		if (event.key.code == sf::Keyboard::Equal) {
			if (usingQuadTree) {
				// Ajusta capacidade da QuadTree
				quadTreeCapacity++;
				configChanged = true;
			} else {
				// Ajusta tamanho da célula do UniformGrid
				uniformGridCellSize += 1.f;
				configChanged = true;
			}
		}
	}

	/*// Teclado
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up)
            acceleration.y = -force;
        else if (event.key.code == sf::Keyboard::Down)
            acceleration.y = force;
        else if (event.key.code == sf::Keyboard::Left)
            acceleration.x = -force;
        else if (event.key.code == sf::Keyboard::Right)
            acceleration.x = force;
    }
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
            acceleration.y = 0;
        if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
            acceleration.x = 0;
    }*/

    // Mouse
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			dragging = true;
		}
	}
	if (event.type == sf::Event::MouseMoved) {
		sf::Vector2i pixelPos(event.mouseMove.x, event.mouseMove.y);
		mousePosition = window.mapPixelToCoords(pixelPos);
	}
	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			dragging = false;
			particleSelected = nullptr;
		}
	}
	if (event.type == sf::Event::MouseLeft) {
		mouseInSide = false;
		dragging = false;
		particleSelected = nullptr;
	}
	if (event.type == sf::Event::MouseEntered) {
		mouseInSide = true;
	}

    else if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            float delta = event.mouseWheelScroll.delta;
            float newRadius = forceRadius + delta * 2.f;
            newRadius = std::max(5.f, std::min(newRadius, 300.f));
            forceRadius = newRadius;
        }
    }
}

void Sketch::update(float dt) {
	if (!stoped) {
		if (parallel) {
			updateParalell(dt);
		} else {
			updateSequentially(dt);
		}
	}
}

void Sketch::updateParalell(float dt) {
    if (configChanged) reBuildSpacePartition();

    auto start = std::chrono::high_resolution_clock::now();

    // Parte sequencial: reconstrução da estrutura espacial
    spacePartition->clear();
    for (auto& p : particles) {
    	spacePartition->insert(&p);
    	p.setHighlighted(false);
    }

    // Parte paralela: densidade
    #pragma omp parallel for
    for (std::size_t i = 0; i < particles.size(); ++i) {
        Particle& p = particles[i];
        std::vector<Particle*> localFound;
        spacePartition->query(Circle(p.getPredictedPosition(), p.getSmoothingRadius()), localFound);
        p.calculateDensity(localFound);
    }

    // Parte paralela: pressão e viscosidade
    #pragma omp parallel for
    for (std::size_t i = 0; i < particles.size(); ++i) {
        Particle& p = particles[i];
        std::vector<Particle*> localFound;
        spacePartition->query(Circle(p.getPredictedPosition(), p.getSmoothingRadius()), localFound);

        Vector2D pressure = p.calculatePressure(localFound);
        p.applyAcceleration(pressure / p.getDensity());

        if (p.getViscosityStrenght() != 0) {
        	Vector2D viscosityForce = p.calculateViscosityForce(localFound);
        	p.applyForce(viscosityForce);
        }
    }

    // Atualização paralela de posição
    #pragma omp parallel for
    for (std::size_t i = 0; i < particles.size(); ++i) {
    	Particle& p = particles[i];
    	if (withGraity) p.applyAcceleration(gravity);
    	if (p.getSelectedDebbug()) {
    	   std::cerr << p.getAcceleration().length() << std::endl;
    	}
        p.update(dt);
        box.applyConstraint(p);
        if (p.getSelectedDebbug()) {
        	std::cerr << p.getVelocity().length() << std::endl;
        }
    }

    // Detecção de colisão (ainda sequencial)
    if (collision) collisionDetector.detect(particles, *spacePartition);

    if (dragging) {
    	if (applyForce) {
    							foundShapes.clear();
    							spacePartition->query(Circle(mousePosition.x, mousePosition.y, forceRadius), foundShapes);
    							if (!foundShapes.empty()) {
    								for (auto& p : foundShapes) {
    									Vector2D force = p->interactionForce(mousePosition, forceStreng, forceRadius) * forceSignal;
    									p->applyForce(force);
    								}
    							}
    						} else {
    							if(particleSelected) {
    								particleSelected->setPosition(Vector2D(mousePosition.x, mousePosition.y) + dragOffset);
    							}
    						}
    }

    // Consulta pelo mouse (ainda sequencial)
    foundShapes.clear();
    if (queryShapeCircle) {
        Circle query(mousePosition.x, mousePosition.y, forceRadius);
        spacePartition->query(query, foundShapes);
    } else {
        Rectangle query(mousePosition.x - forceRadius, mousePosition.y - forceRadius, 2 * queryRadius, 2 * forceRadius);
        spacePartition->query(query, foundShapes);
    }

    // Timer + debug info
    auto end = std::chrono::high_resolution_clock::now();
    detectionTimeMs = std::chrono::duration<float, std::milli>(end - start).count();

    std::ostringstream oss;
    oss << "Detection: " << detectionTimeMs << " ms (" << (usingQuadTree ? "QuadTree" : "UniformGrid") << ") (" << (withGraity ? "Gravity" : "No Gravity") << ") (" << (parallel ? "Parallel" : "Sequentially") << ")";
    debugText.setString(oss.str());

    if (usingQuadTree) {
        quadTreeOptimizer.update(detectionTimeMs);
    } else {
        uniformGridOptimizer.update(detectionTimeMs);
    }
}

void Sketch::updateSequentially(float dt) {
	if (configChanged) reBuildSpacePartition();

	auto start = std::chrono::high_resolution_clock::now();
	spacePartition->clear();
    for (auto& p : particles) {
        spacePartition->insert(&p);
        p.setHighlighted(false);
    }

    for (auto& p : particles) {
    	foundShapes.clear();
        spacePartition->query(Circle(p.getPredictedPosition(), p.getSmoothingRadius()), foundShapes);
        p.calculateDensity(foundShapes);
    }

    for (auto& p : particles) {
    	foundShapes.clear();
    	spacePartition->query(Circle(p.getPredictedPosition(), p.getSmoothingRadius()), foundShapes);
        Vector2D pressure = p.calculatePressure(foundShapes);
        Vector2D viscosityForce = p.calculateViscosityForce(foundShapes);
        p.applyAcceleration(pressure / p.getDensity());
        p.applyForce(viscosityForce);
        if (p.getSelectedDebbug()) for (auto& point : foundShapes) point->setHighlighted(true);
    }

    for (auto& p : particles) {
    	p.applyAcceleration(gravity);
    	if (p.getSelectedDebbug()) {
    	   std::cerr << p.getAcceleration().length() << std::endl;
    	}
    	p.update(dt);
        box.applyConstraint(p);
        if (p.getSelectedDebbug()) {
        	std::cerr << p.getVelocity().length() << std::endl;
        }
    }

    if (collision) collisionDetector.detect(particles, *spacePartition);

    foundShapes.clear();
    if (queryShapeCircle) {
    	Circle query(mousePosition.x, mousePosition.y, forceRadius);
    	spacePartition->query(query, foundShapes);
    } else {
    	Rectangle query(mousePosition.x -forceRadius, mousePosition.y-forceRadius, 2*forceRadius, 2*forceRadius);
    	spacePartition->query(query, foundShapes);
    }

    auto end = std::chrono::high_resolution_clock::now();
    detectionTimeMs = std::chrono::duration<float, std::milli>(end - start).count();
    std::ostringstream oss;
    oss << "Detection: " << detectionTimeMs << " ms (" << (usingQuadTree ? "QuadTree" : "UniformGrid") << ") (" << (withGraity ? "Gravity" : "No Gravity") << ") (" << (parallel ? "Parallel" : "Sequentially") << ")";
    debugText.setString(oss.str());

    if (usingQuadTree) {
        quadTreeOptimizer.update(detectionTimeMs);
    } else {
    	uniformGridOptimizer.update(detectionTimeMs);
    }
}

void Sketch::draw(sf::RenderWindow& window) {
    box.draw(window);

    if (mouseInSide) {
		if (queryShapeCircle) {
			sf::CircleShape shape(forceRadius);
			shape.setOrigin(forceRadius,forceRadius);
			shape.setFillColor(sf::Color::Green);
			shape.setPosition(sf::Vector2f(mousePosition.x, mousePosition.y));
			window.draw(shape);
		} else {
			sf::RectangleShape shape2(sf::Vector2f(2*forceRadius, 2*forceRadius));
			shape2.setPosition(sf::Vector2f(mousePosition.x -forceRadius, mousePosition.y -forceRadius));
			shape2.setFillColor(sf::Color::Green); // cor escura
			window.draw(shape2);
		}
    }

    //spacePartition->draw(window);

    for (auto& p : particles) {
        p.draw(window);
    }

    window.draw(debugText);

}

const char* Sketch::getWindowName() const {
	return windowName;
}

int Sketch::getWidth() const {
	return windowWidth;
}

int Sketch::getHeight() const {
	return windowHeight;
}

Sketch::~Sketch() {
    delete spacePartition;
}
