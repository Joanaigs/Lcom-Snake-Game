#include "snake.h"
#include "objects.h"
#include "graphics.h"
#include "images/cabeca_cobra_baixo.xpm"
#include "images/cabeca_cobra_cima.xpm"
#include "images/cabeca_cobra_dir.xpm"
#include "images/cabeca_cobra_esq.xpm"
#include "images/corpo_cobra.xpm"
#include "images/cauda-baixo.xpm"
#include "images/cauda-cima.xpm"
#include "images/cauda-direita.xpm"
#include "images/cauda-esquerda.xpm"


void (init_snake)(){
  snakeBody[0].mapLeft=xpm_load((xpm_map_t)cobra_esquerda_xpm, XPM_8_8_8, &snakeBody[0].imgLeft);
  snakeBody[0].mapRight=xpm_load((xpm_map_t)cobra_direita_xpm, XPM_8_8_8, &snakeBody[0].imgRight);
  snakeBody[0].mapDown=xpm_load((xpm_map_t)cobra_baixo_xpm, XPM_8_8_8, &snakeBody[0].imgDown);
  snakeBody[0].mapUp=xpm_load((xpm_map_t)cobra_cima_xpm, XPM_8_8_8, &snakeBody[0].imgUp);
  snakeBody[0].x=300;snakeBody[0].y=300;
  snakeBody[1].map=xpm_load((xpm_map_t)cobra_corpo_xpm, XPM_8_8_8, &snakeBody[1].img);
  snakeBody[1].x=snakeBody[0].x+snakeBody[0].imgUp.width+1;snakeBody[1].y=snakeBody[0].y+snakeBody[0].imgUp.height+1;
  numOfBodyParts=2;
  snakeTail.mapLeft=xpm_load((xpm_map_t)tail_left_xpm, XPM_8_8_8, &snakeTail.imgLeft);
  snakeTail.mapRight=xpm_load((xpm_map_t)tail_right_xpm, XPM_8_8_8, &snakeTail.imgRight);
  snakeTail.mapDown=xpm_load((xpm_map_t)tail_down_xpm, XPM_8_8_8, &snakeTail.imgDown);
  snakeTail.mapUp=xpm_load((xpm_map_t)tail_up_xpm, XPM_8_8_8, &snakeTail.imgUp);
}

void (drawSnake)(char * direction, int x, int y){
  if(strcmp(direction, "UP")==0){
    draw_xpm(snakeBody[0].imgUp, snakeBody[0].mapUp, snakeBody[0].x, snakeBody[0].y);
    snakeBody[1].x=snakeBody[0].x+9;snakeBody[1].y=snakeBody[0].y+snakeBody[0].imgUp.height;
    snakeBody[0].direction="UP";
    snakeBody[0].prevDirection="UP";
    snakeBody[1].direction="UP";
    snakeBody[1].prevDirection="UP";
    snakeTail.x=snakeBody[numOfBodyParts-1].x;snakeTail.y=snakeBody[numOfBodyParts-1].y+snakeBody[numOfBodyParts-1].img.height;
    snakeTail.direction="UP";
    snakeTail.prevDirection="UP"; 
  }
  else if(strcmp(direction, "DOWN")==0){
    draw_xpm(snakeBody[0].imgDown, snakeBody[0].mapDown, snakeBody[0].x, snakeBody[0]. y);
    snakeBody[1].x=snakeBody[0].x+9;snakeBody[1].y=snakeBody[0].y-snakeBody[1].img.height;
    snakeBody[0].direction="DOWN";
    snakeBody[0].prevDirection="DOWN";
    snakeBody[1].direction="DOWN";
    snakeBody[1].prevDirection="DOWN";
    snakeTail.x=snakeBody[numOfBodyParts-1].x-1;snakeTail.y=snakeBody[numOfBodyParts-1].y-snakeBody[numOfBodyParts-1].img.height;
    snakeTail.direction="DOWN";
    snakeTail.prevDirection="DOWN";
  } 
  else if(strcmp(direction, "LEFT")==0){
    draw_xpm(snakeBody[0].imgLeft, snakeBody[0].mapLeft, snakeBody[0].x, snakeBody[0]. y);
    snakeBody[1].x=snakeBody[0].x+snakeBody[0].imgUp.width;snakeBody[1].y=snakeBody[0].y+9;
    snakeBody[0].direction="LEFT";
    snakeBody[0].prevDirection="LEFT";
    snakeBody[1].direction="LEFT";
    snakeBody[1].prevDirection="LEFT";
    snakeTail.x=snakeBody[numOfBodyParts-1].x+snakeBody[numOfBodyParts-1].img.width;snakeTail.y=snakeBody[numOfBodyParts-1].y-1;
    snakeTail.direction="LEFT";
    snakeTail.prevDirection="LEFT";
  }
  else if(strcmp(direction, "RIGHT")==0){
    draw_xpm(snakeBody[0].imgRight, snakeBody[0].mapRight, snakeBody[0].x, snakeBody[0]. y);
    snakeBody[1].x=snakeBody[0].x-snakeBody[1].img.width;snakeBody[1].y=snakeBody[0].y+9 ;
    snakeBody[0].direction="RIGHT";
    snakeBody[0].prevDirection="RIGHT";
    snakeBody[1].direction="RIGHT";
    snakeBody[1].prevDirection="RIGHT";
    snakeTail.x=snakeBody[numOfBodyParts-1].x-snakeBody[numOfBodyParts-1].img.width;snakeTail.y=snakeBody[numOfBodyParts-1].y;
    snakeTail.direction="RIGHT";
    snakeTail.prevDirection="RIGHT";
  }
  
}

