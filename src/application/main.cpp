/*
 * main.cpp
 *
 *  Created on: 18 de mar. de 2025
 *      Author: aleksander
 */

// main.cpp
#include "business/engine/Engine.hpp"
#include "business/Sketch.hpp"

int main() {
    Sketch sketch;
    Engine engine(&sketch, 30, 30, false);
    engine.run();
    return 0;
}
