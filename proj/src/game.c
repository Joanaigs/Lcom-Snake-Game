#include <lcom/lcf.h>


#include <stdint.h>
#include <stdio.h>
#include "graphics.h"
#include "keyboard.h"
#include "i8042.h"
#include "macros.h"
#include "objects.h"
#include "graphics.h"


void multiPlayer(){
    if(mouse_enable_data_reporting()) return 1;
    int ipc_status, r;
    message message;
    uint8_t irq_mouse_set = 0;
    if (mouse_subscribe(&irq_mouse_set)) return 1;

    int good = (cnt != 0);
    uint32_t count = 0;
    while (good) {
        if ((r = driver_receive(ANY, &message, &ipc_status)) != 0) {
            printf("driver_receive failed with %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) {
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    if (msg.m_notify.interrupts & irq_mouse_set) {
                        mouse_ih();
                        if(mouse_number_bytes >= 3){
                            struct packet p = parse_packet();
                            count++;
                            if(cnt == count) good = 0;

                        }
                    }
                    break;
                default:
                    break; /* no other notifications expected: do nothing */
            }
        } else { /* received standart message, not a notification */
            /* no standart message expected: do nothing */
        }
    }
    if (mouse_unsubscribe()) return 1; // unsubscribes interrupts
    kbc_restore_mouse();

    if(vg_exit()) return 1;

    return 0;
}
