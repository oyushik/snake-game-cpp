#pragma once

#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "Snake.h"
#include "Food.h"

class SnakeGame {
private:
    Snake snake;
    Food food;
    int score;
    int bestScore;
    int lastScore;
    int speed;

    void drawMap();
    void displayScore();
    void resetGame();
    void update();
    void pauseGame();
    void gameOver();
    void titleScreen();

public:
    SnakeGame();
    void run();
};

#endif // SNAKEGAME_H
