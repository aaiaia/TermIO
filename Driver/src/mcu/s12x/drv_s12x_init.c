#if defined(__HIWARE__) && defined(__HCS12X__)/* MCU */

#include <hidef.h>          /* common defines and macros */
#include "derivative.h"     /* derivative-specific definitions */

#include "drv_s12x_init.h"

void INIT_setup_Mcu_Clk(void)
{
    /* ECLKCTL: NECLK=1,NCLKX2=1,DIV16=0,EDIV4=0,EDIV3=0,EDIV2=0,EDIV1=0,EDIV0=0 */
    setReg8(ECLKCTL, 192U);
    /*  System clock initialization */
    /* CLKSEL: PLLSEL=0,PSTP=0,XCLKS=0,??=0,PLLWAI=0,??=0,RTIWAI=0,COPWAI=0 */
    setReg8(CLKSEL, 0U);                 /* Select clock source from XTAL and set bits in CLKSEL reg. */
    /* PLLCTL: CME=1,PLLON=0,FM1=0,FM0=0,FSTWKP=0,PRE=0,PCE=0,SCME=1 */
    setReg8(PLLCTL, 129U);               /* Disable the PLL */
    /* SYNR: VCOFRQ1=0,VCOFRQ0=1,SYNDIV5=0,SYNDIV4=0,SYNDIV3=0,SYNDIV2=0,SYNDIV1=1,SYNDIV0=1 */
    setReg8(SYNR, 67U);                  /* Set the multiplier register */
    /* REFDV: REFFRQ1=1,REFFRQ0=0,REFDIV5=0,REFDIV4=0,REFDIV3=0,REFDIV2=0,REFDIV1=0,REFDIV0=0 */
    setReg8(REFDV, 128U);                /* Set the divider register */
    /* POSTDIV: ??=0,??=0,??=0,POSTDIV4=0,POSTDIV3=0,POSTDIV2=0,POSTDIV1=0,POSTDIV0=0 */
    setReg8(POSTDIV, 0U);                /* Set the post divider register */
    /* PLLCTL: CME=1,PLLON=1,FM1=0,FM0=0,FSTWKP=0,PRE=0,PCE=0,SCME=1 */
    setReg8(PLLCTL, 193U);
    while(CRGFLG_LOCK == 0U) {           /* Wait until the PLL is within the desired tolerance of the target frequency */
    }
    /* CLKSEL: PLLSEL=1 */
    setReg8Bits(CLKSEL, 128U);           /* Select clock source from PLL */
}

#endif /* defined(__HIWARE__) && defined(__HCS12X__) *//* MCU */