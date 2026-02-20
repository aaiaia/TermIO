#if ( defined(__GNUC__) && defined(__arm__) ) \
 || ( defined(__TASKING__) && defined(__CARM__) )/* MCU */
#include "drv_m3_asclin.h"

#include "ascii_char.h"

typedef volatile struct _FIFOCON
{
    uint32_t reservedA : 16;
    uint32_t fillLevel : 5;
    uint32_t reservedB : 11;
}FIFOCON;

typedef volatile struct _HUART
{
    uint8_t  isInit;
    uint8_t *txData;
    uint8_t *rxData;
    FIFOCON *txCon;
    FIFOCON *rxCon;
}HUART;

#define ASCLIN1TX   ((*(uint32_t *)0xF0000744u))
#define ASCLIN1RX   ((*(uint32_t *)0xF0000748u))

#define ASCLIN1TX_FIFOCON    ((*(FIFOCON *)0xF000070Cu))
#define ASCLIN1RX_FIFOCON    ((*(FIFOCON *)0xF0000710u))

static HUART uart1;

void AURIX_M3_ASCLIN1_Init(void)
{
    uart1.rxData = (uint8_t *)&ASCLIN1RX;
    uart1.rxCon = &ASCLIN1RX_FIFOCON;
    uart1.txData = (uint8_t *)&ASCLIN1TX;
    uart1.txCon = &ASCLIN1TX_FIFOCON;

    uart1.isInit = 1;
}

void AURIX_M3_ASCLIN1_PutByte(uint8_t c)
{
    if(uart1.isInit == 1)
    {
        *uart1.txData = c;
        while(uart1.txCon->fillLevel != 0);
    }
}

void AURIX_M3_ASCLIN1_DelByte(void)
{
    if(uart1.isInit == 1)
    {
        *uart1.txData = ASCII_CHAR_BS;
        while(uart1.txCon->fillLevel != 0);
        *uart1.txData = ASCII_CHAR_DEL;
        while(uart1.txCon->fillLevel != 0);
        *uart1.txData = ASCII_CHAR_BS;
        while(uart1.txCon->fillLevel != 0);
    }
}

uint8_t AURIX_M3_ASCLIN1_GetByte(void)
{
    uint8_t c = 0;
    if(uart1.isInit == 1)
    {
        while(uart1.rxCon->fillLevel == 0);
        c = (uint8_t)(*uart1.rxData);
    }
    return c;
}

void AURIX_M3_ASCLIN1_Deinit(void)
{
    uart1.rxData = (void *)0;
    uart1.rxCon =  (void *)0;
    uart1.txData = (void *)0;
    uart1.txCon =  (void *)0;

    uart1.isInit = 0;
}

#endif /* MCU */
