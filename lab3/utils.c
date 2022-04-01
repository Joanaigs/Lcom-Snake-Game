#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  *lsb=val;
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  *msb=val>>8;
  return 0;
}

#ifdef LAB3
    uint32_t sys_inb_counter = 0;
#endif

int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t result;
  if(sys_inb(port, &result))
    return 1;
  *value=(uint8_t) result;
  #ifdef LAB3
        ++sys_inb_counter;
  #endif
  return 0;
}
