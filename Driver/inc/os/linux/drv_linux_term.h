#ifndef DRV_LINUX_TERM_H
#define DRV_LINUX_TERM_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __linux__
#include <stdio.h>

#include <termios.h>
#include <unistd.h>

extern void linuxTermInit(void);
extern void linuxTermRestore(void);

static inline void linuxTermDelChar(void) {
#define __ASCII_CHAR_BS     0x08    // back space
#define __ASCII_CHAR_SP     0x20    // space
    (void)putchar(__ASCII_CHAR_BS);
    fflush(stdout);
    (void)putchar(__ASCII_CHAR_SP);
    fflush(stdout);
    (void)putchar(__ASCII_CHAR_BS);
    fflush(stdout);
#undef __ASCII_CHAR_BS
#undef __ASCII_CHAR_SP
}
static inline int linuxTermEchoBack(int c) {
    int ret = putchar(c);
    fflush(stdout);
    return ret;
}

#endif /* __linux__ */

#ifdef __cplusplus
}
#endif

#endif /* DRV_LINUX_TERM_H */
