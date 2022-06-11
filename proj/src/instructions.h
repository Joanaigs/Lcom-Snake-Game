#ifndef G03_INSTRUCTIONS_H
#define G03_INSTRUCTIONS_H

#include <stdbool.h>
#include <stdint.h>
#include <lcom/lcf.h>
#include "cursor.h"

/**
 * @brief represents a xpm image
 * 
 */
typedef struct{
    xpm_image_t img;
    uint8_t *map;
}instMap;

/**
 * @brief image of the instruction page
 * 
 */
instMap instructions_menu;

/**
 * @brief image of the instruction with different color button black
 * 
 */
instMap instructions_back;

/**
 * @brief Iniciates all the instructions object by reading their xpm
 * 
 */
void init_instructions();

/**
 * @brief Deals with the result of movement of the mouse, changing te state of the game if the button back is clicked and changing the color of the button if the mouse is on top of it
 * 
 * @param mouse_c mouse object
 * @param p packet with the information of the mouse after movement
 * @return int 1 if the state of the program was changed
 */
int instructionsMenu(cursor *mouse_c, struct packet *p);

/**
 * @brief  Checks if the mouse is on top of the button back
 *  
 * @param mouse_c mouse object
 * @return int 1 if its within the button limits
 */
int menuInstructionsCollisions(cursor *mouse_c);

/**
 * @brief Loop of the instruction page that uses mouse, and timer devices
 * 
 * @return int 1 if an error has occured 
 */
int instructionsLoop();

#endif //G03_INSTRUCTIONS_H
