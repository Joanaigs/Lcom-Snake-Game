#ifndef _CURSOR_H_
#define _CURSOR_H_

#include <stdbool.h>
#include <stdint.h>
#include "graphics.h"
#include <lcom/lcf.h>

typedef struct{
    int x,y;
    xpm_image_t img;
}cursor;

void (drawCursor)(cursor* c){
  draw_xpm(c->img, c->img.bytes, c->x, c->y);
}


#endif /*_CURSOR_H_ */
