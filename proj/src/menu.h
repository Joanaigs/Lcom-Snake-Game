#include <stdbool.h>
#include <stdint.h>
#include <lcom/lcf.h>


void (drawMenu)();

void (menu_ih)();

void (instructionsMenu_ih)();

void (continueMenu_ih)();

void (pauseMenu_ih)();

int (menuOptionCollisions)();

void (drawMenu)();

uint8_t* (chooseButton)(xpm_image_t* image_menu);