void (drawSnakeBody)(){
  for(int i=0; i<numOfBodyParts; i++){
    draw_xpm(snakeBody[i].img, snakeBody[i].map, snakeBody[i].x, snakeBody[i].y);
  }
  if(strcmp(snakeTail.direction, "UP")==0){
    draw_xpm(snakeTail.imgUp, snakeTail.mapUp, snakeTail.x, snakeTail.y); 
  }
  else if(strcmp(snakeTail.direction, "DOWN")==0){
    draw_xpm(snakeTail.imgDown, snakeTail.mapDown, snakeTail.x, snakeTail.y);
  } 
  else if(strcmp(snakeTail.direction, "LEFT")==0){
    draw_xpm(snakeTail.imgLeft, snakeTail.mapLeft, snakeTail.x, snakeTail.y);
  }
  else if(strcmp(snakeTail.direction, "RIGHT")==0){
    draw_xpm(snakeTail.imgRight, snakeTail.mapRight, snakeTail.x, snakeTail.y);
  }
}

void (addBodyPart)(){
  numOfBodyParts++;
  int i=numOfBodyParts-1;
  snakeBody[i].map=xpm_load((xpm_map_t)cobra_corpo_xpm, XPM_8_8_8, &snakeBody[i].img);
  if(strcmp(snakeBody[i-1].direction, "UP")==0){
      snakeBody[i].x=snakeBody[i-1].x;
      snakeBody[i].y=snakeBody[i-1].y+snakeBody[i-1].img.height;
      snakeBody[i].direction="UP";
      snakeBody[i].prevDirection="UP";
      snakeTail.x=snakeBody[numOfBodyParts-1].x;snakeTail.y=snakeBody[numOfBodyParts-1].y+snakeBody[numOfBodyParts-1].img.height;
    }
    else if(strcmp(snakeBody[i-1].direction, "DOWN")==0){
      snakeBody[i].x=snakeBody[i-1].x;
      snakeBody[i].y=snakeBody[i-1].y-snakeBody[i-1].img.height;
      snakeBody[i].direction="DOWN";
      snakeBody[i].prevDirection="DOWN";
      snakeTail.x=snakeBody[numOfBodyParts-1].x-1;snakeTail.y=snakeBody[numOfBodyParts-1].y-snakeBody[numOfBodyParts-1].img.height;
    }
    else if(strcmp(snakeBody[i-1].direction, "LEFT")==0){
      snakeBody[i].x=snakeBody[i-1].x+snakeBody[i-1].img.width;
      snakeBody[i].y=snakeBody[i-1].y;
      snakeBody[i].direction="LEFT";
      snakeBody[i].prevDirection="LEFT";
      snakeTail.x=snakeBody[numOfBodyParts-1].x+snakeBody[numOfBodyParts-1].img.width;snakeTail.y=snakeBody[numOfBodyParts-1].y;

    }
    else if(strcmp(snakeBody[i-1].direction, "RIGHT")==0){
      snakeBody[i].x=snakeBody[i-1].x-snakeBody[i-1].img.width;
      snakeBody[i].y=snakeBody[i-1].y;
      snakeBody[i].direction="RIGHT";
      snakeBody[i].prevDirection="RIGHT";
      snakeTail.x=snakeBody[numOfBodyParts-1].x-snakeBody[numOfBodyParts-1].img.width;snakeTail.y=snakeBody[numOfBodyParts-1].y;

    }
    
}

