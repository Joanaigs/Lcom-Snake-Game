#include <stdbool.h>
#include <stdint.h>
#include <lcom/lcf.h>
#include "graphics.h"

typedef struct{
    int x;
    int y;
    int oldx;
    int oldy;
    int changex;
    int changey;
    char * direction;
    char * prevDirection;
    xpm_image_t img;
    uint8_t *map;
    xpm_image_t imgUp;
    uint8_t *mapUp;
    xpm_image_t imgDown;
    uint8_t *mapDown;
    xpm_image_t imgLeft;
    uint8_t *mapLeft;
    xpm_image_t imgRight;
    uint8_t *mapRight;
}snake_part;
snake_part snakeBody[198];
snake_part snakeTail;
int numOfBodyParts;
int numBend;
int len;
bool start; // if true, snake starts moving
double lives;
int numOfApplesEaten;
int gainLive;

int (movement)(int16_t speed );
void (init_snake)();
void (drawSnake)(char * direction, int x, int y);
void (drawSnakeBody)();
void (addBodyPart)();
void (snakeBodyMovement)(int16_t speed);
void (removeBodyPart)(int n);
void periodicApples();
int takelive(double n);
int isSnake(int x, int y);
