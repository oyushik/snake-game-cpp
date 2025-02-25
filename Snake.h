#pragma once

#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "Point.h"
#include "Config.h"

using namespace std;

class Snake {
public:
    vector<Point> body;   // Snake body segments
    int direction;        // Current direction (LEFT, RIGHT, UP, DOWN)

    Snake();
    void reset(int startX, int startY, int initialLength);
    Point getHead() const;
    void move();
    void grow();
    bool collidesWithSelf() const;
};

#endif // SNAKE_H
