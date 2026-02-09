#include <stdio.h>
#include <stddef.h> //size_t, NULL, sizeof
#include <string.h>
#include "termio_stdint.h" //alternates to stdint.h
#include "test_TermIO.h"

#include "tool_term_io.h"
#include "tool_form_io.h"
#include "tool_menu_io.h"

uint8_t g_buf[256];
uint8_t g_stream[64] = {0};

void (*jumpFunc)(void) = (void (*)(void))0UL;

void test_TermIO(void) {
#if 1   /* MENU_IO */
    union {
#if OINTER____SIZEOF_POINTER__ == 2/* GNUC */
        uint16_t u16;
        uint16_t uint;
#elif __SIZEOF_POINTER__ == 4/* GNUC */
        uint32_t u32;
        uint32_t uint;
#elif __SIZEOF_POINTER__ == 8/* GNUC */
        uint64_t u64;
        uint64_t uint;
#elif defined(__TASKING__)
/* https://www.tasking.com/documentation/tricore/ctc/reference/clang_memqual.html */
        uint32_t u32;
        uint32_t uint;
#else
#error "__SIZEOF_POINTER__ is not supported"
#endif
        void* vaddr;
    } __addr__;
    union {
        uint32_t u32;
        void* vaddr;
    } __addr32__;
    uint32_t __hex__;
    uint32_t __size__;
#endif  /* MENU_IO */

    const uint32_t hex = 0xabcdef89U;
    const uint32_t dec = 1000U;
    const uint8_t str[] = "0123456789ABCDEF";

    (void)TERM_IO_Init();

    (void)sprintf((char*)g_buf, "TEST PRINT STRING");
    (void)dprintString((const char*)g_buf);
    (void)dprintString("\n");

    dprintHex(hex, 32U, DPRINT_PRE_HEX, DPRINT_LF);
    dprintHexPFLF(hex, 32U);
    dprintHex(hex, 16U, DPRINT_PRE_HEX, DPRINT_LF);
    dprintHexPFLF(hex, 16U);
    dprintHex(hex,  8U, DPRINT_PRE_HEX, DPRINT_LF);
    dprintHexPFLF(hex,  8U);
    dprintDec(dec, DPRINT_LF);
    dprintDecLF(dec);
    dmemory(str, strlen(str));

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

    for(;;) {
        /* _FEED_COP(); by default, COP is disabled with device init. When enabling, also reset the watchdog. */
#if 1   /* MENU_IO */
        topMenu("de'v'ice, key'i'n, 'e'xit?: ", g_buf);
        if((g_buf[0] == 'v') || (g_buf[0] == 'V'))
        {
            for(;;)
            {
                subMenu("[DEVICE] 'm'emory, go 't'op: ", g_buf);
                if((g_buf[0] == 'm') || (g_buf[0] == 'M'))
                {
                    menuInAddr(__hex__, g_buf);
                    menuInSize(__size__, g_buf);
                    __addr32__.u32 = __hex__;
                    dmemory(__addr32__.vaddr, __size__);
                }
                else if((g_buf[0] == 'c') || (g_buf[0] == 'C'))
                {
                    jumpFunc = (void (*)(void))0UL;

                    __addr32__.vaddr = (void*)jumpFunc;
                    dprintString("default call addr: ");
                    dprintHexPFLF((uint32_t)__addr32__.u32, 32U);
                    dprintString("data in addr: ");
                    dprintHexPFLF((uint32_t)(*((uint32_t*)__addr32__.vaddr)), 32U);

                    subMenu("[CALL] change call address? 'y'es no(ELSE): ", g_buf);
                    if((g_buf[0] == 'y') || (g_buf[0] == 'Y'))
                    {
                        menuInAddr(__hex__, g_buf);
                        __addr32__.u32 = __hex__;
                        jumpFunc = (void (*)(void))__addr32__.vaddr;

                        __addr32__.vaddr = (void*)jumpFunc;
                        dprintString("changed call addr: ");
                        dprintHexPFLF((uint32_t)__addr32__.u32, 32U);
                        dprintString("data in addr: ");
                        dprintHexPFLF((uint32_t)(*((uint32_t*)__addr32__.vaddr)), 32U);
                    }

                    subMenu("[CALL] really jump to this address? 'y'es no(ELSE): ", g_buf);
                    if((g_buf[0] == 'y') || (g_buf[0] == 'Y'))
                    {
                        jumpFunc();
                    }
                }
            }
        }
        else if((g_buf[0] == 'i') || (g_buf[0] == 'I'))
        {
            for(;;)
            {
                subMenu("[KEYIN] 'h'ex, st'r'eam, 's'tring, go 't'op?: ", g_buf);
                if((g_buf[0] == 'h') || (g_buf[0] == 'H'))
                {
                    menuInHex(__hex__, g_buf);
                    dprintHexPFLF(__hex__, 32U);
                }
                else if((g_buf[0] == 'r') || (g_buf[0] == 'R'))
                {
                    manuInStream(g_stream, g_buf);
                    dmemory(g_stream, sizeof(g_stream));
                }
                else if((g_buf[0] == 's') || (g_buf[0] == 'S'))
                {
                    menuInString(g_buf);
                    dprintStringLF(g_buf);
                }
            }
        }
#endif  /* MENU_IO */
    } /* loop forever */
#if defined(__linux__) /* OS_TERMINAL_RESOTRE */
    (void)TERM_IO_DeInit();
#endif /* OS_TERMINAL_RESOTRE */
    /* please make sure that you never leave main */
}

