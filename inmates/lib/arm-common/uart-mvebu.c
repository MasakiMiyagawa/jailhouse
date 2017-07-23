/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Copyright (c) Siemens AG, 2017
 *
 * Authors:
 *  Jan Kiszka <jan.kiszka@siemens.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */

#include <inmate.h>
#include <uart.h>

#define UART_TSH		0x4
#define UART_STAT		0xc
#define  UART_STAT_TX_FULL	(1 << 11)

static void uart_init(struct uart_chip *chip)
{
}

static bool uart_is_busy(struct uart_chip *chip)
{
	return !!(mmio_read32(chip->base + UART_STAT) & UART_STAT_TX_FULL);
}

static void uart_write(struct uart_chip *chip, char c)
{
	mmio_write32(chip->base + UART_TSH, c);
}

struct uart_chip uart_mvebu_ops = {
	.init = uart_init,
	.is_busy = uart_is_busy,
	.write = uart_write,
};