void (removeBodyPart)(int n){
  numOfBodyParts-=n;
}

void (eraseSnakeBody)(){
  for(int i=1; i<numOfBodyParts; i++){
    erase_xpm(snakeBody[i].img, snakeBody[i].x, snakeBody[i].y, background.img);
  }
}

void (eraseSnakeTail)(){
  if(strcmp(snakeTail.direction, "UP")==0){
    erase_xpm(snakeTail.imgUp, snakeTail.x, snakeTail.y, background.img); 
  }
  else if(strcmp(snakeTail.direction, "DOWN")==0){
    erase_xpm(snakeTail.imgDown, snakeTail.x, snakeTail.y, background.img);
  } 
  else if(strcmp(snakeTail.direction, "LEFT")==0){
    erase_xpm(snakeTail.imgLeft, snakeTail.x, snakeTail.y, background.img);
  }
  else if(strcmp(snakeTail.direction, "RIGHT")==0){
    erase_xpm(snakeTail.imgRight, snakeTail.x, snakeTail.y, background.img);
  }
}

void (changeBodyDirection(int i)){
  if(strcmp(snakeBody[i-1].direction, "UP")==0){
    if(i==1){
      snakeBody[i].x=snakeBody[0].x+9;snakeBody[i].y=snakeBody[0].y+snakeBody[0].imgUp.height;
    }
    else{
      snakeBody[i].x=snakeBody[i-1].x;
      snakeBody[i].y=snakeBody[i-1].y+snakeBody[i-1].img.height;
    }
    snakeBody[i].prevDirection=snakeBody[i].direction;
    snakeBody[i].direction="UP";
    snakeBody[i-1].prevDirection="UP";
  }
  else if(strcmp(snakeBody[i-1].direction, "DOWN")==0){
    if(i==1){
      snakeBody[i].x=snakeBody[0].x+9;snakeBody[i].y=snakeBody[0].y-snakeBody[i].img.height;
    }
      else{
      snakeBody[i].x=snakeBody[i-1].x;
      snakeBody[i].y=snakeBody[i-1].y-snakeBody[i-1].img.height;
    }
    snakeBody[i].prevDirection=snakeBody[i].direction;
    snakeBody[i].direction="DOWN";
    snakeBody[i-1].prevDirection="DOWN";
  }
  else if(strcmp(snakeBody[i-1].direction, "LEFT")==0){
    if(i==1){
      snakeBody[i].x=snakeBody[0].x+snakeBody[0].imgUp.width;snakeBody[i].y=snakeBody[0].y+9;
    }
      else{
      snakeBody[i].x=snakeBody[i-1].x+snakeBody[i-1].img.width;
      snakeBody[i].y=snakeBody[i-1].y;
    }
    snakeBody[i].prevDirection=snakeBody[i].direction;
    snakeBody[i].direction="LEFT";
    snakeBody[i-1].prevDirection="LEFT";
  }
  else if(strcmp(snakeBody[i-1].direction, "RIGHT")==0){
      if(i==1){
      snakeBody[1].x=snakeBody[0].x-snakeBody[1].img.width;snakeBody[1].y=snakeBody[0].y+9 ;
    }
      else{
      snakeBody[i].x=snakeBody[i-1].x-snakeBody[i-1].img.width;
      snakeBody[i].y=snakeBody[i-1].y;
    }
    snakeBody[i].prevDirection=snakeBody[i].direction;
    snakeBody[i].direction="RIGHT";
    snakeBody[i-1].prevDirection="RIGHT";
  }
}

void (changeTailDirection()){
  int bx=snakeBody[numOfBodyParts-1].x;
  int by=snakeBody[numOfBodyParts-1].y;
  int bw=snakeBody[numOfBodyParts-1].img.width;
  int bh=snakeBody[numOfBodyParts-1].img.height;
  if(strcmp(snakeBody[numOfBodyParts-1].direction, "UP")==0){
    snakeTail.x=bx;
    snakeTail.y=by+bw;
    snakeTail.direction="UP";
  }
  else if(strcmp(snakeBody[numOfBodyParts-1].direction, "DOWN")==0){
    snakeTail.x=bx-1;
    snakeTail.y=by-bh;
    snakeTail.direction="DOWN";
  }
  else if(strcmp(snakeBody[numOfBodyParts-1].direction, "LEFT")==0){
    snakeTail.x=bx+bw;
    snakeTail.y=by-1;
    snakeTail.direction="LEFT";
  }
  else if(strcmp(snakeBody[numOfBodyParts-1].direction, "RIGHT")==0){
    snakeTail.x=bx-bw;
    snakeTail.y=by;
    snakeTail.direction="RIGHT";
  }
  }

