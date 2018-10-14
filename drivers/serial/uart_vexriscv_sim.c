/*
 * Copyright (c) 2018 Antmicro <www.antmicro.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <arch/cpu.h>
#include <uart.h>
#include <board.h>



static unsigned char uart_vexriscv_sim_poll_out(struct device *dev,
				       unsigned char c)
{
	volatile int *uart = (int*)0xF0010000;
    volatile int i = 0;
    i++;
    uart[0] = c;
	return c;
}

static int uart_vexriscv_sim_poll_in(struct device *dev, unsigned char *c)
{
	return -1;
}

static int uart_vexriscv_sim_init(struct device *dev)
{
	/* Nothing to do */

	return 0;
}


static const struct uart_driver_api uart_vexriscv_sim_driver_api = {
	.poll_in = uart_vexriscv_sim_poll_in,
	.poll_out = uart_vexriscv_sim_poll_out,
	.err_check = NULL,
};



DEVICE_AND_API_INIT(uart_vexriscv_sim_0, "uart0",
		    uart_vexriscv_sim_init, 0xF0010000,
		    NULL,
		    PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
		    (void *)&uart_vexriscv_sim_driver_api);


