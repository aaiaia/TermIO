#ifndef DRV_FR60_UART_H
#define DRV_FR60_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h> //NULL, size_t

#if defined(__COMPILER_FCC911__) && defined(__CPU_MB91F467D__)/* MCU */
#include "drv_fr60_uart.h"

#if 1   /* ENABLE_UART_STRING_ECHO */
#define ENABLE_UART_STRING_ECHO
#endif  /* ENABLE_UART_STRING_ECHO */

#define UART_NO_LINE            0
#define UART_LINE               1
#define UART_NO_PREFIX          0
#define UART_HEX_PREFIX         1

void FR60_Uart4_SetPin(void);
void FR60_Uart4_Init(void);
uint8_t FR60_Uart4_PutByte(const uint8_t val);
uint8_t FR60_Uart4_GetByte(void);
void FR60_Uart4_DelByte(void);
void FR60_Uart4_SendString(const char* string, const char lf);
void FR60_Uart4_SendData(const uint8_t* buffer, const size_t size);
size_t FR60_Uart4_GetData(uint8_t* buffer, const size_t size);

#endif /* defined(__COMPILER_FCC911__) && defined(__CPU_MB91F467D__) *//* MCU */

#ifdef __cplusplus
}
#endif

#endif /* DRV_FR60_UART_H */
