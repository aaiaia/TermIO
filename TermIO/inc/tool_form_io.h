#ifndef TOOL_FORM_IO_H
#define TOOL_FORM_IO_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__GNUC__)
#include <stdint.h>
#elif defined(__HIWARE__)
#include "hiware_c99_stdint.h"
#elif defined(__COMPILER_FCC911__)
#include "fcc911_c99_stdint.h"
#else
#error "Not Support stdint"
#endif
#include <stddef.h> // size_t, NULL

#define FORM_IO_PRE_NO  0
#define FORM_IO_PRE_HEX 1

void FORM_IO_printU32ToHex(const uint32_t ui32, const uint8_t bits, const char prefix, const char lf);
void FORM_IO_printU32ToDec(const uint32_t ui32, const char lf);
void FORM_IO_printMemory(const void* addr, const uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* TOOL_FORM_IO_H */
