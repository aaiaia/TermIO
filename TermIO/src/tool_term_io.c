#include "tool_term_io.h"

#include "tool_comm_io.h"

int TERM_IO_Init(void)
{
    INIT_COMM_IO();
    return 0;
}

int TERM_IO_DeInit(void)
{
    DEINIT_COMM_IO();
    return 0;
}

size_t TERM_IO_PutString(const char* buffer, const char lf)
{
    size_t i = 0U;

    while(buffer[i] != ASCII_CHAR_NUL)
    {
        (void)PUT_CHAR(buffer[i]);
        i++;
    }
    if(lf != TERM_IO_MODE_NONE)
    {
        (void)PUT_CHAR(ASCII_CHAR_LF);
    }

    return i;
}

size_t TERM_IO_GetStringMode(char* buffer, const size_t bufsize, const uint8_t mode)
{
#define __STRING__(CHAR)    ((' ' <= CHAR) && (CHAR <= '~')) // ' '(0x20): space, '~'(0x7E)
#define __UPPER__(CHAR)     (('A' <= CHAR) && (CHAR <= 'F'))
#define __LOWER__(CHAR)     (('a' <= CHAR) && (CHAR <= 'f'))
#define __NUMS__(CHAR)      (('0' <= CHAR) && (CHAR <= '9'))
    const size_t strMax = bufsize - 1U;
    size_t getLen = 0U;
    uint8_t data8 = 0U;
    uint8_t ovf = 0U;
    uint8_t valid = 0U;

    if((0U < bufsize) && (mode < TERM_IO_STRING_LAST))
    {
        while(data8 != CTRL_KEY_ESC)
        {
            data8 = GET_CHAR();

            /* Special Key */
            if(data8 == CTRL_KEY_DELETE)
            {
                if(getLen != 0U)
                {
                    getLen--;

                    DEL_CHAR();
                }
            }
            else if(data8 == CTRL_KEY_ENTER)
            {
                buffer[getLen] = ASCII_CHAR_NUL;

                (void)ECHO_CHAR(data8);
                break;
            }
            else
            {
                /* Not special key */
                if(getLen <= strMax)
                {
                    if(mode == TERM_IO_STRING_NORM)
                    {
                        valid = (__STRING__(data8));
                    }
                    else if(mode == TERM_IO_STRING_HEX)
                    {
                        valid = (__UPPER__(data8) || __LOWER__(data8) || __NUMS__(data8));
                    }
                    else
                    {
                        // INVALID CASE
                    }

                    if(valid)
                    {
                        if(getLen < strMax)
                        {
                            buffer[getLen] = data8;
                            getLen++;

                            (void)ECHO_CHAR(data8);
                        }
                    }
                }
                else
                {
                    /* Buffer is full */
#ifndef ENABLE_TERM_IO_ECHO
                    ovf = 1U;
                    getLen = bufsize - 1U;
                    buffer[bufsize - 1U] = ASCII_CHAR_NUL;

                    PUT_CHAR(ASCII_CHAR_LF);
                    break;
#endif /* ENABLE_TERM_IO_ECHO */
                }
            }
        }

        /* cancel */
        if(data8 == CTRL_KEY_ESC)
        {
            buffer[0] = ASCII_CHAR_NUL;
            getLen = 0U;
            (void)TERM_IO_PutString("(escape)", TERM_IO_MODE_NONE);
            (void)ESC_CHAR();
        }

#ifndef ENABLE_TERM_IO_ECHO
        /* Overflow Handling */
        if(ovf != 0U)
        {
            (void)TERM_IO_PutString("(ovf|press enter)", TERM_IO_MODE_NONE);

            // ignoring uart receive data
            while(data8 != CTRL_KEY_ENTER)
            {
                data8 = GET_CHAR();
            }
        }
#endif /* ENABLE_TERM_IO_ECHO */
    }

    return getLen;
#undef __STRING__
#undef __UPPER__
#undef __LOWER__
#undef __NUMS__
}

