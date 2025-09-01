#ifndef MENU_IO_H
#define MENU_IO_H

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

uint32_t CONV_IO_hexStringToU32(uint8_t* string);
uint8_t CONV_IO_hexStringToStream(uint8_t* string, uint8_t* stream, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif /* MENU_IO_H */
