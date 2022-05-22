#ifndef __MOUSE_H
#define __MOUSE_H
#include <minix/sysutil.h>
#include "../../lab4/utils.h"
int hook_idR;
int mouse_number_bytes;
uint8_t mouse[3];
uint8_t statusCode;
uint8_t scanCode;

int (mouse_subscrive)(uint8_t *bit_no);
struct packet (parse_packet)();
void (mouse_ih)();
int (mouse_unsubscrive)();
void (kbc_restore_mouse)() ;
struct mouse_ev* (mouse_get_event)(struct packet *pp) ;

#endif /* __MOUSE_H */
