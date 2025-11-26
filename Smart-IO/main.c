
#include "cy8c6247bzi_d54.h"
#include "cy_smartio.h"
#include "cyhal_system.h"
#if defined (CY_USING_HAL)
#include "cyhal.h"
#endif
#include "cybsp.h"
#include "cy_retarget_io.h"

// LDFLAGS = -Wl,--no-warn-rwx-segments in Makefile to turn off register warning

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
		if(GPIO_PRT9->IN & 0x08) // Check if Pin 9_3 is set (output from smart-io)
		{
			GPIO_PRT1->OUT = GPIO_PRT1->OUT | 0x20; // Set pin 1_5 (actually turns off since it's active low)
			printf("OFF\r\n");
		}
		else 
		{
			GPIO_PRT1->OUT = GPIO_PRT1->OUT & ~0x20; // Clear pin 1_5 (actually turns on since it's active low)
			printf("ON\r\n");
		}
		cyhal_system_delay_ms(1000);
    }
}
