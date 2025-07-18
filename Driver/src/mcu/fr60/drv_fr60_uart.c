#if defined(__COMPILER_FCC911__) && defined(__CPU_MB91F467D__)/* MCU */

/*
 * AUTOCRYPT Developer Note
 * "derivative.h" is IDE generated header file.
 * the file include pre-defined target core register and symbols to
 * control MCUs.
 */
#include "mb91467d.h"

#include "fcc911_c99_stdint.h"
#include "ascii_char.h"

#include "drv_fr60_uart.h"

#define __UART_GET_BYTE__(SREG, DREG, BYTE, IN_WAIT_STATEMENT) { \
    while(!SREG)    IN_WAIT_STATEMENT; \
    BYTE = DREG; \
}
#define __UART_PUT_BYTE__(SREG, DREG, BYTE, IN_WAIT_STATEMENT) { \
    while(!SREG)    IN_WAIT_STATEMENT; \
    DREG = BYTE; \
}

#ifdef ENABLE_UART_STRING_ECHO
#define __UART_ECHO__(SREG, DREG, DATA, IN_WAIT_STATEMENT) { \
    __UART_PUT_BYTE__(SREG, DREG, DATA, IN_WAIT_STATEMENT); \
}
#define __UART_DEL__(SREG, DREG, IN_WAIT_STATEMENT) { \
    __UART_PUT_BYTE__(SREG, DREG, ASCII_CHAR_BS, IN_WAIT_STATEMENT); \
    __UART_PUT_BYTE__(SREG, DREG, ASCII_CHAR_DEL, IN_WAIT_STATEMENT); \
    __UART_PUT_BYTE__(SREG, DREG, ASCII_CHAR_BS, IN_WAIT_STATEMENT); \
}
#define __UART_ESC__(REG) { \
    __UART_PUT_BYTE__(SREG, DREG, ASCII_CHAR_LF, IN_WAIT_STATEMENT); \
}
#else
#define __UART_ECHO__(SREG, DREG, DATA, IN_WAIT_STATEMENT)
#define __UART_DEL__(SREG, DREG, IN_WAIT_STATEMENT)
#define __UART_ESC__(SREG, DREG, IN_WAIT_STATEMENT)
#endif /* ENABLE_UART_STRING_ECHO */

void FR60_Uart4_SetPin(void)
{
    PFR19_D0 = 1;       // enable UART
    PFR19_D1 = 1;       // enable UART
    //EPFR19_D1 = 0;    // enable UART
}

void FR60_Uart4_Init(void)
{
    //Baud Rate
    // V=[F/b]-1
    //example 16MHz, 19200baud
    // v = [16000000/19200]-1 = 832
#if 1 /* BAUDRATE_REG_SELECTED */
    BGR04 = 137;        // 115200 baud at 16MHz CLKP
#endif/* BAUDRATE_REG_SELECTED */
#if 0 /* BAUDRATE_REG_EXAMPLE */
    BGR04 = 416;        // 38400 baud at 16MHz CLKP
    BGR04 = 832;        // 19200 baud at 16MHz CLKP
    BGR04 = 1537;       // 10400 baud at 16MHz CLKP
    BGR04 = 1666;       //  9600 baud at 16MHz CLKP
#endif/* BAUDRATE_REG_EXAMPLE */
    //SCR : Serial Control Register
    //  15 | 14 | 13  | 12 || 11 | 10  |  9  | 8
    // PEN |  P | SBL | CL || AD | CRE | RXE | TXE
    SCR04 = 0x17;       // 8 bit, clear reception errors, Tx & Rx enabled
    //SSR : Serial Status Register
    //  15 | 14 | 13  |  12  ||  11  | 10  |  9  | 8
    //  PE | ORE| FRE | RDRF || TDRE | BDS | RIE | TIE
    SSR04 = 0x00;       // LSB First, enable receive interrupts
    //SMR : Serial Mode Register
    //  7  |  6  |  5  |  4  ||  3   |  2   |  1   |  0
    // MD1 | MD0 | OTO | EXT || REST | UPCL | SCKE | SOE
    SMR04 = 0x0D;       // Mode 0, Reset Counter, Reset UART, SOT0 enabled
}

uint8_t FR60_Uart4_PutByte(const uint8_t byte)
{
    __UART_PUT_BYTE__(SSR04_TDRE, TDR04, byte, HWWD_CL = 0);

    return byte;
}

uint8_t FR60_Uart4_GetByte(void)
{
    uint8_t byte;

    __UART_GET_BYTE__(SSR04_RDRF, RDR04, byte, HWWD_CL = 0);

    return byte;
}

void FR60_Uart4_DelByte(void)
{
    __UART_DEL__(SSR04_TDRE, TDR04, HWWD_CL = 0);
}

void FR60_Uart4_SendString(const char* string, const char lf)
{
    size_t i = 0U;
    while(string[i] != ASCII_CHAR_NUL)
    {
        __UART_PUT_BYTE__(SSR04_TDRE, TDR04, string[i], HWWD_CL = 0);
        i++;
    }
    if(lf != UART_NO_LINE)
    {
        __UART_PUT_BYTE__(SSR04_TDRE, TDR04, ASCII_CHAR_LF, HWWD_CL = 0);
    }
}

void FR60_Uart4_SendData(const uint8_t* buffer, const size_t size)
{
    size_t i;
    for(i = 0U; i < size; i++)
    {
        __UART_PUT_BYTE__(SSR04_TDRE, TDR04, buffer[i], HWWD_CL = 0);
        i++;
    }
}

size_t FR60_Uart4_GetData(uint8_t* buffer, const size_t size)
{
    size_t i;
    for(i = 0U; i < size; i++)
    {
        __UART_GET_BYTE__(SSR04_RDRF, RDR04, buffer[i], HWWD_CL = 0);
    }

    return i;
}

#endif /* defined(__COMPILER_FCC911__) && defined(__CPU_MB91F467D__) *//* MCU */
