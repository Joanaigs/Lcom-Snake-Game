#include <lcom/lcf.h>

int gameTime;

/**
 * @brief Iniciates all the header object by reading their xpm
 * 
 */
void init_header();

/**
 * @brief Draws the top part of the game with the heart, time and apples information
 * 
 */
void drawHeader();

/**
 * @brief Draws on screen the number given
 * 
 * @param number the number to be drawn
 * @param x column to start drawing from
 * @param y line to start drawing from
 */
void draw_number(int number, int x, int y);

/**
 * @brief draws the number of lives on the screen
 * 
 * @param number the number to be drawn
 * @param x column to start drawing from
 * @param y line to start drawing from
 */
void drawHearts(double number, int x, int y);

/**
 * @brief erases the number on the screen
 * 
 * @param number the number to be erased
 * @param x column to start erasing from
 * @param y line to start erasing from
 */
void erase_number(int number, int x, int y);

/**
 * @brief erases the time on the screen
 * 
 */
void eraseTime();

/**
 * @brief erases the number of apples on screen
 * 
 */
void eraseAppleNumb();

/**
 * @brief erases the number of hearts on the screen
 * 
 * @param number the number to be erased
 * @param x column to start erasing from
 * @param y line to start erasing from
 */
void eraseHearts(double number, int x, int y);

/**
 * @brief struct of an xpm
 * 
 */
typedef struct{
    xpm_image_t img;
    uint8_t *map;
}objectH;

/**
 * @brief image of the clock
 * 
 */
objectH timeClock;

/**
 * @brief image of left half of the heart
 */
objectH leftHeart;

/**
 * @brief image of right half of the heart
 * 
 */
objectH rightHeart;

/**
 * @brief image of number 1
 * 
 */
objectH one;

/**
 * @brief image of number 2
 * 
 */
objectH two;

/**
 * @brief image of number 3
 * 
 */
objectH three;

/**
 * @brief image of number 4
 * 
 */
objectH four;

/**
 * @brief image of number 5
 * 
 */
objectH five;

/**
 * @brief image of number 6
 * 
 */
objectH six;

/**
 * @brief image of number 7
 * 
 */
objectH seven;

/**
 * @brief image of number 8
 * 
 */
objectH eight;

/**
 * @brief image of number 9
 * 
 */
objectH nine;

/**
 * @brief image of number 0
 * 
 */
objectH zero;
