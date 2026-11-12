#if ( defined(__GNUC__) && defined(__RH850G4MH__) ) \
 || ( defined(__ghs__) && defined(__RH850G4MH__) )/* MCU */
#ifndef DRV_RH850_G4MH_RLN_H
#define DRV_RH850_G4MH_RLN_H
#include <stdint.h>

void RH850_G4MH_RLN30_Init(void);
void RH850_G4MH_RLN30_PutByte(uint8_t c);
uint8_t RH850_G4MH_RLN30_GetByte(void);
int RH850_G4MH_RLN30_GetByte_TimeOut(uint8_t* c, uint32_t timeout);
void RH850_G4MH_RLN30_DelByte(void);
void RH850_G4MH_RLN30_Deinit(void);

#endif /* DRV_RH850_G4MH_RLN_H */
#endif /* MCU */
