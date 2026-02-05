#ifndef MENU_IO_H
#define MENU_IO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "termio_stdint.h" //alternates to stdint.h
#include <stddef.h> // size_t, NULL

uint32_t CONV_IO_hexStringToU32(uint8_t* string);
uint8_t CONV_IO_hexStringToStream(uint8_t* string, uint8_t* stream, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif /* MENU_IO_H */
