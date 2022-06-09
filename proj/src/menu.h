#include <stdbool.h>
#include <stdint.h>
#include <lcom/lcf.h>
#include "cursor.h"

typedef struct{
    xpm_image_t img;
    uint8_t *map;
}menuMaps;

menuMaps main_menu;
menuMaps sp_menu;
menuMaps mp_menu;
menuMaps inst_menu;
menuMaps exit_menu;

void (drawMenu)();

int (menu)(cursor *mouse_c, struct packet *p);

int (continueMenu)(cursor *mouse_c, struct packet *p);

int (menuOptionCollisions)(cursor *mouse_c);

int (menuContinueCollisions)(cursor *mouse_c);

int (menuInstructionsCollisions)(cursor *mouse_c);

uint8_t* (chooseButton)(xpm_image_t* image_menu);

int (mainMenuLoop)();

