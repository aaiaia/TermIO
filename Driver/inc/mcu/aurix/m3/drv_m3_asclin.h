#if ( defined(__GNUC__) && defined(__arm__) ) \
 || ( defined(__TASKING__) && defined(__CARM__) )/* MCU */
#ifndef DRV_AURIX_M3_ASCLIN_H
#define DRV_AURIX_M3_ASCLIN_H
#include <stdint.h>

void AURIX_M3_ASCLIN1_Init(void);
void AURIX_M3_ASCLIN1_PutByte(uint8_t c);
uint8_t AURIX_M3_ASCLIN1_GetByte(void);
void AURIX_M3_ASCLIN1_DelByte(void);
void AURIX_M3_ASCLIN1_Deinit(void);

#endif /* DRV_AURIX_M3_ASCLIN_H */
#endif /* MCU */
