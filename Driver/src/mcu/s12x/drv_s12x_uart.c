#if defined(__HIWARE__) && defined(__HCS12X__)/* MCU */

#include <hidef.h>          /* common defines and macros */
/*
 * AUTOCRYPT Developer Note
 * "derivative.h" is IDE generated header file.
 * the file include pre-defined target core register and symbols to
 * control MCUs.
 */
#include "derivative.h"     /* derivative-specific definitions */

#include "hiware_c99_stdint.h"
#include "ascii_char.h"

#include "drv_s12x_uart.h"

#define __UART_GET_BYTE__(SREG, DREG, BYTE) { \
    while(!SREG); \
    BYTE = DREG; \
}
#define __UART_PUT_BYTE__(SREG, DREG, BYTE) { \
    while(!SREG); \
    DREG = BYTE; \
}

#ifdef ENABLE_UART_STRING_ECHO
#define __UART_ECHO__(REG, DATA) { \
    REG = DATA; \
}
#define __UART_DEL__(SREG, DREG) { \
    __UART_PUT_BYTE__(SREG, DREG, ASCII_CHAR_BS); \
    __UART_PUT_BYTE__(SREG, DREG, ASCII_CHAR_DEL); \
    __UART_PUT_BYTE__(SREG, DREG, ASCII_CHAR_BS); \
}
#define __UART_ESC__(REG) { \
    REG = ASCII_CHAR_LF; \
}
#else
#define __UART_ECHO__(REG, DATA)
#define __UART_DEL__(SREG, DREG)
#define __UART_ESC__(REG)
#endif /* ENABLE_UART_STRING_ECHO */

void Uart1_SetPin(void)
{
#define INFUNC_GPIOM_TO_SCI1    0x2
    MODRRSTR regMODRR;

    regMODRR.Byte = MODRR;
    regMODRR.MergedBits.grpMODRR_6 = INFUNC_GPIOM_TO_SCI1;
    MODRR = regMODRR.Byte;
#undef INFUNC_GPIOM_TO_SCI1
}

void Uart1_Init(uint16_t reg16_scibd)
{
    SCI1CR2STR regSCI1CR2;

    SCI1BD = reg16_scibd;

    regSCI1CR2.Byte = SCI1CR2;
#if 1   /* ENABLE_SCI_RX */
    regSCI1CR2.Bits.RE = 1U;    // Receiver Enable Bit
#endif  /* ENABLE_SCI_RX */
    regSCI1CR2.Bits.TE = 1U;    // Transmitter Enable Bit

    SCI1CR2 = regSCI1CR2.Byte;
}

uint8_t Uart1_PutByte(const uint8_t byte)
{
    __UART_PUT_BYTE__(SCI1SR1_TC, SCI1DRL, byte);

    return byte;
}

uint8_t Uart1_GetByte(void)
{
    uint8_t byte;

    __UART_GET_BYTE__(SCI1SR1_RDRF, SCI1DRL, byte);

    return byte;
}

void Uart1_DelByte(void)
{
    __UART_DEL__(SCI1SR1_TC, SCI1DRL);
}

void Uart1_SendString(const char* string, const char lf)
{
    size_t i = 0U;
    while(string[i] != ASCII_CHAR_NUL)
    {
        __UART_PUT_BYTE__(SCI1SR1_TC, SCI1DRL, string[i]);
        i++;
    }
    if(lf != UART_NO_LINE)
    {
        __UART_PUT_BYTE__(SCI1SR1_TC, SCI1DRL, ASCII_CHAR_LF);
    }
}

void Uart1_SendData(const uint8_t* buffer, const size_t size)
{
    size_t i;
    for(i = 0U; i < size; i++)
    {
        __UART_PUT_BYTE__(SCI1SR1_TC, SCI1DRL, buffer[i]);
        i++;
    }
}

size_t Uart1_GetData(uint8_t* buffer, const size_t size)
{
    size_t i;
    for(i = 0U; i < size; i++)
    {
        __UART_GET_BYTE__(SCI1SR1_RDRF, SCI1DRL, buffer[i]);
    }

    return i;
}

#endif /* defined(__HIWARE__) && defined(__HCS12X__) *//* MCU */