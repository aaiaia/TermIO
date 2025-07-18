#define dioStart()          TERM_IO_Init()
#define dioEnd()            TERM_IO_DeInit()
#define dprintString(BUF)   TERM_IO_PutString((const char*)BUF, TERM_IO_PRT_NO)
#define dprintLine()        TERM_IO_PutString("\n", TERM_IO_PRT_NO)
#define dkeyinString(BUF)   TERM_IO_GetString((char*)BUF, sizeof(BUF))
#define dkeyinHEX(BUF)      TERM_IO_GetHexString((char*)BUF, sizeof(BUF))
#define dprintHex(U32, BITLEN, PREFIX, LF)  \
                            FORM_IO_printU32ToHex(U32, BITLEN, PREFIX, LF);
#define dprintDec(U32, LF)  FORM_IO_printU32ToDec(U32, LF);
#define dmemory(ADDR, SIZE) FORM_IO_printMemory((const void*)ADDR, SIZE)

#include <stdio.h>
#include <stddef.h> //size_t, NULL, sizeof
#include <string.h>
#if defined(__HIWARE__)
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "hiware_c99_stdint.h"
#elif defined(__COMPILER_FCC911__)
#include "mb91467d.h"
#include "fcc911_c99_stdint.h"
#else
#include <stdint.h>
#endif /* __HIWARE__ */

#include "tool_term_io.h"
#include "tool_form_io.h"

uint8_t g_buf[65];

void main(void) {
    const uint32_t hex = 0xabcdef89U;
    const uint32_t dec = 1000U;
    const uint8_t str[] = "0123456789ABCDEF";

    (void)TERM_IO_Init();

    (void)sprintf((char*)g_buf, "TEST PRINT STRING");
    (void)dprintString((const char*)g_buf);
    (void)dprintString("\n");

    dprintHex(hex, 32U, FORM_IO_PRE_HEX, TERM_IO_PRT_LF);
    dprintHex(hex, 16U, FORM_IO_PRE_HEX, TERM_IO_PRT_LF);
    dprintHex(hex,  8U, FORM_IO_PRE_HEX, TERM_IO_PRT_LF);
    dprintDec(dec, TERM_IO_PRT_LF);
    dmemory(str, strlen(str));

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

