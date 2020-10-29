/*
 * Author: Jakub Standarski
 * Email: jstand.jakub.standarski@gmail.com
 *
 * Date: 29.10.2020
 *
 */

/*****************************************************************************/
/* HEADERS */
/*****************************************************************************/

#include "debug.h"
#include "circular_buffer.h"

#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_usart.h"

#include "core_cm4.h"
#include "stm32f407xx.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>



/*****************************************************************************/
/* PRIVATE DEFINES */
/*****************************************************************************/

#define DEBUG_UART_GPIO_PORT        GPIOB
#define DEBUG_UART_GPIO_PORT_CLOCK  LL_AHB1_GRP1_PERIPH_GPIOB
#define DEBUG_UART_GPIO_PIN_TX      LL_GPIO_PIN_6

#define DEBUG_UART_PERIPHERAL       USART1
#define DEBUG_UART_PERIPHERAL_CLOCK LL_APB2_GRP1_PERIPH_USART1

#define DEBUG_MESSAGE_SIZE_MAX      CIRCULAR_BUFFER_SIZE



/*****************************************************************************/
/* PRIVATE OBJECTS DEFINITIONS */
/*****************************************************************************/

static circular_buffer_t debug_buffer;



/*****************************************************************************/
/* PRIVATE FUNCTIONS PROTOTYPES */
/*****************************************************************************/

static void debug_uart_gpio_init(void);
static void debug_uart_peripheral_init(void);



/*****************************************************************************/
/* PUBLIC FUNCTIONS DEFINITIONS */
/*****************************************************************************/

void debug_init(void)
{
    debug_uart_gpio_init();
    debug_uart_peripheral_init();
    circular_buffer_init(&debug_buffer);
}



void debug_printf(const char *text, ...)
{
    char formatted_message[DEBUG_MESSAGE_SIZE_MAX];
    va_list arguments;
    va_start(arguments, text);
    vsprintf(formatted_message, text, arguments);
    va_end(arguments);

    uint32_t formatted_message_length = strlen(formatted_message);
    for (uint32_t index = 0; index < formatted_message_length; index++) {
        while (circular_buffer_is_full(&debug_buffer) ==
            CIRCULAR_BUFFER_STATUS_FULL) {
                ;
        }
        circular_buffer_put_item(&debug_buffer,
            (char)formatted_message[index]);
    }

    LL_USART_Enable(DEBUG_UART_PERIPHERAL);
    LL_USART_EnableIT_TXE(DEBUG_UART_PERIPHERAL);
}



/*****************************************************************************/
/* PRIVATE FUNCTIONS DEFINITIONS */
/*****************************************************************************/

static void debug_uart_gpio_init(void)
{
    LL_AHB1_GRP1_EnableClock(DEBUG_UART_GPIO_PORT_CLOCK);

    LL_GPIO_InitTypeDef uart_gpio_settings = {
        .Pin = DEBUG_UART_GPIO_PIN_TX,
        .Mode = LL_GPIO_MODE_ALTERNATE,
        .Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH,
        .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
        .Pull = LL_GPIO_PULL_NO,
        .Alternate = LL_GPIO_AF_7
    };
    LL_GPIO_Init(DEBUG_UART_GPIO_PORT, &uart_gpio_settings);
}



static void debug_uart_peripheral_init(void)
{
    LL_APB2_GRP1_EnableClock(DEBUG_UART_PERIPHERAL_CLOCK);

    LL_USART_InitTypeDef uart_peripheral_settings = {
        .BaudRate = (uint32_t)115200,
        .DataWidth = LL_USART_DATAWIDTH_8B,
        .StopBits = LL_USART_STOPBITS_1,
        .Parity = LL_USART_PARITY_NONE,
        .TransferDirection = LL_USART_DIRECTION_TX,
        .HardwareFlowControl = LL_USART_HWCONTROL_NONE,
        .OverSampling = LL_USART_OVERSAMPLING_16
    };
    LL_USART_Init(DEBUG_UART_PERIPHERAL, &uart_peripheral_settings);

    LL_USART_DisableSCLKOutput(DEBUG_UART_PERIPHERAL);
}



/*****************************************************************************/
/* INTERRUPT HANDLERS DEFINITIONS */
/*****************************************************************************/

void USART1_IRQHandler(void)
{
    uint8_t data_byte = 0;
    if (LL_USART_IsActiveFlag_TXE(DEBUG_UART_PERIPHERAL) == 1) {
        circular_buffer_get_item(&debug_buffer, &data_byte);
        LL_USART_TransmitData8(DEBUG_UART_PERIPHERAL, data_byte);

        if (circular_buffer_is_empty(&debug_buffer) ==
            CIRCULAR_BUFFER_STATUS_EMPTY) {
                LL_USART_DisableIT_TXE(DEBUG_UART_PERIPHERAL);
        }
    }
}

