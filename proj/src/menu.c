#include "menu.h"
#include <stdbool.h>
#include <stdint.h>
#include <lcom/lcf.h>
#include "graphics.h"
#include "mouse.h"
#include "proj.h"
#include "macros.h"
#include "cursor.h"
#include "images/menu_background.xpm"
#include "images/menu_instructions.xpm"
#include "images/menu_multiPlayer.xpm"
#include "images/menu_singlePlayer.xpm"
#include "images/menu_exit.xpm"



extern enum BaseState baseState;
extern cursor *mouse_c;
extern struct packet p;


//static struct mouse_ev * mouseEvent;
static bool choose_instructions=false, choose_singlePlayer=false, choose_multiPlayer=false, choose_exit=false; //choose_continue=false;
bool on_instructions=false, on_singlePlayer=false, on_multiPlayer=false, on_exit=false;


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
    if(mouse_c->y>=240 && mouse_c->y<=297 && mouse_c->x>=194 && mouse_c->x<=371)
        return 1;
    else if(mouse_c->y>=240 && mouse_c->y<=297 && mouse_c->x>=398 && mouse_c->x<=575)
        return 2;
    else if(mouse_c->y>=325 && mouse_c->y<=382 && mouse_c->x>=185 && mouse_c->x<=566)
        return 3;
    else if(mouse_c->y>=415 && mouse_c->y<=472 && mouse_c->x>=185 && mouse_c->x<=566)
        return 4;
    return 0;
}

int (menuContinueCollisions)(){
    if(mouse_c->y>=777 && mouse_c->y<=860 && mouse_c->x>=685 && mouse_c->x<=909)
        return 1;
    return 0;
}

void (menu_ih)(){
    struct mouse_ev event = mouse_get_event(&p);

    switch (menuOptionCollisions()) {
        case 1:
            if(event.type == LB_RELEASED) {
                choose_singlePlayer=true;
                break;
            }
            if(!on_singlePlayer){
                on_singlePlayer = true;
                drawMenu();
            }
            break;
        case 2:
            if(event.type == LB_RELEASED) {
                choose_multiPlayer=true;
                break;
            }
            if(!on_multiPlayer){
                on_multiPlayer = true;
                drawMenu();
            }
            break;
        case 3:
            if(event.type == LB_RELEASED) {
                choose_instructions=true;
                break;
            }
            if(!on_instructions){
                on_instructions = true;
                drawMenu();
            }
            break;
        case 4:
            if(event.type == LB_RELEASED) {
                choose_exit=true;
                break;
            }
            if(!on_exit){
                on_exit = true;
                drawMenu();
            }
            break;

        case 0:
            if(on_singlePlayer){
                on_singlePlayer = true;
                drawMenu();
            }
            else if(on_multiPlayer){
                on_multiPlayer = false;
                drawMenu();
            }
            else if(on_instructions){
                on_instructions = false;
                drawMenu();
            }
            else if(on_exit){
                on_exit = false;
                drawMenu();
            }
            break;
    }

    if(choose_singlePlayer){
        baseState = singlePlayer;
    }
    else if(choose_multiPlayer){
        baseState = multiPlayer;
    }
    else if(choose_instructions){
        baseState = instructions;
    }
    else if(choose_exit){
        baseState = leave;
    }
}

void (continueMenu_ih)(){
    struct mouse_ev event = mouse_get_event(&p);

    switch (menuContinueCollisions()) {
        case 1:
            if(event.type == LB_RELEASED) {
                choose_singlePlayer=true;
                break;
            }
            if(!on_singlePlayer){
                on_singlePlayer = true;
                drawMenu();
            }
            break;
        case 0:
            if(on_singlePlayer){
                on_singlePlayer = true;
                drawMenu();
            }
    }
}
