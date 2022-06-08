#include <stdbool.h>
#include <stdint.h>
#include <lcom/lcf.h>
#include "cursor.h"



void (drawMenu)();

void (menu)(cursor *mouse_c, struct packet *p);

void (instructionsMenu)();

int (continueMenu)(cursor *mouse_c, struct packet *p);

void (pauseMenu)();

int (menuOptionCollisions)(cursor *mouse_c);

int (menuContinueCollisions)(cursor *mouse_c);

uint8_t* (chooseButton)(xpm_image_t* image_menu);

