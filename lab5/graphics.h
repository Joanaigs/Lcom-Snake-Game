#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <stdbool.h>
#include <stdint.h>
#include <lcom/lcf.h>


vbe_mode_info_t vmi_p;
void (vramMap)();
int (setMode)(uint16_t mode);
int (vg_draw_rectangle)(uint16_t x, uint16_t y,uint16_t width, uint16_t height, uint32_t color);
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
void (drawPixel)(uint16_t x, uint16_t y,uint32_t color);
char *video_mem;		/* Process (virtual) address to which VRAM is mapped */

unsigned h_res;	        /* Horizontal resolution in pixels */
unsigned v_res;	        /* Vertical resolution in pixels */
unsigned bits_per_pixel; /* Number of VRAM bits per pixel */
unsigned bytes_per_pixel;


#endif /* _GRAPHICS_H_ */
