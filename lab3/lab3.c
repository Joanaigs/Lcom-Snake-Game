#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "keyboard.h"
#include "i8042.h"
#include "util.h"
#include "kbc.h"

extern uint8_t scanCode;
extern uint8_t statusCode;
extern uint32_t counter;

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
      return 1;
    kbc_ih();
    kbd_print_scancode(!(scanCode & BREAK_CODE_BIT), 1, &scanCode);
    tickdelay(micros_to_ticks(DELAY));
  }
  if(kbc_restore_keyboard()) return 1;
  if(kbd_print_no_sysinb(counter)) return 1;
  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
