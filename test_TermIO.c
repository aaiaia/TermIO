#define DPRINT_NO               TERM_IO_PRT_NO
#define DPRINT_LF               TERM_IO_PRT_LF
#define dioStart()              TERM_IO_Init()
#define dioEnd()                TERM_IO_DeInit()
#define dprintString(BUF)       TERM_IO_PutString((const char*)BUF, TERM_IO_PRT_NO)
#define dprintStringLF(BUF, LF)             TERM_IO_PutString((const char*)BUF, LF)
#define dprintLine()                        TERM_IO_PutString("\n", TERM_IO_PRT_NO)
#define dkeyinString(BUF)                   TERM_IO_GetString((char*)BUF, sizeof(BUF))
#define dkeyinHEX(BUF)                      TERM_IO_GetHexString((char*)BUF, sizeof(BUF))
#define dprintHex(U32, BITLEN, PREFIX, LF)  FORM_IO_printU32ToHex(U32, BITLEN, PREFIX, LF);
#define dprintDec(U32, LF)                  FORM_IO_printU32ToDec(U32, LF);
#define dmemory(ADDR, SIZE)                 FORM_IO_printMemory((const void*)ADDR, SIZE)

#define menuInHex(U32VAR, STRBUF)           MENU_IO_KEYIN_HEX(U32VAR, STRBUF)
#define menuInHexAndPrint(U32VAR, STRBUF)   MENU_IO_KEYIN_HEX_AND_PRINT(U32VAR, STRBUF)
#define manuInStream(STREAM, STRBUF)        MENU_IO_KEYIN_STREAM(STREAM, STRBUF)
#define menuInString(STRBUF)                MENU_IO_KEYIN_STRING(STRBUF)
#define menuInAddr(ADDR, STRBUF)            MENU_IO_KEYIN_ADDR(ADDR, STRBUF)
#define menuInSize(SIZE, STRBUF)            MENU_IO_KEYIN_SIZE(SIZE, STRBUF)
#define defaultMenu(PRINT_MES, STRBUF)      MENU_IO_DEFAULT_MANU(PRINT_MES, STRBUF)
#define subMenu(PRINT_MES, STRBUF)          MENU_IO_SUB_MENU(PRINT_MES, STRBUF)
#define topMenu(PRINT_MES, STRBUF)          MENU_IO_TOP_MENU(PRINT_MES, STRBUF)

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
#include "tool_menu_io.h"

uint8_t g_buf[256];
uint8_t g_stream[64] = {0};

void (*jumpFunc)(void) = (void (*)(void))0UL;

void test_TermIO(void) {
#if 1   /* MENU_IO */
    union {
#if __SIZEOF_POINTER__ == 2
        uint16_t u16;
        uint16_t uint;
#elif __SIZEOF_POINTER__ == 4
        uint32_t u32;
        uint32_t uint;
#elif __SIZEOF_POINTER__ == 8
        uint64_t u64;
        uint64_t uint;
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

    dprintHex(hex, 32U, FORM_IO_PRE_HEX, DPRINT_LF);
    dprintHex(hex, 16U, FORM_IO_PRE_HEX, DPRINT_LF);
    dprintHex(hex,  8U, FORM_IO_PRE_HEX, DPRINT_LF);
    dprintDec(dec, DPRINT_LF);
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
                    dprintStringLF("default call addr: " , TERM_IO_PRT_NO);
                    dprintHex((uint32_t)__addr32__.u32, 32U, FORM_IO_PRE_HEX, DPRINT_LF);
                    dprintStringLF("data in addr: " , TERM_IO_PRT_NO);
                    dprintHex((uint32_t)(*((uint32_t*)__addr32__.vaddr)), 32U, FORM_IO_PRE_HEX, DPRINT_LF);

                    subMenu("[CALL] change call address? 'y'es no(ELSE): ", g_buf);
                    if((g_buf[0] == 'y') || (g_buf[0] == 'Y'))
                    {
                        menuInAddr(__hex__, g_buf);
                        __addr32__.u32 = __hex__;
                        jumpFunc = (void (*)(void))__addr32__.vaddr;

                        __addr32__.vaddr = (void*)jumpFunc;
                        dprintStringLF("changed call addr: " , TERM_IO_PRT_NO);
                        dprintHex((uint32_t)__addr32__.u32, 32U, FORM_IO_PRE_HEX, DPRINT_LF);
                        dprintStringLF("data in addr: " , TERM_IO_PRT_NO);
                        dprintHex((uint32_t)(*((uint32_t*)__addr32__.vaddr)), 32U, FORM_IO_PRE_HEX, DPRINT_LF);
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
                    dprintHex(__hex__, 32U, FORM_IO_PRE_HEX, DPRINT_LF);
                }
                else if((g_buf[0] == 'r') || (g_buf[0] == 'R'))
                {
                    manuInStream(g_stream, g_buf);
                    dmemory(g_stream, sizeof(g_stream));
                }
                else if((g_buf[0] == 's') || (g_buf[0] == 'S'))
                {
                    menuInString(g_buf);
                    dprintStringLF(g_buf , DPRINT_LF);
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

