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
}menuMap;

/**
 * @brief image of the main menu page
 * 
 */
menuMap main_menu;

/**
 * @brief image of the main menu page with the singlePlayer colored
 * 
 */
menuMap sp_menu;

/**
 * @brief image of the main menu page with the multiPlayer colored
 * 
 */
menuMap mp_menu;

/**
 * @brief image of the main menu page with the intructions colored
 * 
 */
menuMap inst_menu;

/**
 * @brief image of the main menu page with the exit colored
 * 
 */
menuMap exit_menu;

/**
 * @brief Iniciates all the menu object by reading their xpm
 * 
 */
void init_menu();

/**
 * @brief changes the background with the right button colored
 * 
 */
void drawMenu();

/**
 * @brief Deals with the result of movement of the mouse, changing te state of the game if the any button is clicked and changing the color of the button if the mouse is on top of it
 * 
 * @param mouse_c mouse object
 * @param p packet with the information of the mouse after movement
 * @return int 1 if the state of the program was changed
 */
int menu(cursor *mouse_c, struct packet *p);

/**
 * @brief  Checks if the mouse is on top of any button
 *  
 * @param mouse_c mouse object
 * @return int 1 if its within the button limits
 */
int menuOptionCollisions(cursor *mouse_c);

/**
 * @brief Loop of the main Menu page that uses mouse, and timer devices
 * 
 * @return int 1 if an error has occured 
 */
int mainMenuLoop();

