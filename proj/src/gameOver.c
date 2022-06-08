#include "gameOver.h"
#include "graphics.h"
#include "header.h"
#include "i8042.h"
#include "images/gameOver.xpm"
#include "keyboard.h"
#include "objects.h"
#include "snake.h"
#include "timer.h"
#include "mouse.h"
#include "menu.h"
#include "cursor.h"

int(gameOverPage)() {
    xpm_image_t img;
    uint8_t *map = xpm_load((xpm_map_t) game_over_xpm, XPM_8_8_8, &img);
    int x = (h_res - img.width) / 2;
    int y = (v_res + 120 - img.height) / 2;
    draw_xpm(img, map, x, y);
    draw_xpm(timeClock.img, timeClock.map, x + 91 + 20, y + 90);
    draw_number(gameTime, x + 91 + 20 + 45, y + 90 + 10);

    /* INICIALIZAR CURSOR
    cursor c;
    c.x = 200;
    c.y = 200;
    xpm_load((xpm_map_t) maca_preta_xpm, XPM_8_8_8, &(c.img));
    */

    cursor c;
    c.x = 200;
    c.y = 200;
    Apple apple;
    initApple(&apple, x + 91 + 20, y + 140, red);
    drawApple(apple);
    draw_number(numOfApplesEaten, x + 91 + 20 + 45, y + 140 + 10);
    copy_buffer_to_mem();
    message msg;
    int ipc_status, r;
    uint8_t irq_keyboard = 1, irq_timer = 0, irq_mouse = 0;

    if (keyboard_subscribe(&irq_keyboard, 5))
        return 1;
    if (timer_subscribe_int(&irq_timer)) return 1;

    if (mouse_subscribe(&irq_mouse)) return 1;

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
                    if (msg.m_notify.interrupts & irq_timer) {
                        copy_buffer_to_mem();
                    }

                    if (msg.m_notify.interrupts & irq_mouse) {
                        mouse_ih();
                        if (mouse_number_bytes >= 3) {
                            struct packet p = parse_packet();
                            c.x += p.delta_x;
                            c.y -= p.delta_y;
                            continueMenu(&c, &p);
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
    if (mouse_unsubscribe())
        return 1;
    return 0;
}
