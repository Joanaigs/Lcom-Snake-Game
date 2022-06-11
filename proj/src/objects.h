#ifndef __OBJECTS_H
#define __OBJECTS_H


#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <lcom/lcf.h>



/**
 * @brief enum with the different types of apples
 */
enum appleType{red, brown, black};

/**
 * @brief struct that represents an object with their xpm image and position
 * 
 */
typedef struct{
    int x;
    int y;
    xpm_image_t img;
    uint8_t *map;
}object;

/** @brief red apple object*/
object redAppleXpm;
/** @brief brown apple object*/
object brownAppleXpm;
/** @brief black apple object*/
object blackAppleXpm;
/** @brief background object*/
object background;
/** @brief number of apples eaten*/
int nBrownApples;

/**
 * @brief initiates the objects of the apples
 * 
 */
void init_xpms();

/**
 * @brief draws background of the game
 * 
 */
void drawBackground();

/**
 * @brief Gets the xpm object of the right apple type
 * 
 * @param type appleType enum
 * @return object the apple
 */
object get_xpm(enum appleType type);

/**
 * @brief struct of an apple object
 * 
 */
typedef struct {
    int x_pos;
    int y_pos;
    object appleXpm;
    enum appleType type;
}Apple;

/** @brief an array of the apples on the game */
Apple applesArray[195];
/** @brief number of apples placed */
int numApples;

/**
 * @brief Creates an apple and places it on the array
 * 
 * @param apple struck of the object Apple
 * @param x_pos column to place apple
 * @param y_pos line to place apple
 * @param type enum appleType of the apple in question
 */
void initApple(Apple *apple, int x_pos, int y_pos, enum appleType type);

/**
 * @brief places an apple in a random place
 * 
 * @param apple the object of the apple that is created and placed
 * @param type  enum appleType of the apple in question
 */
void initRandomApple(Apple *apple, enum appleType type);

/**
 * @brief Draws the apple in question
 * 
 * @param apple apple to be drawn
 */
void drawApple(Apple apple);

/**
 * @brief Verifies if an apple is in that possition or not
 * 
 * @param x column of the position to be checked
 * @param y line of the position to be checked
 * @return int 
 */
int isApple(int x, int y);

/**
 * @brief places an apple within a square of the background
 * 
 * @param x column of the position to be placed
 * @param y line of the position to be cplaced
 * @param a enum appleType of the apple in question
 */
void placeApple(int x, int y, enum appleType a);



#endif /* __OBJECTS_H */
