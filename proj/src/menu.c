#include "menu.h"
#include <stdbool.h>
#include <stdint.h>
#include <lcom/lcf.h>
#include "graphics.h"
#include "macros.h"
#include "images/menu_background.xpm"


void (drawMenu)(){
    xpm_image_t image_menu;
    uint8_t *image_menu_map;
    image_menu_map = xpm_load((xpm_map_t)menu_xpm, XPM_8_8_8, &(image_menu));
    draw_xpm(image_menu, image_menu_map, 0, 0);
}

int (menuOptionCollisions)(){
    return 0;
}
