#include "SnakeGame.h"
#include "Utils.h"
#include "Config.h"
#include <conio.h>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
#include <ctime>

SnakeGame::SnakeGame() : score(0), bestScore(0), lastScore(0), speed(100) {
    srand(static_cast<unsigned int>(time(NULL)));
}

void SnakeGame::drawMap() {
    // Draw top wall
    for (int i = 0; i < MAP_WIDTH; i++) {
        gotoxy(MAP_X + i, MAP_Y, "[]");
    }
    // Draw left and right walls
    for (int i = MAP_Y + 1; i < MAP_Y + MAP_HEIGHT - 1; i++) {
        gotoxy(MAP_X, i, "[]");
        gotoxy(MAP_X + MAP_WIDTH - 1, i, "[]");
    }
    // Draw bottom wall
    for (int i = 0; i < MAP_WIDTH; i++) {
        gotoxy(MAP_X + i, MAP_Y + MAP_HEIGHT - 1, "[]");
    }
}

void SnakeGame::displayScore() {
    gotoxy(MAP_X, MAP_Y + MAP_HEIGHT, " YOUR SCORE: ");
    printf("%3d, LAST SCORE: %3d, BEST SCORE: %3d", score, lastScore, bestScore);
}

void SnakeGame::titleScreen() {
    while (kbhit()) getch(); // Clear buffered keys

    drawMap();
    // Clear inner board
    for (int i = MAP_Y + 1; i < MAP_Y + MAP_HEIGHT - 1; i++) {
        for (int j = MAP_X + 1; j < MAP_X + MAP_WIDTH - 1; j++) {
            gotoxy(j, i, "  ");
        }
    }
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 5, "+--------------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 6, "|        S N A K E         |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 7, "+--------------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 9, " < PRESS ANY KEY TO START > ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 11, "      Arrow key : Move    ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 12, "      P : Pause             ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 13, "      ESC : Quit              ");

    while (true) {
        if (kbhit()) {
            int ch = getch();
            if (ch == ESC)
                exit(0);
            else
                break;
        }
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 9, " < PRESS ANY KEY TO START > ");
        Sleep(400);
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 9, "                            ");
        Sleep(400);
    }
    resetGame();
}

void SnakeGame::resetGame() {
    system("cls");  // Clear the screen
    drawMap();
    while (kbhit()) getch();  // Clear keyboard buffer

    snake.reset(MAP_WIDTH / 2, MAP_HEIGHT / 2, 5);
    score = 0;
    speed = 100;
    // Draw snake body (using "o") and head (using "Q")
    for (size_t i = 0; i < snake.body.size(); i++) {
        gotoxy(MAP_X + snake.body[i].x, MAP_Y + snake.body[i].y, "o");
    }
    gotoxy(MAP_X + snake.body[0].x, MAP_Y + snake.body[0].y, "Q");

    // Generate and draw food
    food.generate(snake);
    food.draw();
    displayScore();
}

void SnakeGame::pauseGame() {
    while (true) {
        if (kbhit()) {
            int ch = getch();
            if (ch != PAUSE)
                break;
        }
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 9, MAP_Y, "< PAUSE : PRESS ANY KEY TO RESUME > ");
        Sleep(400);
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 9, MAP_Y, "                                    ");
        Sleep(400);
    }
}

void SnakeGame::gameOver() {
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 5, "+----------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 6, "|      GAME OVER !     |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 7, "+----------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 8, " YOUR SCORE: ");
    printf("%d", score);
    lastScore = score;
    if (score > bestScore) {
        bestScore = score;
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 4, MAP_Y + 10, "! BEST SCORE !");
    }
    Sleep(500);
    while (kbhit()) getch();
    getch();
    titleScreen();
}

void SnakeGame::update() {
    // Check collision with food
    if (snake.getHead().x == food.position.x && snake.getHead().y == food.position.y) {
        score += 10;
        snake.grow();
        food.generate(snake);
        food.draw();
        speed = (speed > 3) ? speed - 3 : speed;
    }
    // Check collision with walls
    Point head = snake.getHead();
    if (head.x == 0 || head.x == MAP_WIDTH - 1 || head.y == 0 || head.y == MAP_HEIGHT - 1) {
        gameOver();
        return;
    }
    // Check collision with self
    if (snake.collidesWithSelf()) {
        gameOver();
        return;
    }

    // Erase tail from screen
    Point tail = snake.body.back();
    gotoxy(MAP_X + tail.x, MAP_Y + tail.y, "  ");
    // Move the snake
    snake.move();
    // Draw old head as body segment
    Point oldHead = snake.body[1];
    gotoxy(MAP_X + oldHead.x, MAP_Y + oldHead.y, "o");
    // Draw new head
    Point newHead = snake.getHead();
    gotoxy(MAP_X + newHead.x, MAP_Y + newHead.y, "Q");
    displayScore();
}

void SnakeGame::run() {
    titleScreen();
    while (true) {
        // Handle input
        if (kbhit()) {
            int ch = getch();
            while (ch == 224) { // Ignore extended keys
                ch = getch();
            }
            if (ch == ESC) {
                exit(0);
            }
            else if (ch == PAUSE) {
                pauseGame();
            }
            else if (ch == LEFT || ch == RIGHT || ch == UP || ch == DOWN) {
                // Prevent a 180-degree turn
                if ((snake.direction == LEFT && ch != RIGHT) ||
                    (snake.direction == RIGHT && ch != LEFT) ||
                    (snake.direction == UP && ch != DOWN) ||
                    (snake.direction == DOWN && ch != UP)) {
                    snake.direction = ch;
                }
            }
        }
        update();
        Sleep(speed);
    }
}
