#include "snake.h"
#include "graphics.h"
#include "header.h"
#include "images/cabeca_cobra_baixo.xpm"
#include "images/cabeca_cobra_cima.xpm"
#include "images/cabeca_cobra_dir.xpm"
#include "images/cabeca_cobra_esq.xpm"
#include "images/cauda-baixo.xpm"
#include "images/cauda-cima.xpm"
#include "images/cauda-direita.xpm"
#include "images/cauda-esquerda.xpm"
#include "images/corpo_cobra.xpm"
#include "images/corpo_cobra_H.xpm"
#include "images/corpo_cobra_V.xpm"
#include "objects.h"

int snakeLenght = 40;
int lives=3;
int numOfApplesEaten=3;
void(init_snake)() {
  snakeBody[0].mapLeft = xpm_load((xpm_map_t) cobra_esquerda_xpm, XPM_8_8_8, &snakeBody[0].imgLeft);
  snakeBody[0].mapRight = xpm_load((xpm_map_t) cobra_direita_xpm, XPM_8_8_8, &snakeBody[0].imgRight);
  snakeBody[0].mapDown = xpm_load((xpm_map_t) cobra_baixo_xpm, XPM_8_8_8, &snakeBody[0].imgDown);
  snakeBody[0].mapUp = xpm_load((xpm_map_t) cobra_cima_xpm, XPM_8_8_8, &snakeBody[0].imgUp);
  snakeBody[0].x = 200;
  snakeBody[0].y = 200;
  snakeBody[0].direction = "RIGHT";
  snakeBody[0].map = snakeBody[0].mapRight;
  snakeBody[0].img = snakeBody[0].imgRight;
  snakeBody[1].mapLeft = xpm_load((xpm_map_t) cobra_corpo_xpm, XPM_8_8_8, &snakeBody[1].imgLeft);
  snakeBody[1].mapRight = xpm_load((xpm_map_t) cobra_corpo_xpm, XPM_8_8_8, &snakeBody[1].imgRight);
  snakeBody[1].mapDown = xpm_load((xpm_map_t) cobra_corpo_xpm, XPM_8_8_8, &snakeBody[1].imgDown);
  snakeBody[1].mapUp = xpm_load((xpm_map_t) cobra_corpo_xpm, XPM_8_8_8, &snakeBody[1].imgUp);
  snakeBody[1].direction = "RIGHT";
  snakeBody[1].map = snakeBody[1].mapRight;
  snakeBody[1].img = snakeBody[1].imgRight;
  snakeBody[1].x = snakeBody[0].x - snakeLenght;
  snakeBody[1].y = snakeBody[0].y;
  numOfBodyParts = 2;
  snakeTail.mapLeft = xpm_load((xpm_map_t) tail_left_xpm, XPM_8_8_8, &snakeTail.imgLeft);
  snakeTail.mapRight = xpm_load((xpm_map_t) tail_right_xpm, XPM_8_8_8, &snakeTail.imgRight);
  snakeTail.mapDown = xpm_load((xpm_map_t) tail_down_xpm, XPM_8_8_8, &snakeTail.imgDown);
  snakeTail.mapUp = xpm_load((xpm_map_t) tail_up_xpm, XPM_8_8_8, &snakeTail.imgUp);
  snakeBody[2].map = snakeTail.mapRight;
  snakeBody[2].img = snakeTail.imgRight;
  snakeBody[2].x = snakeBody[1].x - snakeLenght;
  snakeBody[2].y = snakeBody[1].y;
  snakeBody[2].direction = "RIGHT";
}

void(drawSnakeBody)() {
  for (int i = 0; i <= numOfBodyParts; i++) {
    draw_xpm(snakeBody[i].img, snakeBody[i].map, snakeBody[i].x, snakeBody[i].y);
  }
}

void(eraseSnakeBody)() {
  for (int i = 0; i <= numOfBodyParts; i++) {
    erase_xpm(snakeBody[i].img, snakeBody[i].x, snakeBody[i].y, background.img);
  }
}

