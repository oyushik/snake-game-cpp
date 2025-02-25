#include "Food.h"
#include "Utils.h"
#include "Config.h"
#include <cstdlib>
#include <ctime>

Food::Food() : position({ 0, 0 }) {}

void Food::generate(const Snake& snake) {
    int r = 0;
    bool collision = false;
    do {
        collision = false;
        srand(static_cast<unsigned int>(time(NULL)) + r);
        position.x = (rand() % (MAP_WIDTH - 2)) + 1;
        position.y = (rand() % (MAP_HEIGHT - 2)) + 1;
        for (size_t i = 0; i < snake.body.size(); i++) {
            if (position.x == snake.body[i].x && position.y == snake.body[i].y) {
                collision = true;
                r++;
                break;
            }
        }
    } while (collision);
}

void Food::draw() const {
    gotoxy(MAP_X + position.x, MAP_Y + position.y, "&");
}
