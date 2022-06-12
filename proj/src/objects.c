#include "objects.h"
#include "images/0.xpm"
#include "images/1.xpm"
#include "images/2.xpm"
#include "images/3.xpm"
#include "images/4.xpm"
#include "images/5.xpm"
#include "images/6.xpm"
#include "images/7.xpm"
#include "images/8.xpm"
#include "images/9.xpm"
#include "images/clock.xpm"
#include "images/heart-left.xpm"
#include "images/heart-right.xpm"
#include "images/maca.xpm"
#include "images/maca_castanha.xpm"
#include "images/maca_preta.xpm"
#include "images/instructions.xpm"
#include "images/instructions_back.xpm"
#include "images/game_background.xpm"
#include "images/menu_background.xpm"
#include "images/menu_exit.xpm"
#include "images/menu_instructions.xpm"
#include "images/menu_multiPlayer.xpm"
#include "images/menu_singlePlayer.xpm"
#include "images/mouse_cursor.xpm"
#include "snake.h"
#include "graphics.h"
#include "macros.h"
#include <time.h>


void init_xpms(){
  redAppleXpm.map = xpm_load((xpm_map_t)maca_xpm, XPM_8_8_8, &(redAppleXpm.img));
  blackAppleXpm.map = xpm_load((xpm_map_t)maca_preta_xpm, XPM_8_8_8, &(blackAppleXpm.img));
  brownAppleXpm.map = xpm_load((xpm_map_t)maca_castanha_xpm, XPM_8_8_8, &(brownAppleXpm.img));
  timeClock.map = xpm_load((xpm_map_t) clock_xpm, XPM_8_8_8, &(timeClock.img));
  rightHeart.map = xpm_load((xpm_map_t) heart_right_xpm, XPM_8_8_8, &(rightHeart.img));
  leftHeart.map = xpm_load((xpm_map_t) heart_left_xpm, XPM_8_8_8, &(leftHeart.img));
  one.map = xpm_load((xpm_map_t) one_xpm, XPM_8_8_8, &(one.img));
  two.map = xpm_load((xpm_map_t) two_xpm, XPM_8_8_8, &(two.img));
  three.map = xpm_load((xpm_map_t) three_xpm, XPM_8_8_8, &(three.img));
  four.map = xpm_load((xpm_map_t) four_xpm, XPM_8_8_8, &(four.img));
  five.map = xpm_load((xpm_map_t) five_xpm, XPM_8_8_8, &(five.img));
  six.map = xpm_load((xpm_map_t) six_xpm, XPM_8_8_8, &(six.img));
  seven.map = xpm_load((xpm_map_t) seven_xpm, XPM_8_8_8, &(seven.img));
  eight.map = xpm_load((xpm_map_t) eight_xpm, XPM_8_8_8, &(eight.img));
  nine.map = xpm_load((xpm_map_t) nine_xpm, XPM_8_8_8, &(nine.img));
  zero.map = xpm_load((xpm_map_t) zero_xpm, XPM_8_8_8, &(zero.img));
}


void drawBackground(){
    background.map = xpm_load((xpm_map_t)game_background_xpm, XPM_8_8_8, &background.img);
    draw_xpm(background.img, background.map, 0, 0);
}


