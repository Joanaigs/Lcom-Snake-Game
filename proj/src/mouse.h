#ifndef __MOUSE_H
#define __MOUSE_H
#include <minix/sysutil.h>
#include "utils.h"
int hook_idR;
int mouse_number_bytes;
uint8_t mouse[3];
uint8_t statusCode;
uint8_t scanC;

int (mouse_subscribe)(uint8_t *bit_no, int hook);
struct packet (parse_packet)();
void (mouse_ih)();
int (mouse_unsubscribe)();
void (kbc_restore_mouse)() ;
struct mouse_ev (mouse_get_event)(struct packet *pp) ;

#endif /* __MOUSE_H */
