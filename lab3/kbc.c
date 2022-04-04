#include <lcom/lcf.h>

#include "kbc.h"
#include "utils.h"
#include "i8042.h"


int (kbc_read_cmd)(uint8_t *cmd){
    int ret = 0;
    if((ret = kbc_issue_cmd(READ_KBC_CMD))) return ret;
    if((ret = kbc_read_byte(cmd))) return ret;
    return 0;
}

int (kbc_change_cmd)(uint8_t cmd){
    int ret = 0;
    if((ret = kbc_issue_cmd(WRITE_KBC_CMD))) return ret;
    if((ret = kbc_issue_arg(cmd))) return ret;
    return 0;
}

int (kbc_restore_keyboard)(){
    int ret = 0;
    uint8_t cmd = 0;
    if((ret = kbc_read_cmd(&cmd))) return ret;
    cmd = (cmd | INT_KBD) & (~DIS_KBD) ;
    if((ret = kbc_change_cmd(cmd))) return ret;
    return 0 ;
}

int (kbc_issue_cmd)(uint8_t cmd){
    int ret = 0;
    uint8_t stat;
    for(int i = 0; i < KBC_NUM_TRIES; ++i){
        if((ret = util_sys_inb(STATUS_REG, &stat))) return ret;
        if((stat&IN_BUF_FULL) == 0){
            if(sys_outb(KBC_CMD, cmd)) return 1;
            return 0;
        }
        tickdelay(micros_to_ticks(DELAY));
    }
    return 1;
}

int (kbc_issue_arg)(uint8_t arg){
    int ret = 0;
    uint8_t stat;
    for(int i = 0; i < KBC_NUM_TRIES; ++i){
        if((ret = util_sys_inb(STATUS_REG, &stat))) return ret;
        if((stat&IN_BUF_FULL) == 0){
            if(sys_outb(KBC_CMD_ARG, arg)) return 1;
            return 0;
        }
        tickdelay(micros_to_ticks(DELAY));
    }
    return 1;
}

int (kbc_read_byte)(uint8_t *byte){
    int ret = 0;
    uint8_t stat;
    while(true){
        if((ret = util_sys_inb(STATUS_REG, &stat))) return ret;
        if((stat&OBF) && (stat&AUX_MOUSE)==0){
            if(stat & (PARITY_BIT | TIME_OUT_BIT)) return 1;
            if((ret = util_sys_inb(OUTPUT_BUF, byte))) return ret;
            else return 0;
        }
        tickdelay(micros_to_ticks(DELAY));
    }
    return 1;
}
