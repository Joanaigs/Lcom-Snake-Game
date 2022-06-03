#include "mouse.h"
#include <stdbool.h>
#include <stdint.h>
#include <lcom/lcf.h>
#include "../../lab4/i8042.h"

int hook_idR=0;
int mouse_number_bytes=0;
uint8_t command;

struct mouse_ev event_mouse;


int (mouse_subscribe)(uint8_t *bit_no){
    *bit_no=BIT(hook_idR);
    return sys_irqsetpolicy(MOUSE_IRQ,IRQ_REENABLE|IRQ_EXCLUSIVE,&hook_idR);
}

struct packet (parse_packet)(){
    struct packet pp;
    pp.bytes[0] = mouse[0];
    pp.bytes[1] = mouse[1];
    pp.bytes[2] = mouse[2];
    pp.rb       = pp.bytes[0] & RIGHT_BUTTON;
    pp.mb       = pp.bytes[0] & MIDDLE_BUTTON;
    pp.lb       = pp.bytes[0] & LEFT_BUTTON;
    pp.delta_x  = (int16_t)(((0xFF * ((mouse[0] & MSB_X_DELTA) != 0))<<8) |  pp.bytes[1]);
    pp.delta_y  = (int16_t)(((0xFF * ((mouse[0] & MSB_Y_DELTA) != 0))<<8) |  pp.bytes[2]);
    pp.x_ov     = pp.bytes[0] & X_OVERFLOW;
    pp.y_ov     = pp.bytes[0] & Y_OVERFLOW;
    return pp;
}

void (mouse_ih)(){
    if(mouse_number_bytes>=3) mouse_number_bytes=0;
    if(util_sys_inb(STATUS_REG, &statusCode))
                      return;
    if((statusCode & PARITY_BIT) || (statusCode & TIME_OUT_BIT)){
        printf("error");
        return;
    }
    if(!(statusCode & OBF) || !(statusCode & AUX_MOUSE))
      return;
    if(util_sys_inb(OUTPUT_BUF, &scanCode))
        printf("error");
     mouse[mouse_number_bytes] = scanCode;
     mouse_number_bytes++;
}	

int (mouse_unsubscribe)(){
    return sys_irqrmpolicy(&hook_idR);
}

void (kbc_restore_mouse)() {
  // Issuing a command to get the command byte
  for(int i=0; i<5; i++) {
    util_sys_inb(STATUS_REG, &statusCode); /* assuming it returns OK */
    /* loop while 8042 input buffer is not empty */
    if ((statusCode & IN_BUF_FULL) == 0) {
      sys_outb(KBC_CMD, READ_KBC_CMD); /* no args command */
      break;
    }
    tickdelay(micros_to_ticks(DELAY));
  }
  for(int i=0; i<5; i++) {
    util_sys_inb(STATUS_REG, &statusCode); /* assuming it returns OK */
    /* loop while 8042 output buffer is empty */
    if (statusCode & OBF) {
      util_sys_inb(OUTPUT_BUF, &command); /* ass. it returns OK */
      if ((statusCode & (PARITY_BIT | TIME_OUT_BIT)) != 0)
        continue;
    }
    tickdelay(micros_to_ticks(DELAY));
  }
  command = command | INT_MOU;
  //Issue new command
  for(int i=0; i<5; i++) {
    util_sys_inb(STATUS_REG, &statusCode); /* assuming it returns OK */
    /* loop while 8042 input buffer is not empty */
    if ((statusCode & IN_BUF_FULL) == 0) {
      sys_outb(KBC_CMD, WRITE_KBC_CMD); //write commands
      sys_outb(KBC_CMD_ARG, command); //write command argument
      break;
    }
    tickdelay(micros_to_ticks(DELAY));
  }

}

void (restoreCursor)() {
    uint32_t* map = (uint32_t*) background_menu.bytes;

    for (int i = cursor->x; i <= cursor->x + cursor->img.width; i++) {
        for (int j = cursor->y; j <= cursor->y + cursor->img.height; j++) {
            if (i < (int)hres - 1 && j < (int)vres - 1)
                changePixelColor(i,j,*(map + i + j * hres));
        }
    }
}

Cursor *cursor;

Cursor * (load_cursor)() {
    cursor = (Cursor *) malloc(sizeof(Cursor));
    xpm_load(cursor_xpm, XPM_8_8_8_8, &cursor->img);

    cursor->x = 300;
    cursor->y = 400;
    return cursor;
}

