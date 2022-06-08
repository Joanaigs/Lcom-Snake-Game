#include <stdbool.h>
#include <stdint.h>
#include <lcom/lcf.h>
#include "cursor.h"

typedef struct{
    xpm_image_t img;
    uint8_t *map;
}menuu;

menuu main_menu;
menuu sp_menu;
menuu mp_menu;
menuu inst_menu;
menuu exit_menu;

void (drawMenu)();

int (menu)(cursor *mouse_c, struct packet *p);

void (instructionsMenu)();

int (continueMenu)(cursor *mouse_c, struct packet *p);

void (pauseMenu)();

int (menuOptionCollisions)(cursor *mouse_c);

int (menuContinueCollisions)(cursor *mouse_c);

uint8_t* (chooseButton)(xpm_image_t* image_menu);

int (mainMenuLoop)();
