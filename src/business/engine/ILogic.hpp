/*
 * ILogic.hpp
 *
 *  Created on: 18 de mar. de 2025
 *      Author: aleksander
 */

// ILogic.hpp
#ifndef BUSINESS_ENGINE_ILOGIC_HPP_
#define BUSINESS_ENGINE_ILOGIC_HPP_

#include <SFML/Graphics.hpp>

class ILogic {
public:
    virtual void init() = 0;
    virtual void input(const sf::Event& event, sf::RenderWindow& window) = 0; // @suppress("Type cannot be resolved")
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0; // @suppress("Type cannot be resolved")
    virtual const char* getWindowName() const = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual ~ILogic() {}
};

#endif /* BUSINESS_ENGINE_ILOGIC_HPP_ */
