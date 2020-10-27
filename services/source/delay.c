/*
 * Author: Jakub Standarski
 * Email: jstand.jakub.standarski@gmail.com
 *
 * Date: 26.10.2020
 *
 */

/*****************************************************************************/
/* HEADERS */
/*****************************************************************************/

#include "delay.h"

#include "stm32f4xx_ll_utils.h"



/*****************************************************************************/
/* PUBLIC FUNCTIONS DEFINITIONS */
/*****************************************************************************/

void delay_timer_init(void)
{
    LL_Init1msTick(SystemCoreClock);
}



void delay_ms(uint32_t milliseconds)
{
    LL_mDelay(milliseconds);
}

