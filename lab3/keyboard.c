#include <kbc.h>
#include <i8042.h>
#include <keyboard.h>
#include <lcom/lcf.h>
#include <minix/sysutil.h>

int hook_id=0;

int (timer_subscribe_int)(uint8_t *bit_no) {
    *bit_no=hook_id;
    return sys_irqsetpolicy(KBC_IRQ,IRQ_REENABLE|IRQ_EXCLUSIVE,&hook_id);
}
