/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    FDRMKL02Z_LED_RGB.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL02Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */


//MACROS

status_t uart0Inicializar(uint32_t);
uint8_t uart0NuevosDatosEnBuffer(void);
status_t uart0LeerByteDesdeBufferCircular(uint8_t *);
/*
 * @brief   Application entry point.
 */
//void delay(void)
//{
//    volatile uint32_t i = 0;
//    for (i = 0; i < 0xFFFFFFFF; ++i)
//    {
//        __asm("NOP"); /* delay */
//    }
//}

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

