/*
 * Author: Jakub Standarski
 * Email: jstand.jakub.standarski@gmail.com
 *
 * Date: 28.10.2020
 *
 */

/*****************************************************************************/
/* HEADERS */
/*****************************************************************************/

#include "circular_buffer.h"

#include <stdint.h>



/*****************************************************************************/
/* PUBLIC FUNCTIONS DEFINITIONS */
/*****************************************************************************/

circular_buffer_status_t circular_buffer_init(
    circular_buffer_t *circular_buffer
)
{
    memset(circular_buffer->buffer, 0, CIRCULAR_BUFFER_SIZE);
    circular_buffer->head = 0;
    circular_buffer->tail = 0;
    circular_buffer->items_count = 0;

    return CIRCULAR_BUFFER_STATUS_OK;
}

