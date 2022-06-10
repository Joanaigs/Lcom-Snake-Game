#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

/** @defgroup i8042 i8042
 * @{
 * 
 * Constansts for programming the i8042 KBC
 */ 


#define KBC_IRQ     1   /* @brief KBC Controller IRQ Line */
#define MOUSE_IRQ   12  /* @brief Mouse IRQ Line */

/* Delay for KBC */
#define DELAY           20000 /* @brief KBC Response Delay */
#define KBC_NUM_TRIES   10    /* @brief Number of tries to issue command before timeout */

/* I/O Ports Addresses */

#define KBC_CMD     0x64 /* @brief Address to send commands to KBC */
#define KBC_CMD_ARG 0x60 /* @brief Address to write KBC Command Arguments */
#define STATUS_REG  0x64 /* @brief KBC Status Register address */

#define OUTPUT_BUF  0x60 /* @brief Address of Output Buffer of KBC */

/* KBC Commands */
#define READ_KBC_CMD    0x20 /* @brief Read KBC Command Byte */
#define WRITE_KBC_CMD   0x60 /* @brief Write KBC Command Byte */
#define KBC_SELF_TEST   0xAA /* @brief KBC Diagnostic Tests */
#define KBC_INT_TEST    0xAB /* @brief Tests Keyboard Clock and Data lines */
#define KBC_INT_DISABLE 0xAD /* @brief Disable KBC Interface */
#define KBC_INT_ENABLE  0xAE /* @brief Enable KBC Interface */
#define MOUSE_DISABLE   0xA7 /* @brief Disable Mouse */
#define MOUSE_ENABLE    0xA8 /* @brief Enable Mouse */
#define MOUSE_INT_TEST  0xA9 /* @brief Tests Mouse data line */
#define MOUSE_WRITE_B   0xD4 /* @brief Write a byte directly to the mouse */

/* Status Byte Masking */

#define OBF     BIT(0) /* @brief Output Buffer State */
#define IBF     BIT(1) /* @brief Input Buffer State */
#define SYS_FLAG        BIT(2) /* @brief System Flag */
#define DATA_CMD_WRITE  BIT(3) /* @brief Identifier of type of byte in input buffer */
#define INH_FLAG        BIT(4) /* @brief Keyboard inihibited */
#define AUX_MOUSE       BIT(5) /* @brief Mouse Data */
#define TIME_OUT_BIT    BIT(6) /* @brief Time Out Error - Invalid Data */
#define PARITY_BIT    BIT(7) /* @brief Parity Error - Invalid Data */

/* Scancode Constants */
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

#define ESC_BREAK_CODE  0x81    /* @brief ESC Break Code */
#define TWO_BYTE_CODE   0xE0    /* @brief First byte of a two byte Scancode */
#define BREAK_CODE_BIT  BIT(7)  /* @brief Bit to distinguish between Make code and Break code */

/* Command byte masks */
#define INT_KBD         BIT(0)  /* @brief Enable Keyboard Interrupts */
#define INT_MOU         BIT(1)  /* @brief Enable Mouse Interrupts */
#define DIS_KBD         BIT(4)  /* @brief Disable Keyboard */
#define DIS_MOU         BIT(5)  /* @brief Disable Mouse */

#define LEFT_BUTTON     BIT(0) /* @brief Left button click event*/
#define RIGHT_BUTTON    BIT(1) /* @brief Right button click event */
#define MIDDLE_BUTTON   BIT(2) /* @brief Middle button click event */
#define FIRST_BYTE_ID   BIT(3) /* @brief Identifier of first byte of packet CAREFUL: Not 100% accurate */
#define MSB_X_DELTA     BIT(4) /* @brief Most significant bit of X delta */
#define MSB_Y_DELTA     BIT(5) /* @brief Most significant bit of Y delta */
#define X_OVERFLOW      BIT(6) /* @brief X delta overflowed */
#define Y_OVERFLOW      BIT(7) /* @brief Y delta overflowed */
// Byte 1 - X delta
// Byte 2 - Y delta

/* Mouse Commands */
#define RESET           0xFF /* @brief Reset mouse */
#define RESEND          0xFE /* @brief Resend command */
#define DEFAULT         0xF6 /* @brief Set default values */
#define DIS_DATA_REP    0xF5 /* @brief Disable Data Reporting */
#define ENABLE_DATA_REP 0xF4 /* @brief Enable Data Reporting */
#define SET_SAMPLE_RT   0xF3 /* @brief Sets state sampling rate */
#define SET_REMOTE_MD   0xF0 /* @brief Sets Mouse on Remote Mode, data on request */
#define READ_DATA       0xEB /* @brief Sends data packet request */
#define SET_STREAM_MD   0xEA /* @brief Sets mouse on Stream Mode, data on events */
#define STATUS_REQUEST  0xE9 /* @brief Get mouse configuration */
#define SET_RESOLUTION  0xE8 /* @brief Sets resolution for mouse movement */
#define SCALING_ACC_MD  0xE7 /* @brief Sets scaling on acceleration mode */
#define SCALING_LIN_MD  0xE6 /* @brief Sets scaling on linear mode */

/* Mouse Controller Responses */
#define ACK_OK      0xFA /* @brief Operation sucessful */
#define ACK_INVALID 0xFE /* @brief Invalid Byte, first occurence */
#define ACK_ERROR   0xFC /* @brief Invalid Byte on resend */

#define DATA_PACKET_BYTES 3

#define DISABLE_MOUSE 0xA7
#define ENABLE_MOUSE 0xA8
#define WRITE_BYTE_TO_MOUSE 0xD4
#define DISABLE_DATA_REPORTING 0xF5
#define ENABLE_DATA_REPORTING 0xF4
#define READ_DATA 0xEB
#define SET_STREAM_MODE 0xEA
#define SET_DEFAULT 0xF6

/** Acknowledgement bytes */
#define ACK 0xFA
#define NACK 0xFE
#define ERROR 0xFC
#endif /*_LCOM_I8042_H_ */
