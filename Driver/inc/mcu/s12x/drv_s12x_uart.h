#ifndef DRV_S12X_UART_H
#define DRV_S12X_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h> //NULL, size_t

#if defined(__HIWARE__) && defined(__HCS12X__)/* MCU */
#include "drv_s12x_uart.h"

#if 1   /* ENABLE_UART_STRING_ECHO */
#define ENABLE_UART_STRING_ECHO
#endif  /* ENABLE_UART_STRING_ECHO */

#define UART_NO_LINE            0
#define UART_LINE               1
#define UART_NO_PREFIX          0
#define UART_HEX_PREFIX         1

void S12X_Uart1_SetPin(void);
void S12X_Uart1_Init(uint16_t reg16_scibd);
uint8_t S12X_Uart1_PutByte(const uint8_t val);
uint8_t S12X_Uart1_GetByte(void);
void S12X_Uart1_DelByte(void);
void S12X_Uart1_SendString(const char* string, const char lf);
void S12X_Uart1_SendData(const uint8_t* buffer, const size_t size);
size_t S12X_Uart1_GetData(uint8_t* buffer, const size_t size);

#endif /* defined(__HIWARE__) && defined(__HCS12X__) *//* MCU */

#ifdef __cplusplus
}
#endif

#endif /* DRV_S12X_UART_H */
