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

object apple;
object badApple;
object snakeBody;
snake_head snakehead;

int numOfBodyParts;

void (init_objects)();
void (drawApple)();
void (drawSnake)(char * direction);
void (drawSnakeBody)();
void (addBodyPart)();
void (removeBodyPart)(int n);



int (drawBackground)();
