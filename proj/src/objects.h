#ifndef __OBJECTS_H
#define __OBJECTS_H


#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <lcom/lcf.h>



/**
 * @brief struct that represents an object with their xpm image and position
 * 
 */
typedef struct{
    xpm_image_t img;
    uint8_t *map;
}object;

/**
 * @brief red apple object*/
object redAppleXpm;
/**
 * @brief brown apple object*/
object brownAppleXpm;
/**
 * @brief black apple object
 * */
object blackAppleXpm;
/**
 * @brief background object
 * */
object background;

/**
 * @brief image of the clock
 *
 */
object timeClock;
/**
 * @brief image of left half of the heart
 */
object leftHeart;
/**
 * @brief image of right half of the heart
 *
 */
object rightHeart;
/**
 * @brief image of number 1
 *
 */
object one;
/**
 * @brief image of number 2
 *
 */
object two;
/**
 * @brief image of number 3
 *
 */
object three;
/**
 * @brief image of number 4
 *
 */
object four;
/**
 * @brief image of number 5
 *
 */
object five;
/**
 * @brief image of number 6
 *
 */
object six;
/**
 * @brief image of number 7
 *
 */
object seven;
/**
 * @brief image of number 8
 *
 */
object eight;
/**
 * @brief image of number 9
 *
 */
object nine;
/**
 * @brief image of number 0
 *
 */
object zero;


/**
 * @brief initiates the objects
 *
 */
void init_xpms();

/**
 * @brief draws the background of the game
 *
 */
void drawBackground();

#endif /* __OBJECTS_H */
