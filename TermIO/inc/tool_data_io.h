#ifndef TOOL_DATA_IO_H
#define TOOL_DATA_IO_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__GNUC__)
#include <stdint.h>
#elif defined(__HIWARE__)
#include "hiware_c99_stdint.h"
#else
#error "Not Support stdint"
#endif
#include <stddef.h> // size_t, NULL

size_t DATA_IO_PutData(const uint8_t* buffer, const size_t size);
size_t DATA_IO_GetData(uint8_t* buffer, const size_t size);

#ifdef __cplusplus
}
#endif

#endif /* TOOL_DATA_IO_H */
