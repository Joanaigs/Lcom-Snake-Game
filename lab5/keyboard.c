#include <i8042.h>
#include <keyboard.h>
#include <lcom/lcf.h>
#include <minix/sysutil.h>

int hook_idK=2;
uint8_t statusCode=0x0;
uint8_t command;

int (keyboard_subscribe)(uint8_t *bit_no) {
    *bit_no=BIT(hook_idK);
    return sys_irqsetpolicy(KBC_IRQ,IRQ_REENABLE|IRQ_EXCLUSIVE,&hook_idK);
}

int (keyboard_unsubscribe)() {
    return sys_irqrmpolicy(&hook_idK);
}
int size=0;
void (kbc_ih)(){
    if(done) size = 0;
    uint8_t byte;
    if (util_sys_inb(STATUS_REG, &statusCode)) return;
    if((statusCode & PARITY_BIT) || (statusCode & TIME_OUT_BIT)){
        printf("error");
        return;
    }
        if ((statusCode & OBF) == 0 || (statusCode & AUX_MOUSE) != 0) {
        return;
    }
    if (util_sys_inb(OUTPUT_BUF, &byte)) return;
    scanCode[size]=byte;
    if(TWO_BYTE_CODE == byte){
      done=0;
      size++;
    }
    else{
      done=1;
      size++;
    }
}
void (kbc_restore_keyboard)() {
  // Issuing a command to get the command byte
  for(int i=0; i<5; i++) {
    util_sys_inb(STATUS_REG, &statusCode); /* assuming it returns OK */
    /* loop while 8042 input buffer is not empty */
    if ((statusCode & IN_BUF_FULL) == 0) {
      sys_outb(KBC_CMD, READ_KBC_CMD); /* no args command */
      break;
    }
    tickdelay(micros_to_ticks(DELAY));
  }
  for(int i=0; i<5; i++) {
    util_sys_inb(STATUS_REG, &statusCode); /* assuming it returns OK */
    /* loop while 8042 output buffer is empty */
    if (statusCode & OBF) {
      util_sys_inb(OUTPUT_BUF, &command); /* ass. it returns OK */
      if ((statusCode & (PARITY_BIT | TIME_OUT_BIT)) != 0)
        continue;
    }
    tickdelay(micros_to_ticks(DELAY));
  }
  command = command | INT_KBD;
  //Issue new command
  for(int i=0; i<5; i++) {
    util_sys_inb(STATUS_REG, &statusCode); /* assuming it returns OK */
    /* loop while 8042 input buffer is not empty */
    if ((statusCode & IN_BUF_FULL) == 0) {
      sys_outb(KBC_CMD, WRITE_KBC_CMD); //write commands
      sys_outb(KBC_CMD_ARG, command); //write command argument
      break;
    }
    tickdelay(micros_to_ticks(DELAY));
  }

}

void (kbc_restore_keyboard_2)() {
  // Reading the data returned
  for(int i=0; i<5; i++) {
    util_sys_inb(STATUS_REG, &statusCode); /* assuming it returns OK */
    /* loop while 8042 output buffer is empty */
    if (statusCode & OBF) {
      util_sys_inb(OUTPUT_BUF, &command); /* ass. it returns OK */
      if ((statusCode & (PARITY_BIT | TIME_OUT_BIT)) != 0)
        break;
    }
    tickdelay(DELAY);
  }
}

void (kbc_restore_keyboard_3)() {
  command = command | INT_KBD;
  //Issue new command
  for(int i=0; i<5; i++) {
    util_sys_inb(STATUS_REG, &statusCode); /* assuming it returns OK */
    /* loop while 8042 input buffer is not empty */
    if ((statusCode & IN_BUF_FULL) == 0) {
      sys_outb(KBC_CMD, WRITE_KBC_CMD); //write commands
      sys_outb(KBC_CMD_ARG, command); //write command argument
      break;
    }
    tickdelay(DELAY);
  }
}

