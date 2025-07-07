#ifndef COMM_IO_H
#define COMM_IO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ascii_char.h"

#if defined(__GNUC__) && defined(__linux__)/* COMPILER_ID + OS */
#include <stdio.h>
#include "drv_linux_term.h"
#define INIT_COMM_IO()      linuxTermInit()
#define DEINIT_COMM_IO()    linuxTermRestore()
#define GET_CHAR()          ((int)getchar())            // has return value
#define PUT_CHAR(C)         putchar((int)C)             // has return value
#define DEL_CHAR()          linuxTermDelChar()
#define ESC_CHAR(C)         PUT_CHAR(ASCII_CHAR_LF)
#define ECHO_CHAR(C)        linuxTermEchoBack(C)        // has return value

#define CTRL_KEY_ESC        ASCII_CHAR_ESC
#define CTRL_KEY_DELETE     ASCII_CHAR_DEL
#define CTRL_KEY_ENTER      ASCII_CHAR_LF
#elif defined(__HIWARE__) && defined(__HCS12X__)/* COMPILER_ID + MCU */
#include "hiware_c99_stdint.h"
#include "drv_s12x_uart.h"
#define INIT_COMM_IO() { \
    Uart1_Init(0x0011); \
    Uart1_SetPin(); \
}
#define DEINIT_COMM_IO()
#define GET_CHAR()          ((uint8_t)Uart1_GetByte())  // has return value
#define PUT_CHAR(C)         Uart1_PutByte((uint8_t)C)   // has return value
#define DEL_CHAR()          Uart1_DelByte()     // has no return
#define ESC_CHAR()          PUT_CHAR(ASCII_CHAR_LF)
#define ECHO_CHAR(C)        PUT_CHAR(C)

#define CTRL_KEY_ESC        ASCII_CHAR_ESC
#define CTRL_KEY_DELETE     ASCII_CHAR_BS
#define CTRL_KEY_ENTER      ASCII_CHAR_LF
#else/* COMPILER_ID + NOT_SUPPORT */
#warning "Not Support TermIO in this COMPILER"
#define INIT_COMM_IO()
#define DEINIT_COMM_IO()
#define GET_CHAR()          '\0'
#define PUT_CHAR(C)         '\0'
#define DEL_CHAR()
#define ESC_CHAR()
#define ECHO_CHAR(C)

#define CTRL_KEY_ESC        ASCII_CHAR_ESC
#define CTRL_KEY_DELETE     ASCII_CHAR_BS
#define CTRL_KEY_ENTER      ASCII_CHAR_LF
#endif/* COMPILER_ID + END_PRE_PROCESSING */

#ifdef __cplusplus
}
#endif

#endif /* COMM_IO_H */
