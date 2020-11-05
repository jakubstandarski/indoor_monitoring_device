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
static void pwr_peripheral_init(void);



/*****************************************************************************/
/* PRIVATE FUNCTIONS DEFINITIONS */
/*****************************************************************************/

static void pwr_clock_init(void)
{
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
}



static void pwr_peripheral_init(void)
{
    LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
    while (LL_PWR_GetRegulVoltageScaling() != LL_PWR_REGU_VOLTAGE_SCALE1) {
        ;
    }

    LL_PWR_EnableBkUpAccess();
    while (LL_PWR_IsEnabledBkUpAccess() != 1) {
        ;
    }
}

