#if defined(__HIWARE__)
#include "hiware_c99_stdint.h"
#elif defined(__COMPILER_FCC911__)
#include "fcc911_c99_stdint.h"
#else
//defined(__GNUC__) || defined(__TASKING__)
#include <stdint.h>
#endif
