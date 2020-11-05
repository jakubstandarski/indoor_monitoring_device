/*
 * Author: Jakub Standarski
 * Email: jstand.jakub.standarski@gmail.com
 *
 * Date: 05.11.2020
 *
 */

/*****************************************************************************/
/* HEADERS */
/*****************************************************************************/

#include "pwr.h"

#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_pwr.h"



/*****************************************************************************/
/* PRIVATE FUNCTIONS PROTOTYPES */
/*****************************************************************************/

static void pwr_clock_init(void);



/*****************************************************************************/
/* PRIVATE FUNCTIONS DEFINITIONS */
/*****************************************************************************/

static void pwr_clock_init(void)
{
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
}

