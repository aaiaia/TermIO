#define dioStart()          TERM_IO_Init()
#define dioEnd()            TERM_IO_DeInit()
#define dprintString(BUF)   TERM_IO_PutString((const char*)BUF, TERM_IO_PRT_NO)
#define dprintLine()        TERM_IO_PutString("\n", TERM_IO_PRT_NO)
#define dkeyinString(BUF)   TERM_IO_GetString((char*)BUF, sizeof(BUF))
#define dkeyinHEX(BUF)      TERM_IO_GetHexString((char*)BUF, sizeof(BUF))

#include <stdio.h>
#include <stddef.h> //size_t, NULL, sizeof
#if defined(__HIWARE__)
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "hiware_c99_stdint.h"
#else
#include <stdint.h>
#endif /* __HIWARE__ */

#include "drv_s12x_init.h"
#include "tool_term_io.h"

#if defined(__HIWARE__)
void MCU_init(void); /* Device initialization function declaration */
#endif /* __HIWARE__ */

uint8_t g_buf[65];

void main(void) {
#if defined(__HIWARE__)
    MCU_init(); /* call Device Initialization */
    /* put your own code here */
    INIT_setup_Mcu_Clk();
#endif /* __HIWARE__ */
    (void)TERM_IO_Init();

    (void)sprintf((char*)g_buf, "TEST PRINT STRING");
    (void)dprintString((const char*)g_buf);
    (void)dprintString("\n");

    for(;;) {
        /* _FEED_COP(); by default, COP is disabled with device init. When enabling, also reset the watchdog. */
        (void)dprintString("KEYIN(STRING): ");
        (void)dkeyinString(g_buf);
        (void)dprintLine();
        (void)dprintString("PRINT(STRING): ");
        (void)dprintString((const char*)g_buf);
        (void)dprintLine();

        (void)dprintString("KEYIN(HEX): 0x");
        (void)dkeyinHEX(g_buf);
        (void)dprintLine();
        (void)dprintString("PRINT(HEX): 0x");
        (void)dprintString((const char*)g_buf);
        (void)dprintLine();
    } /* loop forever */
#if defined(__linux__) /* OS_TERMINAL_RESOTRE */
    (void)TERM_IO_DeInit();
#endif /* OS_TERMINAL_RESOTRE */
    /* please make sure that you never leave main */
}

