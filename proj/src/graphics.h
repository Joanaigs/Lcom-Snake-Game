#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <stdbool.h>
#include <stdint.h>
#include <lcom/lcf.h>


vbe_mode_info_t vmi_p;
int (setMode)(uint16_t mode);
void (vramMap)();
void (drawPixel)(uint16_t x, uint16_t y,uint32_t color);
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
int (vg_draw_rectangle)(uint16_t x, uint16_t y,uint16_t width, uint16_t height, uint32_t color);
void (draw_xpm)(xpm_image_t img, uint8_t *map, int x, int y);
void (draw_xpm_video_mem)(xpm_image_t img, uint8_t *map, int x, int y);
void (erase_xpm)(xpm_image_t img, int x, int y, xpm_image_t background);


char *video_mem;		/* Process (virtual) address to which VRAM is mapped */
char *video_mem_buf;
void copy_buffer_to_mem();

int h_res;	        /* Horizontal resolution in pixels */
int v_res;	        /* Vertical resolution in pixels */
unsigned bits_per_pixel; /* Number of VRAM bits per pixel */
unsigned bytes_per_pixel;


#endif /* _GRAPHICS_H_ */
