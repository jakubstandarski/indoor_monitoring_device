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

#include "system_clock.h"
#include "debug.h"

#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_utils.h"



/*****************************************************************************/
/* EXTERNAL VARIABLES DECLARATIONS */
/*****************************************************************************/

extern uint32_t SystemCoreClock;



/*****************************************************************************/
/* PUBLIC FUNCTIONS DEFINITIONS */
/*****************************************************************************/

void system_clock_init(void)
{
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);
    while (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_5) {
        ;
    }

    LL_RCC_HSE_Enable();
    while (LL_RCC_HSE_IsReady() != 1) {
        ;
    }

    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_8, 336,
        LL_RCC_PLLP_DIV_2);
    LL_RCC_PLL_Enable();
    while (LL_RCC_PLL_IsReady() != 1) {
        ;
    }

    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);

    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {
        ;
    }

    LL_SetSystemCoreClock(168000000);
}



void system_clock_print_frequencies(void)
{
    LL_RCC_ClocksTypeDef system_clocks_frequencies = {0};
    LL_RCC_GetSystemClocksFreq(&system_clocks_frequencies);

    debug_printf("System clock frequency: %u\n",
        system_clocks_frequencies.SYSCLK_Frequency);
    debug_printf("AHB1 (HCLK) frequency: %u\n",
        system_clocks_frequencies.HCLK_Frequency);
    debug_printf("APB1 frequency: %u\n",
        system_clocks_frequencies.PCLK1_Frequency);
    debug_printf("APB2 frequency: %u\n",
        system_clocks_frequencies.PCLK2_Frequency);
}