void(addBodyPart)() {
  erase_xpm(snakeBody[numOfBodyParts].img, snakeBody[numOfBodyParts].x, snakeBody[numOfBodyParts].y, background.img);
  numOfBodyParts++;
  int i = numOfBodyParts - 1;
  snakeBody[i].mapLeft = xpm_load((xpm_map_t) cobra_corpo_xpm, XPM_8_8_8, &snakeBody[i].imgLeft);
  snakeBody[i].mapRight = xpm_load((xpm_map_t) cobra_corpo_xpm, XPM_8_8_8, &snakeBody[i].imgRight);
  snakeBody[i].mapDown = xpm_load((xpm_map_t) cobra_corpo_xpm, XPM_8_8_8, &snakeBody[i].imgDown);
  snakeBody[i].mapUp = xpm_load((xpm_map_t) cobra_corpo_xpm, XPM_8_8_8, &snakeBody[i].imgUp);
  if (strcmp(snakeBody[i - 1].direction, "UP") == 0) {
    snakeBody[i].x = snakeBody[i - 1].x;
    snakeBody[i].y = snakeBody[i - 1].y + snakeLenght;
    snakeBody[i].direction = "UP";
    snakeBody[i].map = snakeBody[i].mapUp;
    snakeBody[i].img = snakeBody[i].imgUp;
    snakeBody[i + 1].map = snakeTail.mapUp;
    snakeBody[i + 1].img = snakeTail.imgUp;
    snakeBody[i + 1].x = snakeBody[i].x;
    snakeBody[i + 1].y = snakeBody[i].y + snakeLenght;
    snakeBody[i + 1].direction = "UP";
  }
  else if (strcmp(snakeBody[i - 1].direction, "DOWN") == 0) {
    snakeBody[i].x = snakeBody[i - 1].x;
    snakeBody[i].y = snakeBody[i - 1].y - snakeLenght;
    snakeBody[i].direction = "DOWN";
    snakeBody[i].map = snakeBody[i].mapDown;
    snakeBody[i].img = snakeBody[i].imgDown;
    snakeBody[i + 1].map = snakeTail.mapDown;
    snakeBody[i + 1].img = snakeTail.imgDown;
    snakeBody[i + 1].x = snakeBody[i].x;
    snakeBody[i + 1].y = snakeBody[i].y - snakeLenght;
    snakeBody[i + 1].direction = "DOWN";
  }
  else if (strcmp(snakeBody[i - 1].direction, "LEFT") == 0) {
    snakeBody[i].x = snakeBody[i - 1].x + snakeLenght;
    snakeBody[i].y = snakeBody[i - 1].y;
    snakeBody[i].direction = "LEFT";
    snakeBody[i].map = snakeBody[i].mapLeft;
    snakeBody[i].img = snakeBody[i].imgLeft;
    snakeBody[i + 1].map = snakeTail.mapLeft;
    snakeBody[i + 1].img = snakeTail.imgLeft;
    snakeBody[i + 1].x = snakeBody[i].x + snakeLenght;
    snakeBody[i + 1].y = snakeBody[i].y;
    snakeBody[i + 1].direction = "LEFT";
  }
  else if (strcmp(snakeBody[i - 1].direction, "RIGHT") == 0) {
    snakeBody[i].x = snakeBody[i - 1].x - snakeLenght;
    snakeBody[i].y = snakeBody[i - 1].y;
    snakeBody[i].direction = "RIGHT";
    snakeBody[i].map = snakeBody[i].mapRight;
    snakeBody[i].img = snakeBody[i].imgRight;
    snakeBody[i + 1].map = snakeTail.mapRight;
    snakeBody[i + 1].img = snakeTail.imgRight;
    snakeBody[i + 1].x = snakeBody[i].x - snakeLenght;
    snakeBody[i + 1].y = snakeBody[i].y;
    snakeBody[i + 1].direction = "RIGHT";
  }
  draw_xpm(snakeBody[i].img, snakeBody[i].map, snakeBody[i].x, snakeBody[i].y);
  draw_xpm(snakeBody[i + 1].img, snakeBody[i + 1].map, snakeBody[i + 1].x, snakeBody[i + 1].y);
}

int(colisionWithItSelf)() {
  for (int i = 1; i <= numOfBodyParts; i++) {
      if ((snakeBody[0].x == snakeBody[i].x) && snakeBody[0].y == snakeBody[i].y){
          return 1;
      }
  }
  return 0;
}

int takelive(int n){
  if(lives<=0){
    return 1;
  }
  eraseHearts(lives, 620, 20);
  lives-=n;
  drawHeader();
  return 0;
}

void(moveBodyParts)() {
  for (int i = numOfBodyParts; i > 0; i--) {
    snakeBody[i].x = snakeBody[i - 1].x;
    snakeBody[i].y = snakeBody[i - 1].y;
    snakeBody[i].direction = snakeBody[i - 1].direction;
    if (strcmp(snakeBody[i].direction, "UP") == 0) {
      snakeBody[i].img = snakeBody[i].imgUp;
      snakeBody[i].map = snakeBody[i].mapUp;
      if (i == numOfBodyParts) {
        snakeBody[i].img = snakeTail.imgUp;
        snakeBody[i].map = snakeTail.mapUp;
      }
    }
    else if (strcmp(snakeBody[i].direction, "DOWN") == 0) {
      snakeBody[i].img = snakeBody[i].imgDown;
      snakeBody[i].map = snakeBody[i].mapDown;
      if (i == numOfBodyParts) {
        snakeBody[i].img = snakeTail.imgDown;
        snakeBody[i].map = snakeTail.mapDown;
      }
    }
    else if (strcmp(snakeBody[i].direction, "RIGHT") == 0) {
      snakeBody[i].img = snakeBody[i].imgRight;
      snakeBody[i].map = snakeBody[i].mapRight;
      if (i == numOfBodyParts) {
        snakeBody[i].img = snakeTail.imgRight;
        snakeBody[i].map = snakeTail.mapRight;
      }
    }
    else if (strcmp(snakeBody[i].direction, "LEFT") == 0) {
      snakeBody[i].img = snakeBody[i].imgLeft;
      snakeBody[i].map = snakeBody[i].mapLeft;
      if (i == numOfBodyParts) {
        snakeBody[i].img = snakeTail.imgLeft;
        snakeBody[i].map = snakeTail.mapLeft;
      }
    }
  }
}

int(movement)(int16_t speed) {
  eraseSnakeBody();
  moveBodyParts();
  if (strcmp(snakeBody[0].direction, "UP") == 0) {
    if (snakeBody[0].y - speed  < 120) {
      return 1;
    }
    snakeBody[0].y -= speed;
  }
  else if (strcmp(snakeBody[0].direction, "DOWN") == 0) {
    if (snakeBody[0].y + snakeLenght + speed > vmi_p.YResolution - 40) {
      return 1;
    }
    snakeBody[0].y += speed;
  }
  else if (strcmp(snakeBody[0].direction, "RIGHT") == 0) {
    if (snakeBody[0].x + snakeLenght + speed > vmi_p.XResolution - 40) {
      return 1;
    }
    snakeBody[0].x += speed;
  }
  else if (strcmp(snakeBody[0].direction, "LEFT") == 0) {
    if (snakeBody[0].x - speed < 40) {
      return 1;
    }
    snakeBody[0].x -= speed;
  }
  if(colisionWithItSelf()) return 1;
  drawSnakeBody();
  return 0;
}
