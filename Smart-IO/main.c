
#include "cy8c6247bzi_d54.h"
#include "cy_smartio.h"
#include "cyhal_system.h"
#if defined (CY_USING_HAL)
#include "cyhal.h"
#endif
#include "cybsp.h"
#include "cy_retarget_io.h"

int main(void)
{
    cybsp_init();
    __enable_irq();

	cy_en_smartio_status_t smartio_result;

	cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);

	smartio_result = Cy_SmartIO_Init(SMARTIO_PRT9, &ioss_0_port_9_smartio_0_config);
    if (smartio_result != CY_SMARTIO_SUCCESS)
    {
        CY_ASSERT(0);
    }
    Cy_SmartIO_Enable(SMARTIO_PRT9);

    for (;;)
    {
		if(GPIO_PRT9->IN & 0x08)
		{
			Cy_GPIO_Set(CYBSP_USER_LED_PORT, CYBSP_USER_LED_PIN);
			printf("ON\r\n");
		}
		else 
		{
			Cy_GPIO_Clr(CYBSP_USER_LED_PORT, CYBSP_USER_LED_PIN);
			printf("OFF\r\n");
		}
		cyhal_system_delay_ms(2000);
    }
}
