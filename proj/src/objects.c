#include "objects.h"
#include "images/maca.xpm"
#include "images/maca_castanha.xpm"
#include "images/maca_preta.xpm"
#include "images/game_background.xpm"
#include "snake.h"


void (init_xpms)(){
  redAppleXpm.map = xpm_load((xpm_map_t)maca_xpm, XPM_8_8_8, &(redAppleXpm.img));
  blackAppleXpm.map = xpm_load((xpm_map_t)maca_preta_xpm, XPM_8_8_8, &(blackAppleXpm.img));
  brownAppleXpm.map = xpm_load((xpm_map_t)maca_castanha_xpm, XPM_8_8_8, &(brownAppleXpm.img));

}


object (get_xpm)(enum appleType type){
    switch (type) {
        case red: return redAppleXpm;
        case brown: return brownAppleXpm;
        case black: return blackAppleXpm;
    }
}

int (drawBackground)(){
    background.map = xpm_load((xpm_map_t)game_background_xpm, XPM_8_8_8, &background.img);
    draw_xpm(background.img, background.map, 0, 0);
    return 0;
}

void (initApple)(Apple *apple, int x_pos, int y_pos, enum appleType type){
    apple->type = type;
    apple->appleXpm = get_xpm(type);
    apple->x_pos = x_pos;
    apple->y_pos = y_pos;

    applesArray[numApples] = *apple;
    numApples++;

}

void (initRandomApple)(Apple *apple, enum appleType type){
    apple->type = type;
    apple->appleXpm = get_xpm(type);

    int x;
    int y;
    do {
        srand(time(0));
        x = ((rand() % ((h_res - 40 + 1 - 40) / 40)) * 40 )+ 40;
        srand(time(0));
        y = ((rand() % ((v_res - 40 + 1 - 120) / 40)) * 40 )+ 120;

    } while (isApple(x,y) != -1 || isSnake(x,y) == 1);


    apple->x_pos = x;
    apple->y_pos = y;

    applesArray[numApples] = *apple;
    numApples++;

}

void (drawApple)(Apple apple){
    draw_xpm(apple.appleXpm.img, apple.appleXpm.map, apple.x_pos, apple.y_pos);
}


int (isApple)(int x, int y) {
    for (int i = 0; i < numApples; i++) {
        if (applesArray[i].x_pos == x && applesArray[i].y_pos == y) {
            return i;
        }
    }
    return -1;
}



