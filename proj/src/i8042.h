#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

/** @defgroup i8042 i8042
 * @{
 * 
 * Constansts for programming the i8042 KBC
 */ 


#define KBC_IRQ     1   
#define MOUSE_IRQ   12  

/* Ports*/

#define CMD_KBC     0x64 /* send commands to KBC */
#define CMD_KBC_ARG 0x60 /* write KBC Command Arguments */
#define STATUS_REG  0x64 /* KBC Status Register address */

#define OUTPUT_BUF  0x60 /* Address of Output Buffer of KBC */

/* KBC Commands */
#define R_KBC    0x20 /*Read KBC Command Byte */
#define W_KBC  0x60 /*  Write KBC Command Byte */
#define DISABLE_KBC 0xAD /*  Disable KBC Interface */
#define ENABLE_KBC  0xAE /* Enable KBC Interface */
#define DISABLE_MOUSE   0xA7 /* Disable Mouse */
#define ENABLE_MOUSE    0xA8 /* Enable Mouse */
#define MOUSE_TEST  0xA9 /* Tests Mouse data line */
#define MOUSE_WRITE_B   0xD4 /* Write a byte to the mouse */

/* Status */

#define OBF     BIT(0) /* Output Buffer State */
#define IBF     BIT(1) /* Input Buffer State */
#define SYS_FLAG        BIT(2) /*  System Flag */
#define DATA__WRITE  BIT(3) /* Type of byte in input buffer */
#define INH_FLAG        BIT(4) /* Keyboard inihibited */
#define AUX_MOUSE       BIT(5) /*Mouse Data */
#define TIME_OUT    BIT(6) /* Time Out*/
#define PARITY    BIT(7) /* Parity */

/* Scancode */

#define ESC_BREAK_CODE  0x81    /* ESC */
#define ENTER_BREAK_CODE  0x1C    /* ENTER */
#define W_BREAK_CODE 0x91 /* W */ 
#define D_BREAK_CODE 0xa0 /* D */ 
#define S_BREAK_CODE 0x9f /* S */ 
#define A_BREAK_CODE 0x9e /* A */ 
#define UP_BREAK_CODE 0xC8 /* UP */ 
#define RIGHT_BREAK_CODE 0xCD /* RIGHT */ 
#define DOWN_BREAK_CODE 0xD0 /* DOWN */ 
#define LEFT_BREAK_CODE 0xCB /* LEFT */ 
#define W_MAKE_CODE 0x11 /* W */ 
#define D_MAKE_CODE 0x20 /* D */ 
#define S_MAKE_CODE 0x1f /* S */ 
#define A_MAKE_CODE 0x1e /* A */ 
#define UP_MAKE_CODE 0x48 /* UP */ 
#define RIGHT_MAKE_CODE 0x4d /* RIGHT */ 
#define DOWN_MAKE_CODE 0x50 /* DOWN */ 
#define LEFT_MAKE_CODE 0x4b /* LEFT */ 
#define TWO_BYTE_CODE   0xE0    /* First of a two byte Scancode */
#define BREAK_CODE  BIT(7)  /* Distinguish between Make code and Break code */

/* Command byte masks */
#define INT_KBD         BIT(0)  /* Enable Keyboard Interrupts */
#define INT_MOU         BIT(1)  /* Enable Mouse Interrupts */
#define DIS_KBD         BIT(4)  /* Disable Keyboard */
#define DIS_MOU         BIT(5)  /* Disable Mouse */

#endif /*_LCOM_I8042_H_ */
