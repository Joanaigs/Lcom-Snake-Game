// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>
#include "graphics.h"
#include "keyboard.h"
#include "i8042.h"
#include "macros.h"

extern int n_interrupts;
// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
  if(vbe_get_mode_info(mode, &vmi_p)) return 1;
  vramMap();
  if(setMode(mode)) return 1;
  tickdelay(micros_to_ticks(delay*1e6));
  if(vg_exit()) return 1;
  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
  if(vbe_get_mode_info(mode, &vmi_p)) {
       return 1; 
  } 
  vramMap();
  if(setMode(mode)) {
       vg_exit();
       return 1; 
  } 
  uint16_t w = (x + width > h_res) ? (h_res- x) : (width);
  uint16_t h = (y + height > v_res) ? (v_res - y) : (height);

  if (vg_draw_rectangle(x,y,w,h, color)) {
       return 1; 
  }
  int ipc_status, r;
  message msg;
  uint8_t irq_set = 0;
    if (keyboard_subscribe(&irq_set)) return 1;

   while( scanCode[0]!=ESC_BREAK_CODE ) {
     if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                   kbc_ih();
                }
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
 }
  if (keyboard_unsubscribe()) return 1;
  if(vg_exit()) return 1;

  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  if(vbe_get_mode_info(mode, &vmi_p)) return 1;
  vramMap();
  if(setMode(mode)) return 1;
  uint16_t width = h_res/no_rectangles;
  uint16_t height = v_res/no_rectangles;
  uint32_t color, red, green, blue;
  for(uint8_t row = 0; row < no_rectangles; ++row){
        for(uint8_t col = 0; col < no_rectangles; ++col){
            if(bytes_per_pixel == 1){
                color = (first + (row * no_rectangles + col) * step) % (1 << bits_per_pixel);
            }else{
                red = ((0xFF&(first>>vmi_p.RedFieldPosition)) + x * step) % (1 << vmi_p.RedMaskSize);
                green = ((0xFF&(first>>vmi_p.GreenFieldPosition)) + y * step) % (1 << vmi_p.GreenMaskSize);
                blue = ((0xFF&(first>>vmi_p.BlueFieldPosition)) + (x+y) * step) % (1 << vmi_p.BlueMaskSize);
                color=((red&0xFF)<<vmi_p.RedFieldPosition) | ((green&0xFF)<<vmi_p.GreenFieldPosition) | ((blue&0xFF)<<vmi_p.BlueFieldPosition);
            }
            uint16_t x = col * width;
            uint16_t y = row * height;
            uint16_t w = (x + width >h_res) ? (h_res - x) : (width);
            uint16_t h = (y + height > v_res) ? (v_res - y) : (height);
            if (vg_draw_rectangle(x,y,w,h,color)) 
                return 1;
        }
    }

  int ipc_status, r;
  message msg;
  uint8_t irq_set = 0;
  if (keyboard_subscribe(&irq_set)) return 1;
   while( scanCode[0]!=ESC_BREAK_CODE ) {
     if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                   kbc_ih();
                }
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
 }
  if (keyboard_unsubscribe()) return 1;  
  if(vg_exit()) return 1;

  return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  if(vbe_get_mode_info(0x105, &vmi_p)) return 1;
  vramMap();
  if(setMode(0x105)) return 1;
  xpm_image_t img;
  uint8_t *map; 
  
  map = xpm_load(xpm, XPM_INDEXED, &img);
  for(uint8_t col = 0; col < img.width; col++){
      for(uint8_t row = 0; row < img.height; row++){
          if ((x + col) < h_res && (y + row) <v_res) {
            drawPixel(x+col, y+row, map[col+row*img.width]);
          }
      }
  }
  int ipc_status, r;
  message msg;
  uint8_t irq_set = 0;
  if (keyboard_subscribe(&irq_set)) return 1;
   while( scanCode[0]!=ESC_BREAK_CODE ) {
     if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                   kbc_ih();
                }
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
 }
  if (keyboard_unsubscribe()) return 1;  
  if(vg_exit()) return 1;
  return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  if(vbe_get_mode_info(0x105, &vmi_p)) return 1;
  vramMap();
  if(setMode(0x105)) return 1;
  xpm_image_t img;
  uint8_t *map; 
  
  map = xpm_load(xpm, XPM_INDEXED, &img);
  for(uint8_t col = 0; col < img.width; col++){
      for(uint8_t row = 0; row < img.height; row++){
          if ((xi + col) < vmi_p.XResolution && (yi + row) < vmi_p.YResolution) {
            drawPixel(xi+col, yi+row, map[col+row*img.width]);
          }
      }
  }  
  uint16_t frames = sys_hz()/fr_rate;
  int frameCounter=0;
  int ipc_status, r;
  int x=xi, y=yi;
  message msg;
  uint8_t irq_keyboard = 0, irq_timer=0;
  if(timer_subscribe_int(&irq_timer)) return 1;
  if (keyboard_subscribe(&irq_keyboard)) return 1;
   while( scanCode[0]!=ESC_BREAK_CODE ) {
     if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & irq_timer) { /* subscribed interrupt */
                  timer_int_handler();
                  if(n_interrupts%frames==0){
                    for(uint8_t col = 0; col < img.width; col++){
                          for(uint8_t row = 0; row < img.height; row++){
                              drawPixel(x+col, y+row, xpm_transparency_color(img.type));
                          }
                        }
                    frameCounter++;
                    if(speed>0){
                      if(x==xf){
                        y = (y+speed>yf) ? (y=yf) : (y+=speed);
                      }
                      else if(y==yf){
                        x = (x+speed>xf) ? (x=xf) : (x+=speed);
                      }
                      for(uint8_t col = 0; col < img.width; col++){
                        for(uint8_t row = 0; row < img.height; row++){
                            drawPixel(x+col, y+row, map[col+row*img.width]);
                        }
                      }
                    }
                    else{
                      if(frameCounter==abs(speed)){
                        if(x==xf){
                          y = (y+speed>yf) ? (y=yf) : (y+=speed);
                        }
                        else if(y==yf){
                          x = (x+speed>xf) ? (x=xf) : (x+=speed);
                        }
                        for(uint8_t col = 0; col < img.width; col++){
                          for(uint8_t row = 0; row < img.height; row++){
                              drawPixel(x+col, y+row, map[col+row*img.width]);
                          }
                        }
                      }
                    }

                  }
                }
                if (msg.m_notify.interrupts & irq_keyboard) { /* subscribed interrupt */
                  kbc_ih();
                }
                
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
 }
  if (keyboard_unsubscribe()) return 1;  
  if(timer_unsubscribe_int()) return 1;
  if(vg_exit()) return 1;
  return 0;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
