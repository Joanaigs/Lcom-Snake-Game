#include <stdbool.h>
#include <stdint.h>
#include <lcom/lcf.h>
#include "cursor.h"

typedef struct{
    xpm_image_t img;
    uint8_t *map;
}menuMap;

menuMap main_menu;
menuMap sp_menu;
menuMap mp_menu;
menuMap inst_menu;
menuMap exit_menu;
menuMap continue_colored;
menuMap continu;

void (drawMenu)();

int (menu)(cursor *mouse_c, struct packet *p);

int (menuOptionCollisions)(cursor *mouse_c);

int (menuInstructionsCollisions)(cursor *mouse_c);

uint8_t* (chooseButton)(xpm_image_t* image_menu);

int (mainMenuLoop)();

