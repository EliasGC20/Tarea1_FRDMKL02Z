// Realizar un proyecto que utilice los leds RGB del microcontrolador FRDM-KL02Z realizado de la siguiente manera:
// V ON verde - v OFF verde
// R ON rojo - r OFF rojo
// A ON azul - a OFF azul
 
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL02Z4.h"
#include "fsl_debug_console.h"


//Declaracion de las MACROS

status_t uart0Inicializar(uint32_t);
uint8_t uart0NuevosDatosEnBuffer(void);
status_t uart0LeerByteDesdeBufferCircular(uint8_t *);


int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    (void)uart0Inicializar(115200);

        while(1) {
        	status_t status;
        	uint8_t nuevo_byte;

        	if(uart0NuevosDatosEnBuffer()>0){
        		status=uart0LeerByteDesdeBufferCircular(&nuevo_byte);
        		if(status==kStatus_Success){
        			printf("Dato:%c\r\n",nuevo_byte);
			switch (nuevo_byte) {

				case 'R': // Led rojo ON, led verde OFF Y led Azu OFF.
					GPIO_PortClear(GPIOB, 1u << 6U);
					GPIO_PortSet(GPIOB, 1u << 7U);
					GPIO_PortSet(GPIOB, 1u << 10U);

					break;
				case 'r': //Led rojo OFF.
					GPIO_PortSet(GPIOB, 1u << 6U);
					break;

				case 'V': // Led verde ON, led azul OFF y led rojo OFF.
					GPIO_PortClear(GPIOB, 1u << 7U);
					GPIO_PortSet(GPIOB, 1u << 6U);
					GPIO_PortSet(GPIOB, 1u << 10U);
					break;
				case 'v': //Led verde OFF
					GPIO_PortSet(GPIOB, 1u << 7U);
					break;

				case 'A': // Led azul ON, led verde OFF Y led rojo OFF.
					GPIO_PortClear(GPIOB, 1u << 10U);
					GPIO_PortSet(GPIOB, 1u << 6U);
					GPIO_PortSet(GPIOB, 1u << 7U);
					break;
				case 'a': // Led azul ON,
					GPIO_PortSet(GPIOB, 1u << 10U);
					break;
				//default: ;
			}


        		}
			else{
        			printf("error\r\n");
        		}
        	}
        	}


    return 0 ;
}

