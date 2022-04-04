#include <i8042.h>
#include <keyboard.h>
#include <lcom/lcf.h>
#include <minix/sysutil.h>

int hook_id=0;
uint8_t statusCode=0x0;
uint8_t scanCode=0x0;

int (keyboard_subscribe)(uint8_t *bit_no) {
    *bit_no=hook_id;
    return sys_irqsetpolicy(KBC_IRQ,IRQ_REENABLE|IRQ_EXCLUSIVE,&hook_id);
}

int (keyboard_unsubscribe)() {
    return sys_irqrmpolicy(&hook_id);
}

void (kbc_ih)(){
    if((statusCode & PARITY_BIT) || (statusCode & TIME_OUT_BIT)){
        printf("error");
        return;
    }
    if(util_sys_inb(OUTPUT_BUF, &scanCode))
        printf("error");
}