void mouse_update(struct packet * pp) {

    restoreCursor();

    if (pp->delta_y > 0) {
        if (cursor->y - pp->delta_y < 0)
            cursor->y = 0;
        else
            cursor->y -= pp->delta_y;
    } else if (pacote->delta_y < 0) {
        if (cursor->y + cursor->img.height - pacote->delta_y > (int) vres)
            cursor->y = (int) vres - cursor->img.height;
        else
            cursor->y -= pacote->delta_y;
    }
    if (pp->delta_x < 0 pp->delta_x > 0) {
        if (cursor->x + pacote->delta_x < 0)
            cursor->x = 0;
        else
            cursor->x += pacote->delta_x;
    } else if (pp->delta_x > 0) {
        if (cursor->x + pacote->delta_x > (int) hres - cursor->img.width)
            cursor->x = (int) hres - cursor->img.width;
        else
            cursor->x += pacote->delta_x;
    }
}

enum states {
    INITIAL,
    UP,
    VERTEX,
    DOWN,
    FINAL
};

struct mouse_ev* (mouse_get_event)(struct packet *pp) {
    static bool lbtn_pressed = false, rbtn_pressed = false, mbtn_pressed = false;

    event_mouse.delta_x = pp->delta_x;
    event_mouse.delta_y = pp->delta_y;

    if (!lbtn_pressed && pp->lb && !rbtn_pressed && !mbtn_pressed && !pp->mb && !pp->rb) {
        lbtn_pressed = true;
        event_mouse.type = LB_PRESSED;
    }
    else if (!rbtn_pressed && pp->rb && !lbtn_pressed && !mbtn_pressed && !pp->mb && !pp->lb) {
        rbtn_pressed = true;
        event_mouse.type = RB_PRESSED;
    }
    else if (lbtn_pressed && !pp->lb && !rbtn_pressed && !mbtn_pressed && !pp->mb && !pp->rb) {
        lbtn_pressed = false;
        event_mouse.type = LB_RELEASED;
    }
    else if (rbtn_pressed && !pp->rb && !lbtn_pressed && !mbtn_pressed && !pp->mb && !pp->lb) {
        rbtn_pressed = false;
        event_mouse.type = RB_RELEASED;
    }
    else if (!mbtn_pressed && pp->mb) {
        mbtn_pressed = true;
        event_mouse.type = BUTTON_EV;
    }
    else if(mbtn_pressed && !pp->mb) {
        mbtn_pressed = false;
        event_mouse.type = BUTTON_EV;
    }
    else
        event_mouse.type = MOUSE_MOV;

    return &event_mouse;
}


int (state_machine)(struct mouse_ev* event, uint8_t x_len, uint8_t tolerance) {

    static enum states state = INITIAL;
    static int response = 1;
    static int x_length = 0;
    static int y_length = 0;

    if (event == NULL)
        return response;

    switch (state) {
        case INITIAL:
            if (event->type == LB_PRESSED)
                state = UP;
            break;
        case UP:
            if (event->type == MOUSE_MOV) {
                if (event->delta_x < -tolerance || event->delta_y < -tolerance) {
                    state = INITIAL;
                    x_length = 0;
                    y_length = 0;
                    break;
                }

                x_length += event->delta_x;
                y_length += event->delta_y;
            } else if (event->type == LB_RELEASED) {
                if (y_length < x_length || x_length < x_len) {
                    state = INITIAL;
                    x_length = 0;
                    y_length = 0;
                    break;
                }

                state = VERTEX;
                x_length = 0;
                y_length = 0;
            } else {
                state = INITIAL;
                x_length = 0;
                y_length = 0;
            }
            break;
        case VERTEX:
            if (event->type == MOUSE_MOV) {
                x_length += event->delta_x;
                y_length += event->delta_y;
                if (abs(x_length) > tolerance || abs(y_length) > tolerance) {
                    state = INITIAL;
                    x_length = 0;
                    y_length = 0;
                }
            } else if (event->type == RB_PRESSED) {
                state =DOWN;
                x_length = 0;
                y_length = 0;
            } else if (event->type == LB_PRESSED) {
                state =UP;
                x_length = 0;
                y_length = 0;
            } else {
                state = INITIAL;
                x_length = 0;
                y_length = 0;
            }
            break;
        case DOWN:
            if (event->type == MOUSE_MOV) {
                if (event->delta_x < -tolerance || event->delta_y > tolerance) {
                    state = INITIAL;
                    x_length = 0;
                    y_length = 0;
                    break;
                }

                x_length += event->delta_x;
                y_length += event->delta_y;
            } else if (event->type == RB_RELEASED) {
                if (x_length == 0 || y_length == 0) {
                    state = INITIAL;
                    break;
                }

                if (y_length > -x_length || x_length < x_len) {
                    state = INITIAL;
                    x_length = 0;
                    y_length = 0;
                    break;
                }

                state = FINAL;
                response = 0;
                x_length = 0;
                y_length = 0;
            } else {
                state = INITIAL;
                x_length = 0;
                y_length = 0;
            }
            break;
        case FINAL: // acception state
            response = 0;
        default: // invalid state / dead state
            response = 1;
    }
    return response;
}
