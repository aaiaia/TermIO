#ifndef MENU_IO_H
#define MENU_IO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "termio_stdint.h" //alternates to stdint.h
#include <stddef.h> // size_t, NULL
#include "tool_term_io.h"
#include "tool_form_io.h"

extern const char MENU_IO_IN_HEX[];
extern const char MENU_IO_IN_STREAM[];
extern const char MENU_IO_IN_STRING[];
extern const char MENU_IO_IN_KEYIN[];
extern const char MENU_IO_IN_ADDR[];
extern const char MENU_IO_IN_SIZE[];

uint32_t CONV_IO_hexStringToU32(uint8_t* string);
uint8_t CONV_IO_hexStringToStream(uint8_t* string, uint8_t* stream, uint16_t size);

#if defined(__HIWARE__)
#define MENU_IO_CLR_WATCH_DOG
#elif defined(__COMPILER_FCC911__)
#include "mb91467d.h"
#define MENU_IO_CLR_WATCH_DOG
#else
//defined(__GNUC__) || defined(__TASKING__)
#define MENU_IO_CLR_WATCH_DOG
#endif

#define MENU_IO_IF_GO_TOP(STRBUF) {\
    if((STRBUF[0] == 't') || (STRBUF[0] == 'T'))\
    {\
        break;\
    }\
}
#define MENU_IO_IF_EXIT(STRBUF) {\
    if((STRBUF[0] == 'e') || (STRBUF[0] == 'E'))\
    {\
        TERM_IO_PutString("exit loop" , TERM_IO_PRT_LF);\
        break;\
    }\
}
#define MENU_IO_KEYIN_HEX(U32VAR, STRBUF) {\
    TERM_IO_PutString(MENU_IO_IN_HEX, TERM_IO_PRT_NO);\
    (void)TERM_IO_GetHexString((char*)STRBUF, (sizeof(U32VAR)<<1U)+1U);\
    U32VAR = CONV_IO_hexStringToU32(STRBUF);\
}
#define MENU_IO_KEYIN_HEX_AND_PRINT(U32VAR, STRBUF) {\
    MENU_IO_KEYIN_HEX(U32VAR, STRBUF);\
    TERM_IO_PutString(MENU_IO_IN_KEYIN , TERM_IO_PRT_NO);\
    FORM_IO_printU32ToHex(U32VAR, 32U, FORM_IO_PRE_HEX, TERM_IO_PRT_LF);\
}
#define MENU_IO_KEYIN_STREAM(STREAM, STRBUF) {\
    TERM_IO_PutString(MENU_IO_IN_STREAM, TERM_IO_PRT_NO);\
    (void)TERM_IO_GetHexString((char*)STRBUF, (sizeof(STREAM)<<1U)+1U);\
    (void)CONV_IO_hexStringToStream(STRBUF,\
            STREAM, sizeof(STREAM));\
}
#define MENU_IO_KEYIN_STRING(STRBUF) {\
    TERM_IO_PutString(MENU_IO_IN_STRING, TERM_IO_PRT_NO);\
    TERM_IO_GetString((char*)STRBUF, sizeof(STRBUF));\
}
#define MENU_IO_KEYIN_ADDR(ADDR, STRBUF) {\
    TERM_IO_PutString(MENU_IO_IN_ADDR, TERM_IO_PRT_NO);\
    MENU_IO_KEYIN_HEX(ADDR, STRBUF);\
    TERM_IO_PutString(MENU_IO_IN_KEYIN , TERM_IO_PRT_NO);\
    FORM_IO_printU32ToHex(ADDR, 32U, FORM_IO_PRE_HEX, TERM_IO_PRT_LF);\
}
#define MENU_IO_KEYIN_SIZE(SIZE, STRBUF) {\
    TERM_IO_PutString(MENU_IO_IN_SIZE, TERM_IO_PRT_NO);\
    MENU_IO_KEYIN_HEX(SIZE, STRBUF);\
    TERM_IO_PutString(MENU_IO_IN_KEYIN , TERM_IO_PRT_NO);\
    FORM_IO_printU32ToHex(SIZE, 32U, FORM_IO_PRE_HEX, TERM_IO_PRT_LF);\
}
#define MENU_IO_DEFAULT_MANU(PRINT_MES, STRBUF) {\
    STRBUF[0] = '\0';\
    TERM_IO_PutString(PRINT_MES, TERM_IO_PRT_NO);\
    TERM_IO_GetString((char*)STRBUF, 2U);\
}
#define MENU_IO_SUB_MENU(PRINT_MES, STRBUF) {\
    MENU_IO_DEFAULT_MANU(PRINT_MES, STRBUF);\
    MENU_IO_IF_GO_TOP(STRBUF);\
}
#define MENU_IO_TOP_MENU(PRINT_MES, STRBUF) {\
    MENU_IO_DEFAULT_MANU(PRINT_MES, STRBUF);\
    MENU_IO_IF_EXIT(STRBUF);\
}

#ifdef __cplusplus
}
#endif

#endif /* MENU_IO_H */
