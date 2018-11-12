/*
 * Copyright (c) 2017 Jean-Paul Etienne <fractalclone@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <arch/cpu.h>
#include <device.h>
#include <system_timer.h>
#include <board.h>



static volatile u32_t *vexriscv_area_timer_counter = (u32_t *)CONFIG_VEXRISCV_TIMER_COUNTER_BASE;
static volatile u32_t *vexriscv_area_timer_cmp = (u32_t *)CONFIG_VEXRISCV_TIMER_CMP_BASE;
static u32_t vexriscv_area_timer_accumulator = 0;

static ALWAYS_INLINE void vexriscv_area_timer_rearm(void)
{
    *vexriscv_area_timer_counter = 0;

	irq_enable(RISCV_MACHINE_TIMER_IRQ);
}

static void vexriscv_contest_area_timer_irq_handler(void *unused)
{
	ARG_UNUSED(unused);
#ifdef CONFIG_EXECUTION_BENCHMARKING
	extern void read_timer_start_of_tick_handler(void);
	read_timer_start_of_tick_handler();
#endif
    vexriscv_area_timer_accumulator += sys_clock_hw_cycles_per_tick;

	_sys_clock_tick_announce();

	vexriscv_area_timer_rearm();

#ifdef CONFIG_EXECUTION_BENCHMARKING
	extern void read_timer_end_of_tick_handler(void);
	read_timer_end_of_tick_handler();
#endif
}

#ifdef CONFIG_TICKLESS_IDLE
#error "Tickless idle not yet implemented for riscv-machine timer"
#endif

int _sys_clock_driver_init(struct device *device)
{
	ARG_UNUSED(device);

	IRQ_CONNECT(RISCV_MACHINE_TIMER_IRQ, 0,
		    vexriscv_contest_area_timer_irq_handler, NULL, 0);

	*vexriscv_area_timer_cmp = sys_clock_hw_cycles_per_tick-1;
	vexriscv_area_timer_rearm();

	return 0;
}


u32_t _timer_cycle_get_32(void)
{
	return  vexriscv_area_timer_accumulator + *vexriscv_area_timer_counter;
}
