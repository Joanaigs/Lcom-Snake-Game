// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>
#include "mouse.h"
#include "timer.h"
extern int n_interrupts;

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
    if(mouse_enable_data_reporting()) return 1;
    int ipc_status, r;
    message msg;
    uint8_t mouse_set = 0;
    if (mouse_subscrive(&mouse_set)) return 1;

    int good = (cnt != 0);
    uint32_t count = 0;
    while (good) {
        /* Get a request message. */
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */
                    if (msg.m_notify.interrupts & mouse_set) { /* subscribed interrupt */
                        mouse_ih();
                        if(mouse_number_bytes >= 3){
                            struct packet p = parse_packet();
                            mouse_print_packet(&p);
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
    if (mouse_unsubscrive()) return 1; // unsubscribes interrupts
    kbc_restore_mouse();
    return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
    int ipc_status, r;
    message msg;
    int frequency=sys_hz();
    uint8_t mouse_set = 0, timer_set=0;
    if (timer_subscribe_int(&timer_set)) return 1;
    if(mouse_enable_data_reporting()) return 1;
    if (mouse_subscrive(&mouse_set)) return 1;
    int count = 0;
    int good=1;
    while (good) {
        /* Get a request message. */
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */
                    if (msg.m_notify.interrupts & timer_set) { /* subscribed interrupt */
                        timer_int_handler();
                        if ( n_interrupts % frequency==0) { /* second elapsed */
                                    count++;
                                }
                        if(count >= idle_time) good = 0;
                    }
                     if (msg.m_notify.interrupts & mouse_set) { /* subscribed interrupt */
                        mouse_ih();
                        if(mouse_number_bytes >= 3){
                            struct packet p = parse_packet();
                            mouse_print_packet(&p);
                            count=0;
                             n_interrupts=0;
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
    if (mouse_unsubscrive()) return 1; // unsubscribes interrupts
    if(timer_unsubscribe_int())return 1;
    kbc_restore_mouse();
    return 0;
}

int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
    if(mouse_enable_data_reporting()) return 1;
    int ipc_status, r;
    message msg;
    uint8_t mouse_set = 0;
    if (mouse_subscrive(&mouse_set)) return 1;
    struct mouse_ev *event;
    int good = 1;
    while (good) {
        /* Get a request message. */
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */
                    if (msg.m_notify.interrupts & mouse_set) { /* subscribed interrupt */
                        mouse_ih();
                        if(mouse_number_bytes >= 3){
                            struct packet p = parse_packet();
                            mouse_print_packet(&p);
                            event = mouse_get_event(&p);

                            if(!state_machine(event, x_len, tolerance))
                                good=0;
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
    if (mouse_unsubscrive()) return 1; // unsubscribes interrupts
    kbc_restore_mouse();
    return 0;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* This year you need not implement this. */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}
