#include <lcom/lcf.h>
#include <lcom/proj.h>
#include <lcom/liblm.h>
#include "proj.h"
#include "objects.h"
#include "macros.h"
#include "graphics.h"
#include "menu.h"
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

bool menu(){
  drawMenu();
  return false;
}

bool single_player(){
  drawBackground();
  init_objects();
  addBodyPart();
  printf("%d", numOfBodyParts);
  drawApple();
  drawSnake("UP");
  return false;
}

int(proj_main_loop)(int argc, char *argv[]) {
  bool running = true;
  baseState=mainMenu;
  if(vbe_get_mode_info(0x115, &vmi_p)) return 1;
  vramMap();
  if(setMode(0x115)) return 1;
  while (running) {
        switch (baseState) {
            case mainMenu:
              running= menu();
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

  sleep(5);
  vg_exit(); //comentar se quiserem ver a imagem, isto fecha o ecra
  return 0;
}

