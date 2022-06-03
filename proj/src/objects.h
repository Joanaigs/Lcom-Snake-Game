#ifndef __OBJECTS_H
#define __OBJECTS_H


#include <stdbool.h>
#include <stdint.h>
#include <lcom/lcf.h>
#include "graphics.h"
#include "macros.h"



typedef struct{
    int x;
    int y;
    char * direction;
    char * prevDirection;
    int xVelocity, yVelocity;
    xpm_image_t imgUp;
    uint8_t *mapUp;
    xpm_image_t imgDown;
    uint8_t *mapDown;
    xpm_image_t imgLeft;
    uint8_t *mapLeft;
    xpm_image_t imgRight;
    uint8_t *mapRight;
}snake_head;

typedef struct{
    int x;
    int y;
    int xVelocity, yVelocity;
    xpm_image_t img;
    uint8_t *map;
}object;

object goodApple;
object brownApple;
object blackApple;
object snakeBody;
object snakeTail;
snake_head snakehead;
object  brownApples[5];
int nBrownApples;
//object blackApples[5];
//int nBlackApples = 0;

int numOfBodyParts;

void (init_objects)();
void (drawGoodApple)();
void (drawBlackApple)();
void (drawBrownApple)();
void (drawSnake)(char * direction);
void (drawSnakeBody)();
void (addBodyPart)();
void (removeBodyPart)(int n);
void (addBrownApple)(int x, int y);
int (drawBackground)();


#endif /* __OBJECTS_H */
