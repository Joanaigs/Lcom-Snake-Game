int(kbd_test_scan)() {
    int ipc_status, r;
  message msg;
  uint8_t irq_set = 0;
  if (subscrive_keyboard(&irq_set)) return 1;
  while(1 ) {
     if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                   if(util_sys_inb(STATUS_REG, &status))
                      return 1;
                   kbc_ih();
                   kbd_print_scancode(!(scanCode[0] & BREAK_CODE_BIT), 1, scanCode);
                }
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
 }
  if (unsubscrive_keyboard()) return 1;  
  kbd_print_no_sysinb(cnt);
  return 0;

}