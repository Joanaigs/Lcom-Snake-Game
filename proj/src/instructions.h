#ifndef G03_INSTRUCTIONS_H
#define G03_INSTRUCTIONS_H

#include <stdbool.h>
#include <stdint.h>
#include <lcom/lcf.h>
#include "cursor.h"

typedef struct{
    xpm_image_t img;
    uint8_t *map;
}instMap;


instMap instructions_menu;
instMap instructions_back;

void (init_instructions)();

int (instructionsMenu)(cursor *mouse_c, struct packet *p);

int (menuInstructionsCollisions)(cursor *mouse_c);

void (drawInstructionMenu)();

int (instructionsLoop)();

#endif //G03_INSTRUCTIONS_H
