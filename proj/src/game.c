#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include "graphics.h"
#include "keyboard.h"
#include "i8042.h"
#include "timer.h"
#include "snake.h"
#include "objects.h"
uint8_t fr_rate=60;
int16_t speed=2;

int (singlePlayerMode)(){

    if(vbe_get_mode_info(0x115, &vmi_p)) return 1;
    vramMap();
    if(setMode(0x115)) return 1;
    drawBackground();
    
    init_snake();
    drawSnake("UP", 200, 300);
    drawSnakeBody();
    uint16_t frames = sys_hz()/fr_rate;
    int ipc_status, r;
    int n_interrupts = 0;
    message msg;
    uint8_t irq_keyboard = 0, irq_timer=0;
    if(timer_subscribe_int(&irq_timer)) return 1;
  if (keyboard_subscribe(&irq_keyboard)) return 1;
   while( scanCode[0]!=ESC_BREAK_CODE ) {
     if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) {
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: 
                if (msg.m_notify.interrupts & irq_timer) {
                  n_interrupts++;
                  if(n_interrupts%frames==0){
                    if(movement(speed)){
                        vg_exit();
                        return 1;
                    }

                  }
                }
                if (msg.m_notify.interrupts & irq_keyboard) { 
                  kbc_ih();
                  if(strcmp(snakeBody[0].direction, "UP")==0 ||strcmp(snakeBody[0].direction, "DOWN")==0){
                    if(scanCode[0]==D_MAKE_CODE || scanCode[1]==RIGHT_MAKE_CODE){
                      addBodyPart();
                      snakeBody[0].prevDirection=snakeBody[0].direction;
                      snakeBody[0].direction="RIGHT";
                      snakeBody[0].changex=snakeBody[0].x;snakeBody[0].changey=snakeBody[0].y;
                    }
                    if(scanCode[0]==A_MAKE_CODE || scanCode[1]==LEFT_MAKE_CODE){
                      snakeBody[0].prevDirection=snakeBody[0].direction;
                      snakeBody[0].direction="LEFT";
                      snakeBody[0].changex=snakeBody[0].x;snakeBody[0].changey=snakeBody[0].y;
                    }
                  }
                  else if(strcmp(snakeBody[0].direction, "LEFT")==0 ||strcmp(snakeBody[0].direction, "RIGHT")==0){
                    if(scanCode[0]==W_MAKE_CODE || scanCode[1]==UP_MAKE_CODE){
                    snakeBody[0].prevDirection=snakeBody[0].direction;
                    snakeBody[0].direction="UP";
                    snakeBody[0].changex=snakeBody[0].x;snakeBody[0].changey=snakeBody[0].y;
                    }
                    if(scanCode[0]==S_MAKE_CODE || scanCode[1]==DOWN_MAKE_CODE){
                      snakeBody[0].prevDirection=snakeBody[0].direction;
                      snakeBody[0].direction="DOWN";
                      snakeBody[0].changex=snakeBody[0].x;snakeBody[0].changey=snakeBody[0].y;
                    }
                  }
                }
                
                break;
            default:
                break; 
        }
    } else { 
        
    }
 }
    if (keyboard_unsubscribe()) return 1;  
    if(timer_unsubscribe_int()) return 1;
    
    if(vg_exit()) return 1;
    return 0;
}

