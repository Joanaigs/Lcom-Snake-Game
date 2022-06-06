#include "cursor.h"
#include "graphics.h"
#include "header.h"
#include "i8042.h"
#include "images/maca_preta.xpm"
#include "keyboard.h"
#include "mouse.h"
#include "objects.h"
#include "rtc.h"
#include "snake.h"
#include "timer.h"
#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
uint8_t fr_rate = 8;
int16_t speed = 40;

int(singlePlayerMode)() {
  drawBackground();
  init_xpms();

  Apple initialApple;
  initApple(&initialApple, 280, 200, red);
  drawApple(initialApple);

  init_snake();
  init_header();
  drawHeader();
  drawSnakeBody();
  gameTime = 0;
  uint16_t frames = sys_hz() / fr_rate;
  int ipc_status, r;
  int n_interrupts = 0;
  message msg;
  start = false;
  uint8_t irq_keyboard = 0, irq_timer = 0, irq_rtc = 0;
  if (timer_subscribe_int(&irq_timer))
    return 1;
  if (keyboard_subscribe(&irq_keyboard, 2))
    return 1;
  if (rtc_subscribe_int(&irq_rtc))
    return 1;
  set_periodic();
  set_update_int(true);
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
            if ((n_interrupts % frames == 0) && start) {
              if (movement(speed)) {
                if (rtc_unsubscribe_int())
                  return 1;
                if (set_update_int(false))
                  return 1;
                if (keyboard_unsubscribe())
                  return 1;
                if (timer_unsubscribe_int())
                  return 1;
                return 0;
              }
            }
            if ((n_interrupts % sys_hz() == 0) && start) {
              eraseTime();
              gameTime++;
              drawHeader();
            }
            copy_buffer_to_mem();
          }

          if (msg.m_notify.interrupts & irq_keyboard) {
            kbc_ih();
            if (strcmp(snakeBody[0].direction, "UP") == 0 || strcmp(snakeBody[0].direction, "DOWN") == 0) {
              start = true;
              if (scanCode[0] == D_MAKE_CODE || scanCode[1] == RIGHT_MAKE_CODE) {
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
              start = true;
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
          if (msg.m_notify.interrupts & irq_rtc) {
            rtc_ih();
          }

          break;
        default:
          break;
      }
    }
    else {
    }
  }
  if (rtc_unsubscribe_int())
    return 1;
  if (set_update_int(false))
    return 1;
  if (keyboard_unsubscribe())
    return 1;
  if (timer_unsubscribe_int())
    return 1;
  return 0;
}

int(multiPlayerMode)() {
  
  drawBackground();
  init_xpms();

  Apple initialApple;
  initApple(&initialApple, 280, 200, red);
  drawApple(initialApple);

  init_snake();
  init_header();
  drawHeader();
  drawSnakeBody();
  gameTime = 0;

  if (mouse_enable_data_reporting())
    return 1;
  uint16_t frames = sys_hz() / fr_rate;
  int ipc_status, r;
  int n_interrupts = 0;
  message msg;
  uint8_t irq_keyboard = 0, irq_timer = 0, irq_rtc = 0, mouse_set = 0;
  cursor c;
  c.x = 200;
  c.y = 200;
  xpm_load((xpm_map_t) maca_preta_xpm, XPM_8_8_8, &(c.img));

  if (timer_subscribe_int(&irq_timer))
    return 1;
  if (keyboard_subscribe(&irq_keyboard, 2))
    return 1;
  if (mouse_subscribe(&mouse_set))
    return 1;
  if (rtc_subscribe_int(&irq_rtc))
    return 1;
  set_periodic();
  set_update_int(true);

  drawBackground();

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

            // movement  desenha a cobra e mexe-a
            if (n_interrupts % frames == 0) {

              if (movement(speed)) {

                if (keyboard_unsubscribe())
                  return 1;
                if (timer_unsubscribe_int())
                  return 1;
                if (rtc_unsubscribe_int())
                  return 1;
                if (set_update_int(false))
                  return 1;
                return 1;
              }
            }

            copy_buffer_to_mem();
            drawCursor(&c);
          }

          if (msg.m_notify.interrupts & irq_keyboard) {
            kbc_ih();
            if (strcmp(snakeBody[0].direction, "UP") == 0 || strcmp(snakeBody[0].direction, "DOWN") == 0) {
              if (scanCode[0] == D_MAKE_CODE || scanCode[1] == RIGHT_MAKE_CODE) {

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
          if (msg.m_notify.interrupts & irq_rtc) {
            rtc_ih();
          }
          if (msg.m_notify.interrupts & mouse_set) {
            mouse_ih();
            if (mouse_number_bytes >= 3) {
              struct packet p = parse_packet();
              c.x += p.delta_x;
              c.y -= p.delta_y;

              // EVENTO DO CLIQUE
              struct mouse_ev event = mouse_get_event(&p);
              if (event.type == LB_RELEASED) {

                Apple apple;
                initApple(&apple, c.x, c.y, brown);
                drawApple(apple);
              }
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

  if (rtc_unsubscribe_int())
    return 1;
  if (set_update_int(false))
    return 1;
  if (keyboard_unsubscribe())
    return 1;
  if (timer_unsubscribe_int())
    return 1;
  if (mouse_unsubscribe())
    return 1;

  return 0;
}
