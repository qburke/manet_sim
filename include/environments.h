#ifndef ENVIRONMENTS_H
#define ENVIRONMENTS_H

#include "layers.h"
#include <vector>
#include <stdint.h>
#include <iostream>

typedef struct {
    int x;
    int y;
} CartesianXY;

typedef struct {
    CartesianXY pos;
    Velocity vel;
} LocationData;

/**
 * @brief A simulated environment broken up into
 * Layers. There are movement layers which dictate how devices
 * move and data layers from which devices sense information.
 * The environment keeps track of the devices and their connections.
 */
class Environment
{
private:
    unsigned int time;
public:

    virtual ~Environment() {}

    /**
     * Steps the time of the environment by one unit
     */
    virtual void step() = 0;

    /**
     * Returns the scaled data at Cartesian coordinates (x,y).
     * Red display color
     */
    virtual uint8_t dataRAt(int x, int y) = 0;

    /**
     * Returns the scaled data at Cartesian coordinates (x,y).
     * Green display color
     */
    virtual uint8_t dataGAt(int x, int y) = 0;

    /**
     * Returns the scaled data at Cartesian coordinates (x,y).
     * Blue display color
     */
    virtual uint8_t dataBAt(int x, int y) = 0;

    /**
     * Returns the location of the devices in the environment.
     */
    virtual std::vector<LocationData> devices() = 0;
};

#include <unordered_map>

using namespace std;

class SimpleEnvironment : public Environment
{
private:
    unsigned int time;
    OscHorizontal moveLayer;
    VertBarCycle dataLayer;
    vector<LocationData> devCoords;
public:
    ~SimpleEnvironment() {}

    SimpleEnvironment(int screenWidth, int screenHeight)
        : moveLayer(screenHeight / 2),
        dataLayer(0, screenWidth, 0xFF, 0)
    {
        time = 0;
        // devices
        devCoords.push_back({{10, 10}, {0, 0}});
    }

    void step() {
        time++;
        dataLayer.step();
        moveLayer.step();
        // update device positions
        for(LocationData& l : devCoords) {
            Velocity v = moveLayer.valueAt(l.pos.x, l.pos.y);
            l.vel.x += v.x;
            l.vel.y += v.y;
            l.pos.x += l.vel.x;
            l.pos.y += l.vel.y; 
        }
    }

    uint8_t dataRAt(int x, int y) {
        return 0;
    }

    uint8_t dataGAt(int x, int y) {
        return dataLayer.valueAt(x,y);
    }

    uint8_t dataBAt(int x, int y) {
        return 0;
    }

    vector<LocationData> devices() {
        return devCoords;
    }

};

#endif