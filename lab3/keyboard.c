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

void (kbc_restore_keyboard)(){
    void reenable_kbd_int(){
  uint8_t oldCommand;
  uint8_t newCommand;

  int tries = 5;

  //Issuing a command to get the command byte
  while (tries > 0) {
    util_sys_inb(KBC_ST_REG, &statusCode); /* assuming it returns OK */
    /* loop while 8042 input buffer is not empty */
    if ((statusCode & KBC_ST_IBF) == 0) {
      sys_outb(KBC_CMD_REG, READ_CMD_BYTE); /* no args command */
      break;
    }
    tickdelay(WAIT_KBC);
    tries--;
  }

  tries = 5;
  //Reading the data returned
  while (tries > 0) {
    util_sys_inb(KBC_ST_REG, &statusCode); /* assuming it returns OK */
    /* loop while 8042 output buffer is empty */
    if (statusCode & KBC_ST_OBF) {
      util_sys_inb(KBC_OUT_BUF, &oldCommand); /* ass. it returns OK */
      if ((statusCode & (KB_ST_PARITY_BIT  | KB_ST_TIME_OUT_BIT)) != 0)
        break;
    }
    tickdelay(WAIT_KBC); 
    tries--;
  }

  newCommand = oldCommand | KBD_INT;
  tries = 5;
  //Issue new command
  while (tries > 0) {
    util_sys_inb(KBC_ST_REG, &statusCode); /* assuming it returns OK */
    /* loop while 8042 input buffer is not empty */
    if ((statusCode & KBC_ST_IBF) == 0) {
      sys_outb(KBC_CMD_REG, WRITE_CMD_BYTE); //write commands
      sys_outb(KBC_CMD_ARGS, newCommand); //write command argument
      break;
    }
    tickdelay(WAIT_KBC);
    tries--;
  }
}
}