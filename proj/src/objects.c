#include "objects.h"
#include "images/maca.xpm"
#include "images/maca_castanha.xpm"
#include "images/maca_preta.xpm"
#include "images/game_background.xpm"


int (drawBackground)(){
  /*
  uint32_t lightGreen=SET_COLOR(170, 215, 81);
  uint32_t darkGreen=SET_COLOR(148, 191, 67);
  uint16_t weight = h_res/10;
  uint16_t height = v_res/10;
  int i=0;
  for(uint8_t row = 0; row < 10; ++row){
        for(uint8_t col = 0; col < 10; ++col){
            uint16_t x = col * weight;
            uint16_t y = row * height;
            uint16_t w = (x + weight >h_res) ? (h_res - x) : (weight);
            uint16_t h = (y + height > v_res) ? (v_res - y) : (height);

            if(i%2==0){
              if (vg_draw_rectangle(x,y,w,h,lightGreen)) 
                return 1;
            }
            else{
              if (vg_draw_rectangle(x,y,w,h,darkGreen)) 
                return 1;
            }
            i++;
        }
        i++;
    }
    */
  
    background.map = xpm_load((xpm_map_t)game_background_xpm, XPM_8_8_8, &background.img);
    draw_xpm(background.img, background.map, 0, 0);
    return 0;
}

void (init_objects)(){
  goodApple.map = xpm_load((xpm_map_t)maca_xpm, XPM_8_8_8, &(goodApple.img));
  goodApple.x=55; goodApple.y=1;
  blackApple.map = xpm_load((xpm_map_t)maca_preta_xpm, XPM_8_8_8, &(blackApple.img));
  blackApple.x=0; blackApple.y=1;
  brownApple.map = xpm_load((xpm_map_t)maca_castanha_xpm, XPM_8_8_8, &(brownApple.img));
  brownApple.x=55; brownApple.y=400;
  nBrownApples = 0;
}

void (drawGoodApple)(){
  draw_xpm(goodApple.img, goodApple.map, goodApple.x, goodApple.y);
}

void (drawBlackApple)(){
  draw_xpm(blackApple.img,blackApple.map, blackApple.x, blackApple.y);
}

void (addBrownApple)(int x, int y){
  if(nBrownApples >= 4) nBrownApples = 0;
  brownApples[nBrownApples].x = x;
  brownApples[nBrownApples].y = y;
  xpm_load((xpm_map_t)maca_castanha_xpm,XPM_8_8_8, &(brownApples[nBrownApples].img));
  nBrownApples++;
}

void (drawBrownApple)(){
  for(int i = 0 ; i < nBrownApples; i++){
    draw_xpm( brownApples[i].img, brownApples[i].img.bytes, brownApples[i].x, brownApples[i].y);
  }
}
