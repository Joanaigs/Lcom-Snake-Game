#include "gameOver.h"
#include "graphics.h"
#include "header.h"
#include "objects.h"
#include "snake.h"
#include "i8042.h"
#include "images/gameOver.xpm"
#include "keyboard.h"
int(gameOverPage)() {
  xpm_image_t img;
  uint8_t *map = xpm_load((xpm_map_t) game_over_xpm, XPM_8_8_8, &img);
  int x=(h_res- img.width) / 2;
  int y=(v_res +120 - img.height) / 2;
  draw_xpm(img, map, x, y);
  draw_xpm(timeClock.img, timeClock.map, x+91+20, y+90);
  draw_number(gameTime, x+91+20+45, y+90+10);
  //draw_xpm(goodApple.img, goodApple.map, x+91+20, y+140); -adiconar quando a matilde der merge
  draw_number(numOfApplesEaten, x+91+20+45, y+140+10);
  message msg;
  int ipc_status, r;
  uint8_t irq_keyboard = 1;
  if (keyboard_subscribe(&irq_keyboard, 4))
    return 1;
  int good = 1;
  while (good) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_keyboard) {
            kbc_ih();
            if (done) {
              if (scanCode[0] == ENTER_BREAK_CODE)
                good = 0;
              size = 0;
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
  return 0;
}
