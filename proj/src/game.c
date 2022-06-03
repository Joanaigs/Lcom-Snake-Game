#include "graphics.h"
#include "i8042.h"
#include "keyboard.h"
#include "objects.h"
#include "snake.h"
#include "timer.h"
#include "mouse.h"
#include "cursor.h"
#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
uint8_t fr_rate = 5;
int16_t speed = 50;

int(singlePlayerMode)() {

  if (vbe_get_mode_info(0x115, &vmi_p))
    return 1;
  vramMap();
  if (setMode(0x115))
    return 1;
  drawBackground();

  init_snake();
  drawSnakeBody();
  if(mouse_enable_data_reporting()) return 1;
  uint16_t frames = sys_hz() / fr_rate;
  int ipc_status, r;
  int n_interrupts = 0;
  message msg;
  uint8_t irq_keyboard = 0, irq_timer = 0, mouse_set=0;
  cursor c;
    c.x = 0;
    c.y = 0;
  if (timer_subscribe_int(&irq_timer))
    return 1;
  if (keyboard_subscribe(&irq_keyboard))
    return 1;
  if (mouse_subscribe(&mouse_set)) return 1;
  while (scanCode[0] != ESC_BREAK_CODE) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_timer) {
            n_interrupts++;
            if (n_interrupts % frames == 0) {
              if (movement(speed)) {
                sleep(1);
                if (keyboard_unsubscribe())
                  return 1;
                if (timer_unsubscribe_int())
                  return 1;
                vg_exit();
                return 1;
              }
            }
          }
          if (msg.m_notify.interrupts & irq_keyboard) {
            kbc_ih();
            if (strcmp(snakeBody[0].direction, "UP") == 0 || strcmp(snakeBody[0].direction, "DOWN") == 0) {
              if (scanCode[0] == D_MAKE_CODE || scanCode[1] == RIGHT_MAKE_CODE) {
                addBodyPart();
                snakeBody[0].direction = "RIGHT";
                snakeBody[0].img = snakeBody[0].imgRight;
                snakeBody[0].map = snakeBody[0].mapRight;
              }
              if (scanCode[0] == A_MAKE_CODE || scanCode[1] == LEFT_MAKE_CODE) {
                snakeBody[0].direction = "LEFT";
                snakeBody[0].img = snakeBody[0].imgLeft;
                snakeBody[0].map = snakeBody[0].mapLeft;
              }
            }
            else if (strcmp(snakeBody[0].direction, "LEFT") == 0 || strcmp(snakeBody[0].direction, "RIGHT") == 0) {
              if (scanCode[0] == W_MAKE_CODE || scanCode[1] == UP_MAKE_CODE) {
                snakeBody[0].direction = "UP";
                snakeBody[0].img = snakeBody[0].imgUp;
                snakeBody[0].map = snakeBody[0].mapUp;
              }
              if (scanCode[0] == S_MAKE_CODE || scanCode[1] == DOWN_MAKE_CODE) {
                snakeBody[0].direction = "DOWN";
                snakeBody[0].img = snakeBody[0].imgDown;
                snakeBody[0].map = snakeBody[0].mapDown;
              }
            }
          }
          if (msg.m_notify.interrupts & mouse_set) { 
                        mouse_ih();
                        if(mouse_number_bytes >= 3){
                            struct packet p = parse_packet();
                            c.x += p.delta_x;
                            c.y -= p.delta_y; 

                            //EVENTO DO CLIQUE
                            struct mouse_ev event = mouse_get_event(&p);
                            if(event.type == LB_RELEASED){
                              addBrownApple(c.x , c.y);
                            }

                            drawBackground();
                            //drawSnake("RIGHT");
                            drawBrownApple();

                            // DRAW RATO (meter dentro do timer para desenhar cada frame)
                            //drawCursor(&c);

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
  if (keyboard_unsubscribe())
    return 1;
  if (timer_unsubscribe_int())
    return 1;
  if (mouse_unsubscribe()) return 1;
    kbc_restore_mouse();
  if (vg_exit())
    return 1;
  return 0;
}
