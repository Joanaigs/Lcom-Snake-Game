#include <i8042.h>
#include <keyboard.h>
#include <lcom/lcf.h>
#include <minix/sysutil.h>

int hook_id=0;
uint8_t statusCode=0x0;
uint8_t scanCode=0x0;
uint8_t oldCommand;
uint8_t newCommand;

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

void (kbc_restore_keyboard_1)() {

  int tries = 5;

  // Issuing a command to get the command byte
  while (tries > 0) {
    util_sys_inb(STATUS_REG, &statusCode); /* assuming it returns OK */
    /* loop while 8042 input buffer is not empty */
    if ((statusCode & IN_BUF_FULL) == 0) {
      sys_outb(KBC_CMD, READ_KBC_CMD); /* no args command */
      break;
    }
    tickdelay(DELAY);
    tries--;
  }
  kbc_restore_keyboard_2();
  kbc_restore_keyboard_3();
}

void (kbc_restore_keyboard_2)() {
  int tries = 5;
  // Reading the data returned
  while (tries > 0) {
    util_sys_inb(STATUS_REG, &statusCode); /* assuming it returns OK */
    /* loop while 8042 output buffer is empty */
    if (statusCode & OUTPUT_BUF) {
      util_sys_inb(OUTPUT_BUF, &oldCommand); /* ass. it returns OK */
      if ((statusCode & (PARITY_BIT | TIME_OUT_BIT)) != 0)
        break;
    }
    tickdelay(DELAY);
    tries--;
  }
}

void (kbc_restore_keyboard_3)() {
  newCommand = oldCommand | INT_KBD;
  int tries = 5;
  //Issue new command
  while (tries > 0) {
    util_sys_inb(STATUS_REG, &statusCode); /* assuming it returns OK */
    /* loop while 8042 input buffer is not empty */
    if ((statusCode & IN_BUF_FULL) == 0) {
      sys_outb(KBC_CMD, WRITE_KBC_CMD); //write commands
      sys_outb(KBC_CMD_ARG, newCommand); //write command argument
      break;
    }
    tickdelay(DELAY);
    tries--;
  }
}