void (snakeBodyMovement)(int16_t speed ){
  for(int i=1; i<numOfBodyParts; i++){
    int x=snakeBody[i].x, y=snakeBody[i].y;
    snakeBody[i].oldx=snakeBody[i].x;snakeBody[i].oldx=snakeBody[i].y;
    if(strcmp(snakeBody[i-1].prevDirection, "UP")==0){
      if(y<=snakeBody[0].changey+9){
        changeBodyDirection(i);
      }
      snakeBody[i].y-=speed;
    }
    else if(strcmp(snakeBody[i-1].prevDirection, "DOWN")==0){
      if(y>=snakeBody[0].changey-9){
        changeBodyDirection(i);
      }
      snakeBody[i].y+=speed;
    }
    else if(strcmp(snakeBody[i-1].prevDirection, "LEFT")==0){
      if(x<=snakeBody[0].changex+9){
        changeBodyDirection(i);
      }
      snakeBody[i].x-=speed;
    }
    else if(strcmp(snakeBody[i-1].prevDirection, "RIGHT")==0){
      if(x>=snakeBody[0].changex-9){
        changeBodyDirection(i);
      }
      snakeBody[i].x+=speed;
    }
  }
  if(strcmp(snakeBody[numOfBodyParts-1].prevDirection, "UP")==0){
    if(snakeTail.y<=snakeBody[0].changey+9){
        changeTailDirection();
      }
      snakeTail.y-=speed;
  }
  else if(strcmp(snakeBody[numOfBodyParts-1].prevDirection, "DOWN")==0){
     if(snakeTail.y>=snakeBody[0].changey-9){
        changeTailDirection();
      }
      snakeTail.y+=speed;
  }
  else if(strcmp(snakeBody[numOfBodyParts-1].prevDirection, "LEFT")==0){
    if(snakeTail.x<=snakeBody[0].changey+9){
        changeTailDirection();
      }
      snakeTail.x-=speed;
  }
  else if(strcmp(snakeBody[numOfBodyParts-1].prevDirection, "RIGHT")==0){
    if(snakeTail.x>=snakeBody[0].changey-9){
        changeTailDirection();
      }
      snakeTail.x+=speed;
  }
  drawSnakeBody();
}

int (movement)(int16_t speed ){
    int x=snakeBody[0].x, y=snakeBody[0].y;
    snakeBody[0].oldx=snakeBody[0].x;snakeBody[0].oldy=snakeBody[0].y;
    if(strcmp(snakeBody[0].direction, "UP")==0){
        erase_xpm(snakeBody[0].imgUp, x, y, background.img);
        eraseSnakeBody();
        eraseSnakeTail();
        if(y+-speed<0){
          return 1;
        } 
        y-=speed;
        draw_xpm(snakeBody[0].imgUp, snakeBody[0].mapUp, x, y);
        snakeBodyMovement(speed);
        
    }
    else if(strcmp(snakeBody[0].direction, "DOWN")==0){
        erase_xpm(snakeBody[0].imgDown, x, y, background.img);
        eraseSnakeBody();
        eraseSnakeTail();
        if(y+snakeBody[0].imgUp.height+speed>v_res){
          return 1;
        } 
        y+=speed;
        draw_xpm(snakeBody[0].imgDown, snakeBody[0].mapDown, x, y);
        snakeBodyMovement(speed);
    }
    else if(strcmp(snakeBody[0].direction, "RIGHT")==0){
        erase_xpm(snakeBody[0].imgRight, x, y, background.img);
        eraseSnakeBody();
        eraseSnakeTail();
        if(x+snakeBody[0].imgRight.width+speed>h_res){
          return 1;
        } 
        x+=speed;
        draw_xpm(snakeBody[0].imgRight, snakeBody[0].mapRight, x, y);
        snakeBodyMovement(speed);
    }
    else if(strcmp(snakeBody[0].direction, "LEFT")==0){
        erase_xpm(snakeBody[0].imgLeft, x, y, background.img);
        eraseSnakeBody();
        eraseSnakeTail();
        if(y-speed<0){
          return 1;
        } 
        x-=speed;
        draw_xpm(snakeBody[0].imgLeft, snakeBody[0].mapLeft, x, y);
        snakeBodyMovement(speed);

    }
    snakeBody[0].y=y; snakeBody[0].x=x;
    return 0;
}
