/*
 * Engine.hpp
 *
 *  Created on: 18 de mar. de 2025
 *      Author: aleksander
 */

// Engine.hpp
#ifndef SRC_BUSINESS_ENGINE_ENGINE_HPP_
#define SRC_BUSINESS_ENGINE_ENGINE_HPP_

#include "ILogic.hpp"
#include <SFML/Graphics.hpp>
#include <thread>

class Engine {
public:
    Engine(ILogic* logic, int fps, int ups, bool sync);
    void run();
    void stop();

private:
    void loop();
    void sync(float frameStartTime);

    ILogic* logic;
    int targetFPS;
    int targetUPS;
    bool syncEnabled;
    bool running;
};

#endif /* SRC_BUSINESS_ENGINE_ENGINE_HPP_ */
