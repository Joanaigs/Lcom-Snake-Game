#include <lcom/lcf.h>
#include <lcom/proj.h>
#include <lcom/liblm.h>
#include "proj.h"
#include "objects.h"
#include "macros.h"
#include "graphics.h"
#include "mouse.h"
#include "cursor.h"
#include "images/mouse_cursor.xpm"
enum BaseState baseState;
int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/src/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/src/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


bool single_player(){
  drawBackground();
  init_objects();

  // rato para depois                  MARIANA E INESI
  //colocar maças pretas
   if(mouse_enable_data_reporting()) return 1;
    int ipc_status, r;
    message msg;
    uint8_t mouse_set = 0;
    if (mouse_subscribe(&mouse_set)) return 1;
    cursor c;
    c.x = 0;
    c.y = 0;
    xpm_load((xpm_map_t)mouse_cursor, XPM_8_8_8, &(c.img));
    
    int counter = 0;
    while (counter < 1000) {

        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) { 
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: 
                    if (msg.m_notify.interrupts & mouse_set) { 
                        mouse_ih();
                        if(mouse_number_bytes >= 3){
                            counter++;
                            struct packet p = parse_packet();
                            c.x += p.delta_x;
                            c.y -= p.delta_y; 

                            //EVENTO DO CLIQUE
                            struct mouse_ev event = mouse_get_event(&p);
                            if(event.type == LB_RELEASED){
                              addBrownApple(c.x , c.y);
                            }

                            drawBackground();
                            //drawSnake("RIGHT");
                            drawBrownApple();

                            // DRAW RATO (meter dentro do timer para desenhar cada frame)
                            //drawCursor(&c);

                        }
                    }
                    break;
                default:
                    break; 
            }
        } else { 
            
        }
    }
    if (mouse_unsubscribe()) return 1;
    kbc_restore_mouse();
    return 0;

    return false;
}

int(proj_main_loop)(int argc, char *argv[]) {
  bool running = true;
  baseState=singlePlayer;
  while (running) {
        switch (baseState) {
            case mainMenu:
              break;
            case singlePlayer:
              running=single_player();
              break;
            case multiPlayer:
              break; 
            case instructions:
              break; 
            case leaderboard:
              break; 

        }
    }
  vg_exit(); //comentar se quiserem ver a imagem, isto fecha o ecra
  return 0;
}

