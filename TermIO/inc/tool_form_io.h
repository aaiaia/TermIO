#ifndef TOOL_FORM_IO_H
#define TOOL_FORM_IO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "termio_stdint.h" //alternates to stdint.h
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
