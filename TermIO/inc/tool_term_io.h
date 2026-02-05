#ifndef TOOL_TERM_IO_H
#define TOOL_TERM_IO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "termio_stdint.h" //alternates to stdint.h
#include <stddef.h> // size_t, NULL

#define TERM_IO_MODE_NONE   0   // Attach Nothing
#define TERM_IO_MODE_UNIX   1   // Attach LF
#define TERM_IO_MODE_DOS    2   // Attach CR LF

#define ENABLE_TERM_IO_ECHO
#define DEFAULT_TERM_MODE   TERM_IO_MODE_UNIX

#define TERM_IO_STRING_NORM 0U
#define TERM_IO_STRING_HEX  1U
#define TERM_IO_STRING_LAST (TERM_IO_STRING_HEX + 1U)

#define TERM_IO_PRT_NO  0
#define TERM_IO_PRT_LF  1

extern int TERM_IO_Init(void);
extern int TERM_IO_DeInit(void);

size_t TERM_IO_PutString(const char* buffer, const char lf);
size_t TERM_IO_GetStringMode(char* buffer, const size_t bufsize, const uint8_t mode);
#if defined(__GNUC__)
static inline size_t TERM_IO_GetString(char* buffer, const size_t bufsize)
{
    return TERM_IO_GetStringMode(buffer, bufsize, TERM_IO_STRING_NORM);
}
static inline size_t TERM_IO_GetHexString(char* buffer, const size_t bufsize)
{
    return TERM_IO_GetStringMode(buffer, bufsize, TERM_IO_STRING_HEX);
}
#else
#define TERM_IO_GetString(buffer, bufsize) TERM_IO_GetStringMode(buffer, bufsize, TERM_IO_STRING_NORM)
#define TERM_IO_GetHexString(buffer, bufsize) TERM_IO_GetStringMode(buffer, bufsize, TERM_IO_STRING_HEX)
#endif

#ifdef __cplusplus
}
#endif

#endif /* TOOL_TERM_IO_H */
