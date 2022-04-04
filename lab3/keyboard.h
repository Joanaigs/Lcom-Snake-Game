#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdbool.h>
#include <stdint.h>

int (keyboard_subscribe)(uint8_t *bit_no);

int (keyboard_unsubscribe)();

void (kbc_ih)();

#endif /* _KEYBOARD_H_ */
