#include "Snake.h"

Snake::Snake() : direction(LEFT) {}

void Snake::reset(int startX, int startY, int initialLength) {
    body.clear();
    for (int i = 0; i < initialLength; i++) {
        Point p = { startX + i, startY };
        body.push_back(p);
    }
    direction = LEFT; // init dir == LEFT
}

Point Snake::getHead() const {
    return body[0];
}

void Snake::move() {
    for (int i = body.size() - 1; i > 0; i--) {
        body[i] = body[i - 1];
    }
    switch (direction) {
    case LEFT:  body[0].x--; break;
    case RIGHT: body[0].x++; break;
    case UP:    body[0].y--; break;
    case DOWN:  body[0].y++; break;
    }
}

void Snake::grow() {
    body.push_back(body.back());
}

bool Snake::collidesWithSelf() const {
    Point head = getHead();
    for (size_t i = 1; i < body.size(); i++) {
        if (head.x == body[i].x && head.y == body[i].y)
            return true;
    }
    return false;
}
