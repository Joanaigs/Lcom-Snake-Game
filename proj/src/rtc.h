#include <lcom/lcf.h>

#include "rtc_macros.h"

int(rtc_subscribe_int)(uint8_t *bit_no);
int(rtc_unsubscribe_int)();
int wait_valid_rtc();
int set_periodic();
int set_update_int(bool on);
void(rtc_ih)();
