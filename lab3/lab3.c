#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "keyboard.h"
#include "i8042.h"
#include "util.h"
#include "timer.h"

extern uint8_t scanCode;
extern uint8_t statusCode;
extern uint32_t counter;
extern int n_interrupts;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  int ipc_status, r;
  message msg;
  uint8_t keyboard_id = 0;
  if (keyboard_subscribe(&keyboard_id)) return 1;
  int irq_set = BIT(keyboard_id);
  while( scanCode!=ESC_BREAK_CODE ) {
     if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                   if(util_sys_inb(STATUS_REG, &statusCode))
                      return 1;
                   kbc_ih();
                   kbd_print_scancode(!(scanCode & BREAK_CODE_BIT), 1, &scanCode);
                }
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
 }
  if(sys_outb(OUTPUT_BUF, 0X01))
    return 1;
  if (keyboard_unsubscribe()) return 1;  
  kbd_print_no_sysinb(counter);
  return 0;

}

int(kbd_test_poll)() {
  while(scanCode != ESC_BREAK_CODE){
    if(util_sys_inb(STATUS_REG, &statusCode))
      continue;
    if(!(statusCode & OBF) || (statusCode & AUX_MOUSE))
      continue;

    kbc_ih();
    kbd_print_scancode(!(scanCode & BREAK_CODE_BIT), 1, &scanCode);
    tickdelay(micros_to_ticks(DELAY));
  }
  if(kbd_print_no_sysinb(counter)) return 1;
  kbc_restore_keyboard();
  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  int ipc_status, r;
  const int frequency = 60; 
  message msg;
  uint8_t kbd_int_bit = 0;
  uint8_t timer0_int_bit = 0;
  uint8_t time = 0;

   if (timer_subscribe_int(&timer0_int_bit)) return 1;

  if (keyboard_subscribe(&kbd_int_bit)) return 1;

  while( scanCode!=ESC_BREAK_CODE && time<=n) {
     if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & kbd_int_bit) { /* subscribed interrupt */
                   if(util_sys_inb(STATUS_REG, &statusCode))
                      return 1;
                   time = 0;
                   n_interrupts = 0;
                   kbc_ih();
                   kbd_print_scancode(!(scanCode & BREAK_CODE_BIT), 1, &scanCode);
                }
                else if (msg.m_notify.interrupts &  timer0_int_bit) { /* subscribed interrupt */
                   timer_int_handler();
                   if (n_interrupts % frequency==0) { /* second elapsed */
                            time ++;
                        }
                }
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
 }
  if (keyboard_unsubscribe()) return 1;  
  if (timer_unsubscribe_int()) return 1;
  return 0;
}
