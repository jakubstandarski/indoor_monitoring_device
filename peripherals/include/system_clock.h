/*
 * Author: Jakub Standarski
 * Email: jstand.jakub.standarski@gmail.com
 *
 * Date: 26.10.2020
 *
 */

#ifndef SYSTEM_CLOCK_H
    #define SYSTEM_CLOCK_H

/*****************************************************************************/
/* PUBLIC FUNCTIONS PROTOTYPES */
/*****************************************************************************/

/**
 * @brief   Set clock source (i.e. HSI or HSE), system clock source and its
 *          speed if PLL is used (HCLK), AHB1 prescaler, APB1 prescaler,
 *          APB2 prescaler and Flash latency.
 *
 * @param   None.
 *
 * @retval  None.
 */
void system_clock_init(void);



#endif /*SYSTEM_CLOCK_H */

