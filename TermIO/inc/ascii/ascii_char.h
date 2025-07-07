#ifndef ASCII_CHAR_H
#define ASCII_CHAR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Reference: https://en.wikipedia.org/wiki/ASCII */
#define ASCII_CHAR_LF   '\n'    // linefeed
#define ASCII_CHAR_NUL  '\0'    // null
#define ASCII_CHAR_BS   0x08    // back space
#define ASCII_CHAR_CAN  0x18    // cancel
#define ASCII_CHAR_ESC  0x1B    // escape
#define ASCII_CHAR_SP   0x20    // space
#define ASCII_CHAR_DEL  0x7F    // delete

#ifdef __cplusplus
}
#endif

#endif /* ASCII_CHAR_H */
