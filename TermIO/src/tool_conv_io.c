#include "tool_conv_io.h"
#include "tool_term_io.h"

uint32_t CONV_IO_hexStringToU32(uint8_t* string)
{
    uint32_t value = 0x0UL;
    uint16_t i;
    for(i = 0U; string[i] != '\0'; i++)
    {
        value = value << 4U;
        if      (('A' <= string[i]) && (string[i] <= 'F'))
        {
            value |= (0xAU + (string[i] - 'A'));
        }
        else if (('a' <= string[i]) && (string[i] <= 'f'))
        {
            value |= (0xAU + (string[i] - 'a'));
        }
        else if (('0' <= string[i]) && (string[i] <= '9'))
        {
            value |= (0x0U + (string[i] - '0'));
        }
        else
        {
            TERM_IO_PutString(&string[i], TERM_IO_PRT_NO);
            TERM_IO_PutString(" is not hex", TERM_IO_PRT_LF);
            value = 0UL;
            break;
        }
    }
    return value;
}

uint8_t CONV_IO_hexStringToStream(uint8_t* string, uint8_t* stream, uint16_t size)
{
    uint16_t i, j;
    for(i = 0U, j = 0U; (string[i] != '\0') && (j < size); i++, j = (i >> 1U))
    {
        if((i & 0x1U) == 0x0U)  // even
        {
            stream[j] = 0x0U;
        }
        else                    // odd
        {
            stream[j] = stream[j] << 4U;
        }
        if      (('A' <= string[i]) && (string[i] <= 'F'))
        {
            stream[j] |= (0xAU + (string[i] - 'A'));
        }
        else if (('a' <= string[i]) && (string[i] <= 'f'))
        {
            stream[j] |= (0xAU + (string[i] - 'a'));
        }
        else if (('0' <= string[i]) && (string[i] <= '9'))
        {
            stream[j] |= (0x0U + (string[i] - '0'));
        }
        else
        {
            TERM_IO_PutString(&string[i], TERM_IO_PRT_NO);
            TERM_IO_PutString(" is not hex", TERM_IO_PRT_LF);
            return 1U;
        }
    }

    return 0U;
}
