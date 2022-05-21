#include "objects.h"
#include "images/maca.xpm"
#include "images/cabeca_cobra_baixo.xpm"
#include "images/cabeca_cobra_cima.xpm"
#include "images/cabeca_cobra_dir.xpm"
#include "images/cabeca_cobra_esq.xpm"
#include "images/corpo_cobra.xpm"
#include "images/cauda_cobra.xpm"
int (drawBackground)(){
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
    return 0;
}

void (init_objects)(){
  apple.map = xpm_load((xpm_map_t)maca_xpm, XPM_8_8_8, &(apple.img));
  apple.x=55; apple.y=1;
  snakehead.mapLeft=xpm_load((xpm_map_t)cobra_esquerda_xpm, XPM_8_8_8, &snakehead.imgLeft);
  snakehead.mapRight=xpm_load((xpm_map_t)cobra_direita_xpm, XPM_8_8_8, &snakehead.imgRight);
  snakehead.mapDown=xpm_load((xpm_map_t)cobra_baixo_xpm, XPM_8_8_8, &snakehead.imgDown);
  snakehead.mapUp=xpm_load((xpm_map_t)cobra_cima_xpm, XPM_8_8_8, &snakehead.imgUp);
  snakehead.x=100;snakehead.y=100;
  snakeBody.map=xpm_load((xpm_map_t)cobra_corpo_xpm, XPM_8_8_8, &snakeBody.img);
  snakeTail.map=xpm_load((xpm_map_t)cobra_cauda_xpm, XPM_8_8_8, &snakeTail.img);
  snakeBody.x=snakehead.x+snakehead.imgUp.width+1;snakeBody.y=snakehead.y+snakehead.imgUp.height+1;
  numOfBodyParts=1;
}

void (drawApple)(){
  draw_xpm(apple.img, apple.map, apple.x, apple.y);
}

void (drawSnake)(char * direction){
  if(strcmp(direction, "UP")==0){
    draw_xpm(snakehead.imgUp, snakehead.mapUp, snakehead.x, snakehead. y);
    snakeBody.x=snakehead.x;snakeBody.y=snakehead.y+snakehead.imgUp.height;
    snakehead.direction="UP";
  }
  else if(strcmp(direction, "DOWN")==0){
    draw_xpm(snakehead.imgDown, snakehead.mapDown, snakehead.x, snakehead. y);
    snakeBody.x=snakehead.x;snakeBody.y=snakehead.y-snakehead.imgUp.height;
    snakehead.direction="DOWN";
  }
  else if(strcmp(direction, "LEFT")==0){
    draw_xpm(snakehead.imgLeft, snakehead.mapLeft, snakehead.x, snakehead. y);
    snakeBody.x=snakehead.x+snakehead.imgUp.width;snakeBody.y=snakehead.y;
    snakehead.direction="LEFT";
  }
  else if(strcmp(direction, "RIGHT")==0){
    draw_xpm(snakehead.imgRight, snakehead.mapRight, snakehead.x, snakehead. y);
    snakeBody.x=snakehead.x-snakeBody.img.width;snakeBody.y=snakehead.y+9 ;
    snakehead.direction="RIGHT";
  }
  drawSnakeBody();
}

void (drawSnakeBody)(){
  for(int i=0; i<numOfBodyParts; i++){
    if(strcmp(snakehead.direction, "UP")==0){
      draw_xpm(snakeBody.img, snakeBody.map, snakeBody.x, snakeBody.y+i*snakeBody.img.height);
      draw_xpm(snakeTail.img, snakeTail.map, snakeBody.x, snakeBody.y+(i+1)*snakeBody.img.height);
    }
    else if(strcmp(snakehead.direction, "DOWN")==0){
      draw_xpm(snakeBody.img, snakeBody.map, snakeBody.x, snakeBody.y-i*snakeBody.img.height);
      draw_xpm(snakeTail.img, snakeTail.map, snakeBody.x, snakeBody.y-(i+1)*snakeBody.img.height);
    }
    else if(strcmp(snakehead.direction, "LEFT")==0){
      draw_xpm(snakeBody.img, snakeBody.map, snakeBody.x+i*snakeBody.img.width, snakeBody.y);
      draw_xpm(snakeTail.img, snakeTail.map, snakeBody.x+(i+1)*snakeBody.img.width, snakeBody.y);
    }
    else if(strcmp(snakehead.direction, "RIGHT")==0){
      draw_xpm(snakeBody.img, snakeBody.map, snakeBody.x-i*snakeBody.img.width, snakeBody. y);
      draw_xpm(snakeTail.img, snakeTail.map, snakeBody.x-(i+1)*snakeBody.img.width, snakeBody.y);
    }
  }
}

void (addBodyPart)(){
  numOfBodyParts++;
}

void (removeBodyPart)(int n){
  numOfBodyParts-=n;
}
