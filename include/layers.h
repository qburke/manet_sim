#ifndef LAYERS_H
#define LAYERS_H

/**
 * A scalar plane parametrized by time.
 */
class DataLayer
{
private:
    unsigned int time;
public:

    virtual ~DataLayer() {}

    /**
     * Returns the value of the layer at Cartesian
     * coordinates (x, y).
     */
    virtual int valueAt(int x, int y) = 0;

    /**
     * Advances the time of the layer by 1
     */
    virtual void step() = 0;
};

typedef struct {
    int x;
    int y;
} Velocity;

/**
 * A planar vector field parametrized by time.
 */
class MobileLayer
{
private:
    unsigned int time;
public:

    virtual ~MobileLayer() {}

    /**
     * Returns the vector of the layer at Cartesian
     * coordinates (x, y).
     */
    virtual Velocity valueAt(int x, int y) = 0;

    /**
     * Advances the time of the layer by 1
     */
    virtual void step() = 0;
};

class OscHorizontal : public MobileLayer {
private:
    int midLine;
public:
    ~OscHorizontal() {}

    OscHorizontal(int midLine) {
        this->midLine = midLine;
    }

    Velocity valueAt(int x, int y) {
        return {0, (midLine - y) >> 4};
    }

    void step() {

    }
};

class VertBarCycle : public DataLayer {
private:
    int barPos;
    int leftBound;
    int rightBound;
    int max;
    int min;
public:
    ~VertBarCycle() {}

    VertBarCycle(int left, int right, int max, int min) {
        leftBound = left;
        rightBound = right;
        this->max = max;
        this->min = min;
        barPos = 0;
    }

    int valueAt(int x, int y) {
        if(x >= leftBound && x <= rightBound) {
            int diff = barPos - x;
            diff = diff > 0 ? diff : -diff;
            // TODO change
            return min - diff * 10;
        } else {
            return 0;
        }
    }

    void step() {
        barPos++;
        if(barPos >= rightBound) {
            barPos = leftBound;
        }
    }

};

#endif