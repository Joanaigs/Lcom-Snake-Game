
#include "instructions.h"


bool on_back=false;

void (init_instructions)(){
    instructionsMenu.map=xpm_load((xpm_map_t)menu_instructions_xpm, XPM_8_8_8, &(instructionsMenu.img));
    instructionsBack.map=xpm_load((xpm_map_t)instructions_back_xpm, XPM_8_8_8, &(instructionsBack.img));
}

int (menuInstructionsCollisions)(cursor *mouse_c){
    if(mouse_c->y>=522 && mouse_c->y<=566 && mouse_c->x>=306 && mouse_c->x<=487)
        return 1;
    return 0;
}

void (drawInstructionMenu)(){
    if(on_back)
        draw_xpm(instructionsBack.img, instructionsBack.map, 0, 0);
}

void (instructionsMenu)(cursor *mouse_c, struct packet *p){
    struct mouse_ev event = mouse_get_event(p);

    if(menuInstructionsCollisions(mouse_c)) {

        if (event.type == LB_RELEASED) {
            baseState = mainMenu;
            return 1;
        }
        if(!on_back){
            on_back = true;
            drawInstructionMenu();
            copy_buffer_to_mem();
            draw_xpm_video_mem(c->img, c->img.bytes, c->x, c->y);
        }
    }
    return 0;
}

int(instructionsLoop)() {
    cursor c;
    c.x = 200;
    c.y = 200;
    xpm_load((xpm_map_t)mouse_cursor, XPM_8_8_8, &(c.img));
    copy_buffer_to_mem();

    init_instructions();
    draw_xpm(instructionsMenu.img, instructionsMenu.map, 0, 0);

    message msg;
    int ipc_status, r;
    uint8_t irq_timer = 0, irq_mouse = 2;

    if (timer_subscribe(&irq_timer, 0)) return 1;
    if(mouse_subscribe(&irq_mouse, 1)) return 1;

    int good = 1;
    while (good) {
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) {
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    if (msg.m_notify.interrupts & irq_timer) {
                        copy_buffer_to_mem();
                        draw_xpm_video_mem(c.img, c.img.bytes, c.x, c.y);
                    }

                    if (msg.m_notify.interrupts & irq_mouse) {
                        mouse_ih();
                        if (mouse_number_bytes >= 3) {
                            struct packet p = parse_packet();
                            c.x += p.delta_x;
                            c.y -= p.delta_y;
                            if(instructionsMenu(&c, &p))
                                good=0;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        else {
        }
    }
    if (timer_unsubscribe_int())
        return 1;
    if (mouse_unsubscribe())
        return 1;
    return 0;
}