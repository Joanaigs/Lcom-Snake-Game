#ifndef _KBC_H_
#define _KBC_H_

#include <stdbool.h>
#include <stdint.h>

#define DELAY_US    20000

tickdelay(micros_to_ticks(DELAY_US));

void (kbc_ih)();

#endif /* _KBC_H_ */