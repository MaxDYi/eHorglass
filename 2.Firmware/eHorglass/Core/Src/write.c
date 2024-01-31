#include <LowLevelIOInterface.h>
#include <stdint.h>
#include "main.h"
#include "usart.h"
#include "usbd_cdc_if.h"
#pragma module_name = "?__write"

#define DEBUG_UART huart1

/*
 * If the __write implementation uses internal buffering, uncomment
 * the following line to ensure that we are called with "buffer" as 0
 * (i.e. flush) when the application terminates.
 */

size_t __write(int handle, const unsigned char *buffer, size_t size)
{
    if (buffer == 0)

    {
        /*
         * This means that we should flush internal buffers.  Since we
         * don't we just return.  (Remember, "handle" == -1 means that all
         * handles should be flushed.)
         */

        return 0;
    }
    /* This template only writes to "standard out" and "standard err",
     * for all other file handles it returns failure. */

    if (handle != _LLIO_STDOUT && handle != _LLIO_STDERR)
    {
        return _LLIO_ERROR;
    }

    /* Sending in normal mode */
    if (HAL_UART_Transmit(&DEBUG_UART, (uint8_t *)buffer, size, 0xFFFF) == HAL_OK)
    {
        
        return size;
    }
    else
    {
        return _LLIO_ERROR;
    }
}