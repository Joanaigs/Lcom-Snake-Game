#include "graphics.h"
#include "macros.h"

int (setMode)(uint16_t mode){

    reg86_t r;
    memset(&r, 0, sizeof(r));
    r.intno = 0x10;
    r.ah = 0x4F;
    r.al = 0x02;
    r.ax = 0x4F02; // VBE call, function 02 -- set VBE mode
    r.bx = 1<<14|mode; // set bit 14: linear framebuffer
    if( sys_int86(&r) != OK ) {
        printf("set_vbe_mode: sys_int86() failed \n");
        return 1;
    }
    return 0;
}


void (vramMap)(){
    int r;
    struct minix_mem_range mr; /* physical memory range */
    unsigned int vram_base=vmi_p.PhysBasePtr; /* VRAM’s physical addresss */
    unsigned int vram_size=vmi_p.XResolution *vmi_p.YResolution* (vmi_p.BitsPerPixel ) >> 3; /* VRAM’s size, but you can use
    the frame-buffer size, instead */
    /* Allow memory mapping */
    mr.mr_base = (phys_bytes) vram_base;
    mr.mr_limit = mr.mr_base + vram_size;
    if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
        panic("sys_privctl (ADD_MEM) failed: %d\n", r);
    /* Map memory */
    video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);
    if(video_mem == MAP_FAILED)
        panic("couldn’t map video memory");
    bits_per_pixel=vmi_p.BitsPerPixel;
    h_res=vmi_p.XResolution;
    v_res= vmi_p.YResolution;
    bytes_per_pixel=(vmi_p.BitsPerPixel) >> 3;
    
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){
    for (uint16_t i = 0; i < len; i++){
        if (x+i >= h_res || y >=v_res) return 1;
        drawPixel(x+i, y, color);
    }
    return 0;
}

void (drawPixel)(uint16_t x, uint16_t y,uint32_t color){
    unsigned int p = (x + y * h_res) * bytes_per_pixel;
    memcpy(video_mem + p, &color,bytes_per_pixel);
}
int (vg_draw_rectangle)(uint16_t x, uint16_t y,uint16_t width, uint16_t height, uint32_t color){
    for (uint16_t i = 0; i < height; i++)
       if(vg_draw_hline(x, y+i, width, color))
            return 1;
    return 0;
}

