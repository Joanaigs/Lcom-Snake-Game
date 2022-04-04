#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdbool.h>
#include <stdint.h>

int (keyboard_subscribe)(uint8_t *bit_no);

int (keyboard_unsubscribe)();

void (kbc_ih)();

/**
 * @brief High-level function that restores KBC to normal state
 * High-level function that restores KBC to normal state, because lcf_start
 * changes the command byte of KBC. If this function is not used, there is a
 * chance that the keyboard and keyboard interrupts remain disabled.
 * @return 1 if operation was successful, 1 otherwise
 */
void (kbc_restore_keyboard_1)();

void (kbc_restore_keyboard_2)();

void (kbc_restore_keyboard_3)();

#endif /* _KEYBOARD_H_ */
