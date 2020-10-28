/*
 * Author: Jakub Standarski
 * Email: jstand.jakub.standarski@gmail.com
 *
 * Date: 28.10.2020
 *
 */

#ifndef CIRCULAR_BUFFER_H
    #define CIRCULAR_BUFFER_H

/*****************************************************************************/
/* PUBLIC ENUMS */
/*****************************************************************************/

typedef enum circular_buffer_status {
    CIRCULAR_BUFFER_STATUS_OK,
    CIRCULAR_BUFFER_STATUS_ERROR,
    CIRCULAR_BUFFER_STATUS_EMPTY,
    CIRCULAR_BUFFER_STATUS_NOT_EMPTY,
    CIRCULAR_BUFFER_STATUS_FULL,
    CIRCULAR_BUFFER_STATUS_NOT_FULL
}circular_buffer_status_t;




#endif /* CIRCULAR_BUFFER_H */

