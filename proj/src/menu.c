#include "menu.h"
#include <stdbool.h>
#include <stdint.h>
#include <lcom/lcf.h>
#include "graphics.h"
#include "macros.h"
#include "mouse.h"
#include "images/menu_background.xpm"
#include "images/menu_instructions.xpm"
#include "images/menu_multiPlayer.xpm"
#include "images/menu_singlePlayer.xpm"
#include "images/menu_exit.xpm"



static bool on_instructions=false, on_singlePlayer=false, on_multiPlayer=false, on_exit=false;

uint8_t* (chooseButton)(xpm_image_t *image_menu){
    uint8_t *image_menu_map;

    if(on_singlePlayer) 
        image_menu_map = xpm_load((xpm_map_t)menu_singlePlayer_xpm, XPM_8_8_8, (image_menu));
    
    else if(on_multiPlayer) 
        image_menu_map = xpm_load((xpm_map_t)menu_multiPlayer_xpm, XPM_8_8_8, (image_menu));

    else if(on_instructions) 
        image_menu_map = xpm_load((xpm_map_t)menu_instructions_xpm, XPM_8_8_8, (image_menu));
    
    else if(on_exit)  
        image_menu_map = xpm_load((xpm_map_t)menu_exit_xpm, XPM_8_8_8, (image_menu));
    
    else
        image_menu_map = xpm_load((xpm_map_t)menu_xpm, XPM_8_8_8, (image_menu));
    
    return image_menu_map;
}


void (drawMenu)(){
    xpm_image_t image_menu;
    uint8_t *image_menu_map;
    image_menu_map = chooseButton(&image_menu);
    draw_xpm(image_menu, image_menu_map, 0, 0);
    copy_buffer_to_mem();
}

int (menuOptionCollisions)(){
    return 0;
}
