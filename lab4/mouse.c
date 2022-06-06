#include "mouse.h"
#include "i8042.h"
#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
#include <lcom/lcf.h>
#include "../../lab4/i8042.h"

int hook_idR = 0;
int mouse_number_bytes = 0;
uint8_t command;
int(mouse_subscrive)(uint8_t *bit_no) {
  *bit_no = BIT(hook_idR);
  return sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_idR);
}

struct packet(parse_packet)() {
  struct packet pp;
  pp.bytes[0] = mouse[0];
  pp.bytes[1] = mouse[1];
  pp.bytes[2] = mouse[2];
  pp.rb = pp.bytes[0] & BIT(1);
  pp.lb = pp.bytes[0] & BIT(0);
  pp.mb = pp.bytes[0] & BIT(2);
  pp.delta_x = (pp.bytes[0] & BIT(4)) ? (pp.bytes[1] - 256) : (pp.bytes[1]);
  pp.delta_y = (pp.bytes[0] & BIT(5)) ? (pp.bytes[2] - 256) : (pp.bytes[2]);
  pp.x_ov= pp.bytes[0] & BIT(6);
  pp.y_ov= pp.bytes[0] & BIT(7);
  return pp;
}

void(mouse_ih)() {
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

int(mouse_unsubscrive)() {
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
enum states {
  INITIAL,
  UP,
  VERTEX,
  DOWN,
  FINAL
};
struct mouse_ev *(mouse_get_event) (struct packet *pp) {
  static struct mouse_ev event;
  static uint8_t last = 0;

  if (pp == NULL)
    return &event;

  // current button presses
  uint8_t button_presses = pp->bytes[0] & (LEFT_BUTTON | RIGHT_BUTTON | MIDDLE_BUTTON);
  int16_t delta_x = pp->delta_x;
  int16_t delta_y = pp->delta_y;

  if ((button_presses ^ last) == LEFT_BUTTON && !(last & LEFT_BUTTON)) {
    event.type = LB_PRESSED;
    last |= LEFT_BUTTON;
  }
  else if ((button_presses ^ last) == RIGHT_BUTTON && !(last & RIGHT_BUTTON)) {
    event.type = RB_PRESSED;
    last |= RIGHT_BUTTON;
  }
  else if ((button_presses ^ last) == LEFT_BUTTON && (last & LEFT_BUTTON)) {
    event.type = LB_RELEASED;
    last &= ~LEFT_BUTTON;
  }
  else if ((button_presses ^ last) == RIGHT_BUTTON && (last & RIGHT_BUTTON)) {
    event.type = RB_RELEASED;
    last &= ~RIGHT_BUTTON;
  }
  else if ((delta_x || delta_y) && (button_presses == last)) {
    event.type = MOUSE_MOV;
  }
  else
    event.type = BUTTON_EV;

  event.delta_x = delta_x;
  event.delta_y = delta_y;
  return &event;
}

int(state_machine)(struct mouse_ev *event, uint8_t x_len, uint8_t tolerance) {

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
      }
      else if (event->type == LB_RELEASED) {
        if (y_length < x_length || x_length < x_len) {
          state = INITIAL;
          x_length = 0;
          y_length = 0;
          break;
        }

        state = VERTEX;
        x_length = 0;
        y_length = 0;
      }
      else {
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
      }
      else if (event->type == RB_PRESSED) {
        state = DOWN;
        x_length = 0;
        y_length = 0;
      }
      else if (event->type == LB_PRESSED) {
        state = UP;
        x_length = 0;
        y_length = 0;
      }
      else {
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
      }
      else if (event->type == RB_RELEASED) {
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
      }
      else {
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
