#include <stdbool.h>
#include <stdint.h>
#include <lcom/lcf.h>
#include "graphics.h"
#include "macros.h"


typedef struct{
    int x;
    int y;
    xpm_image_t img;
    uint8_t *map;
}object;

object goodApple;
object brownApple;
object blackApple;
object background;

void (init_objects)();
void (drawGoodApple)();
void (drawBlackApple)();
void (drawBrownApple)();
int (drawBackground)();
