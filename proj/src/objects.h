#ifndef __OBJECTS_H
#define __OBJECTS_H


#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <lcom/lcf.h>




enum appleType{red, brown, black};

typedef struct{
    int x;
    int y;
    xpm_image_t img;
    uint8_t *map;
}object;

object redAppleXpm;
object brownAppleXpm;
object blackAppleXpm;
object background;
int nBrownApples;
//object blackApples[5];
//int nBlackApples = 0;


void (init_xpms)();
int (drawBackground)();
object (get_xpm)(enum appleType type);
void (addBrownApple)(int x, int y);

typedef struct {
    int x_pos;
    int y_pos;
    object appleXpm;
    enum appleType type;
}Apple;


Apple applesArray[195];
int numApples;

void (initApple)(Apple *apple, int x_pos, int y_pos, enum appleType type);
void (initRandomApple)(Apple *apple, enum appleType type);

void (drawApple)(Apple apple);

int (isApple)(int x, int y);

void placeApple(int x, int y, enum appleType a);



#endif /* __OBJECTS_H */
