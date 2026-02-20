#ifndef TOOL_TEST_IO_H
#define TOOL_TEST_IO_H
#include "tool_term_io.h"
#include "tool_form_io.h"
#include "tool_menu_io.h"
#define DPRINT_NO                           TERM_IO_PRT_NO
#define DPRINT_LF                           TERM_IO_PRT_LF
#define dioStart()                          TERM_IO_Init()
#define dioEnd()                            TERM_IO_DeInit()
#define dprintString(BUF)                   TERM_IO_PutString((const char*)BUF, TERM_IO_PRT_NO)
#define dprintStringLF(BUF)                 TERM_IO_PutString((const char*)BUF, TERM_IO_PRT_LF)
#define dprintLine()                        TERM_IO_PutString("\n", TERM_IO_PRT_NO)
#define dkeyinString(BUF)                   TERM_IO_GetString((char*)BUF, sizeof(BUF))
#define dkeyinHEX(BUF)                      TERM_IO_GetHexString((char*)BUF, sizeof(BUF))
#define DPRINT_PRE_NO                       FORM_IO_PRE_NO
#define DPRINT_PRE_HEX                      FORM_IO_PRE_HEX
#define dprintHex(U32, BITLEN, PREFIX, LF)  FORM_IO_printU32ToHex(U32, BITLEN, PREFIX, LF)
#define dprintHexLF(U32, BITLEN)            FORM_IO_printU32ToHex(U32, BITLEN, DPRINT_PRE_HEX, DPRINT_LF)
#define dprintDec(U32, LF)                  FORM_IO_printU32ToDec(U32, LF)
#define dprintDecLF(U32)                    FORM_IO_printU32ToDec(U32, DPRINT_LF)
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
#endif  /* TOOL_TEST_IO_H */
