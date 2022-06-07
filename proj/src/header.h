#include <lcom/lcf.h>

int gameTime;

void (init_header)();
void drawHeader();
void draw_number(int number, int x, int y);
void eraseTime();
void eraseAppleNumb();
void eraseHearts(double number, int x, int y);

typedef struct{
    xpm_image_t img;
    uint8_t *map;
}objectH;

objectH timeClock;
objectH leftHeart;
objectH rightHeart;
objectH one;
objectH two;
objectH three;
objectH four;
objectH five;
objectH six;
objectH seven;
objectH eight;
objectH nine;
objectH zero;
