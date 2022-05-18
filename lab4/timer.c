#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"


int hook_id=1;
int n_interrupts = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  if (freq > TIMER_FREQ) {
        printf("%s: Frequency out of range");
        return 1;
    }

  uint16_t new_freq=TIMER_FREQ/freq;
  uint8_t status = 0;
  uint8_t time = 0;
  if (timer_get_conf(timer, &status)) return 1;

  uint8_t cw = TIMER_LSB_MSB|(status & (BIT(3) | BIT(2) | BIT(1) | BIT(0)));

  switch (timer)
  {
  case 0:
    cw|=TIMER_SEL0;
    time=TIMER_0;
    break;
  case 1:
    cw|=TIMER_SEL1;
    time=TIMER_1;
    break;
  case 2:
    cw|=TIMER_SEL2;
    time=TIMER_2;
    break;
  }

  if (sys_outb(TIMER_CTRL, cw)) return 1;

  uint8_t lsb = 0, msb = 0;
  if(util_get_LSB(new_freq,&lsb)) return 1;
  if(util_get_MSB(new_freq,&msb)) return 1;

  if (sys_outb(time, lsb)) return 1;
  if (sys_outb(time, msb)) return 1;


  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
    *bit_no=BIT(hook_id);
    return sys_irqsetpolicy(TIMER0_IRQ,IRQ_REENABLE,&hook_id);
}

int (timer_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id);
}

void (timer_int_handler)() {
  n_interrupts++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  if(st==NULL) return 1;
  uint8_t cw = TIMER_RB_CMD | TIMER_RB_SEL(timer) | TIMER_RB_COUNT_ | !TIMER_RB_STATUS_;
  if(sys_outb(TIMER_CTRL, cw)) return 1;
  int n; 
  switch (timer){
    case 0:
      n=TIMER_0;
      break;
    case 1:
      n=TIMER_1;
      break;
    case 2:
      n=TIMER_2;
      break;
  }
  if(util_sys_inb(n, st)) return 1;
  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {  
  union timer_status_field_val a;
  switch (field)
  {
  case tsf_all:
    a.byte=st;
    break;
  case tsf_initial:
    a.in_mode=(st&TIMER_IN_MASK)>>4;
    break;
  case tsf_mode:
    a.count_mode = (st & TIMER_MODE_MASK)>>1;
    break;
  case tsf_base:
    a.bcd=st & TIMER_BCD;
    break;
  }
  timer_print_config(timer, field,a);
  return 0;
}
