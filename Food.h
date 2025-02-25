#pragma once

#ifndef FOOD_H
#define FOOD_H

#include "Point.h"
#include "Snake.h"

class Food {
public:
    Point position;
    Food();
    void generate(const Snake& snake);
    void draw() const;
};

#endif // FOOD_H
