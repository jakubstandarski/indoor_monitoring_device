/*
 * Author: Jakub Standarski
 * Email: jstand.jakub.standarski@gmail.com
 *
 * Date: 26.10.2020
 *
 */

#ifndef DELAY_H
    #define DELAY_H

/*****************************************************************************/
/* HEADERS */
/*****************************************************************************/

#include <stdint.h>



/*****************************************************************************/
/* PUBLIC FUNCTIONS PROTOTYPES */
/*****************************************************************************/

/**
 * @brief   Initialize timer responsible of delay functions.
 *
 * @param   None.
 *
 * @retval  None.
 */
void delay_timer_init(void);



/**
 * @brief   Wait given amount of milliseconds (blocking function).
 *
 * @param   milliseconds - delay time given in milliseconds.
 *
 * @retval  None.
 */
void delay_ms(uint32_t milliseconds);



#endif /* DELAY_H */

