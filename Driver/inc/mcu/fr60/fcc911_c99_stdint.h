/**
 * @file c99_stdint.h
 *
 * @brief Paritally support exact-width integer type for S12XS on HC12 compiler.
 *
 ********************************************************************************
* \copyright
* Copyright 2025. Autocrypt, Inc. All Rights Reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef C99_STDINT_H
#define C99_STDINT_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __COMPILER_FCC911__  // __COMPILER_FCC911__: Compiler Vendor Identification Defines
#include <stdint.h>
#else               // ANSI-C/cC++ Compiler for HC12 V-5.0.46 Build 15249, Sep  7 2015
                    // Assembler for HC12 V-5.0.32 Build 15249, Sep  7 2015
/*
 * Reference
 * 1. [WEBSITE] https://en.wikibooks.org/wiki/C_Programming/stdint.h
 * 1.1.         stdint.h is a header file in the C standard library introduced in 
 *              the C99 standard library section 7.18 to allow programmers to 
 *              write more portable code by providing a set of typedefs that 
 *              specify exact-width integer types, together with the defined 
 *              minimum and maximum allowable values for each type, using 
 *              macros.
 * 2. [FILE]    /usr/include/stdint.h
 */
/* Minimum of signed integral types.  */
# define INT8_MIN       (-128)
# define INT16_MIN      (-32767-1)
# define INT32_MIN      (-2147483647-1)
#if 0   /* NOT_SUPPORTED_64BITS */
# define INT64_MIN      (-__INT64_C(9223372036854775807)-1)
#endif  /* NOT_SUPPORTED_64BITS */
/* Maximum of signed integral types.  */
# define INT8_MAX       (127)
# define INT16_MAX      (32767)
# define INT32_MAX      (2147483647)
#if 0   /* NOT_SUPPORTED_64BITS */
# define INT64_MAX      (__INT64_C(9223372036854775807))
#endif  /* NOT_SUPPORTED_64BITS */

/* Maximum of unsigned integral types.  */
# define UINT8_MAX      (255)
# define UINT16_MAX     (65535)
# define UINT32_MAX     (4294967295U)
#if 0   /* NOT_SUPPORTED_64BITS */
# define UINT64_MAX     (__UINT64_C(18446744073709551615))
#endif  /* NOT_SUPPORTED_64BITS */

/*
 * References
 * 1. [Doc]     SOFTUNE C/C++ Compiler Manual for V6, CM81-00206-7E
 * 1.1.         9.1 Compiler-dependent C Language Specification Differentials, pp.151
 *              Table 9.1-1 Compiler-dependent Language Specification Differentials
 * 2. [FILE]    FR Family C++ Library V65L06, limits.h
 *    [PATH]    c:\Softune6\Lib\911\include\limits.h
 */
typedef  unsigned char      uint8_t;
typedef    signed char      int8_t;

typedef  unsigned short     uint16_t;
typedef    signed short     int16_t;

typedef  unsigned int       uint32_t;
typedef    signed int       int32_t;

#endif /* __COMPILER_FCC911__ */

#ifdef __cplusplus
}
#endif

#endif /* C99_STDINT_H */
