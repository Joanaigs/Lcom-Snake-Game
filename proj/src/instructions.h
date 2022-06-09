#ifndef G03_INSTRUCTIONS_H
#define G03_INSTRUCTIONS_H

#include "gameOver.h"
#include "graphics.h"
#include "header.h"
#include "i8042.h"
#include "images/menu_instructions.xpm"
#include "images/instructions_back.xpm"
#include "images/mouse_cursor.xpm"
#include "keyboard.h"
#include "objects.h"
#include "snake.h"
#include "timer.h"
#include "mouse.h"
#include "menu.h"


menuMap instructionsMenu;
menuMap instructionsBack;

void (init_instructions)();

void (instructionsMenu)(cursor *mouse_c, struct packet *p);

int (menuInstructionsCollisions)(cursor *mouse_c);

void (drawInstructionMenu)();

int (instructionsLoop)();

#endif //G03_INSTRUCTIONS_H
