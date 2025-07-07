#include "tool_data_io.h"

#include "tool_comm_io.h"

size_t DATA_IO_PutData(const uint8_t* buffer, const size_t size)
{
    size_t i;

    for(i = 0U; i < size; i++)
    {
        (void)PUT_CHAR(buffer[i]);
        i++;
    }

    return i;
}

size_t DATA_IO_GetData(uint8_t* buffer, const size_t size)
{
    size_t i;

    for(i = 0U; i < size; i++)
    {
        (void)PUT_CHAR(buffer[i]);
    }

    return i;
}
