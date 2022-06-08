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
#include "images/gameOver.xpm"


static bool choose_instructions=false, choose_singlePlayer=false, choose_multiPlayer=false, choose_exit=false, choose_continue=false;
bool on_instructions=false, on_singlePlayer=false, on_multiPlayer=false, on_exit=false, on_continue=false;

void (drawMenu)(){
    xpm_image_t image_menu;
    uint8_t *image_menu_map;
    image_menu_map = xpm_load((xpm_map_t)menu_xpm, XPM_8_8_8, &(image_menu));
    draw_xpm(image_menu, image_menu_map, 0, 0);
    copy_buffer_to_mem();
}


int (menuOptionCollisions)(cursor *mouse_c){
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

int (menuContinueCollisions)(cursor *mouse_c){
    if(mouse_c->y>=777 && mouse_c->y<=860 && mouse_c->x>=685 && mouse_c->x<=909)
        return 1;
    return 0;
}

void (menu)(cursor *mouse_c, struct packet *p){
    struct mouse_ev event = mouse_get_event(p);

    switch (menuOptionCollisions(mouse_c)) {
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

void (continueMenu)(cursor *mouse_c, struct packet *p){
    struct mouse_ev event = mouse_get_event(p);

    switch (menuContinueCollisions(mouse_c)) {
        case 1:
            if (event.type == LB_RELEASED) {
                choose_continue = true;
                break;
            }
            if (!on_continue) {
                on_continue = true;
                drawMenu();
            }
            break;
        case 0:
            if (on_continue) {
                on_continue = true;
                xpm_image_t img;
                uint8_t *map = xpm_load((xpm_map_t) game_over_xpm, XPM_8_8_8, &img);
                int x = (h_res - img.width) / 2;
                int y = (v_res + 120 - img.height) / 2;
                draw_xpm(img, map, x, y);
            }
    }
    if(choose_continue)
        baseState = mainMenu;
}
