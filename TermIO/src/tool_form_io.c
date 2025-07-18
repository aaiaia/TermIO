#include <stdio.h>

#include "tool_form_io.h"

#include "ascii_char.h"
#include "tool_comm_io.h"
#include "tool_term_io.h"

void FORM_IO_printU32ToHex(const uint32_t ui32, const uint8_t bits, const char prefix, const char lf)
{
    uint8_t sftr;
    uint8_t hex;

    if(prefix != FORM_IO_PRE_NO)
    {
        TERM_IO_PutString("0x", TERM_IO_PRT_NO);
    }

    for(sftr = bits; sftr != 0U; sftr -= 4U)
    {
        hex = (uint8_t)(ui32 >> (sftr - 4U));
        hex &= 0xFU;
        if(hex < 0xAU)  hex += ('0' - 0x0U);
        else            hex += ('A' - 0xAU);
        PUT_CHAR(hex);
    }
    if(lf != TERM_IO_PRT_NO)
    {
        PUT_CHAR(ASCII_CHAR_LF);
    }
}

void FORM_IO_printU32ToDec(const uint32_t ui32, const char lf)
{
    char buf[12];

    (void)sprintf(buf, "%lu", ui32);

    TERM_IO_PutString(buf, TERM_IO_PRT_NO);

    if(lf != TERM_IO_PRT_NO)
    {
        PUT_CHAR(ASCII_CHAR_LF);
    }
}

void FORM_IO_printMemory(const void* addr, const uint32_t size)
{
#define _ADDR_BIT_LEN_  (sizeof(void*) << 3U)
#define _BYTE_BIT_LEN_  (sizeof(uint8_t) << 3U)
    uint32_t i, j=0UL;
    for(i = 0UL; i < size; i+=16UL)
    {
        TERM_IO_PutString("[", TERM_IO_PRT_NO);
        FORM_IO_printU32ToHex((uint32_t)(&((uint8_t*)addr)[i]), _ADDR_BIT_LEN_, FORM_IO_PRE_HEX, TERM_IO_PRT_NO);
        TERM_IO_PutString("]\t", TERM_IO_PRT_NO);

        TERM_IO_PutString("0x ", TERM_IO_PRT_NO);
        for(j = 0U; j < 16UL; j++)
        {
            FORM_IO_printU32ToHex((uint32_t)(((uint8_t*)addr)[i+j]), _BYTE_BIT_LEN_, FORM_IO_PRE_NO, TERM_IO_PRT_NO);
            TERM_IO_PutString(" ", TERM_IO_PRT_NO);
            if(i+j+1U >= size)
            {
                break;
            }
        }
        TERM_IO_PutString("", TERM_IO_PRT_LF);
    }
    TERM_IO_PutString("[size = ", TERM_IO_PRT_NO);
    FORM_IO_printU32ToHex(size, 32U, FORM_IO_PRE_HEX, TERM_IO_PRT_NO);
    TERM_IO_PutString("]", TERM_IO_PRT_LF);
#undef _ADDR_BIT_LEN_
#undef _BYTE_BIT_LEN_
}
