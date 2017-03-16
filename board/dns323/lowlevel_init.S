/*
 * Setup the RAM and multiplexing pins
 *
 * Copyright (C) 2008 Byron Bradley <byron.bbradley@gmail.com>
 *
 * Modified for DNS-323 from Kuro Pro
 * Copyright (C) 2008 Veli-Matti Valtonen <maligor@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */


#include <config.h>
#include <version.h>

#define INTREG_BASE			0xd0000000
#define ORION5X_REGS_PHYS_BASE		0xf1000000

#define ORION5X_REGISTER(x)		(ORION5X_REGS_PHYS_BASE | x)
#define ORION5X_OFFSET_REG		(INTREG_BASE | 0x20080)

_TEXT_BASE:
	.word	TEXT_BASE

.globl lowlevel_init
lowlevel_init:

	/* Linux expects the internal registers to be at 0xf1000000 */
	/* Window 6 is enabled by default for 128MB at 0xf0000000 */
	ldr r1, =ORION5X_OFFSET_REG
	ldr r3, =ORION5X_REGS_PHYS_BASE
	str r3, [r1]
	
	/* MMU, LE, high vectors, PCIE is root */
	ldr r1, =ORION5X_REGISTER(0x20100)
	ldr r3, =0x2	/* 0x2 would be PCIe & Vector start 0xfff00000 */
	str r3, [r1]

	/* Setup the Multiplexing pins */
	ldr r1, =ORION5X_REGISTER(0x10000)
	ldr r3, =0x00000000
	str r3, [r1]
	ldr r3, =0x00000000
	str r3, [r1, #0x4]
	ldr r3, =0x00001111
	str r3, [r1, #0x50]

	/* Initialise GPIO pins */
	ldr r3, =0x06e1
	str r3, [r1, #0x104]

	ldr r3, =0x10			
	str r3, [r1, #0x108]	/* Enable power led blink */
	ldr r3, =0x6
	str r3, [r1, #0x100]	/* Disable Orange leds */

	/* DDR1 Setup */
	ldr r1, =ORION5X_REGISTER(0x1000)
	ldr r3, =0x03148400
	str r3, [r1, #0x400]	/* SDRAM Configuration Register, DDR1 */
	ldr r3, =0x4041000	
	str r3, [r1, #0x404]	/* SDRAM Control Register */
	ldr r3, =0x10
	str r3, [r1, #0x410]	/* Adress Control Register */

	/* These leave auto pad drive enabled so it shouldn't be a problem, they set it to the default values 
	 * However it does set it to the autodeteced values on my unit, the marvell code copies the autodetected 
	 * values from autodetected values */
	ldr r3, =0x8001138F
	str r3, [r1, #0x4c0]	/* Address/Control Pads Calibration-Enable Write */
	ldr r3, =0x8001138F
	str r3, [r1, #0x4c4]	/* Data Pads Calibration - Enable Write */
	ldr r3, =0x0001138F
	str r3, [r1, #0x4c0]	/* SR bits[13:12] = 0x1 */
	ldr r3, =0x0001138F
	str r3, [r1, #0x4c4]	/* SR bits[13:12] = 0x1 */
	
	ldr r3, =0x03ff0001
	str r3, [r1, #0x504]	/* SDRAM CS[0]n Size - 64MB, Enable */
	ldr r3, =0x0fff0000
	str r3, [r1, #0x50c]	/* SDRAM CS[1]n Size - Disable */
	ldr r3, =0x0fff0000
	str r3, [r1, #0x514]	/* SDRAM CS[2]n Size - Disable */
	ldr r3, =0x0fff0000
	str r3, [r1, #0x51c]	/* SDRAM CS[3]n Size - Disable */
	ldr r3, =0x00000000
	str r3, [r1, #0x420]	/* Extended DDR SDRAM Mode Register, All bits set to 0 for DDR1 */
	ldr r3, =0x00000000
	str r3, [r1, #0x414]	/* DDR SDRAM Open Pages Control */
	ldr r3, =0x00000062
	str r3, [r1, #0x41c]	/* DDR SDRAM Mode - CL 2.5 */

	ldr r3, =0x11602220    
	str r3, [r1, #0x408]	/* DDR SDRAM Timing (Low) Register */
	ldr r3, =0x0000040c    
	str r3, [r1, #0x40c]	/* DDR SDRAM Timing (High) Register */

	ldr     r10, =0x30
1:
	subs    r10, r10, #1
	bne     1b

	ldr r3, =0x00000001
	str r3, [r1, #0x480]	/* DDR SDRAM Initialization Control - Enable */

	ldr     r10, =0x30
1:
	subs    r10, r10, #1
	bne     1b

#if 0 /* Don't think we should configure PCI here, just cpu and dram */
	/* Configure PCI Express */
	ldr r1, =ORION5X_REGISTER(0x41000)
	ldr r3, =0x03ff0001
	str r3, [r1, #0x804]	/* BAR1, 64MB */
	ldr r3, =0x0fff0000
	str r3, [r1, #0x808]	/* BAR2, Disable */

	ldr r3, =0x03ff0e01
	str r3, [r1, #0x820]	/* PCI Express Window0 Control - Enable, CS0, Bar1, 64MB */
	ldr r3, =0x00000000
	str r3, [r1, #0x824]	/* PCI Express Window0 Base - 0x0, upper half used only */

	/* All the other windows are disabled, DevCS stuff, mapped to BAR2 */
	ldr r3, =0x001f1e12
	str r3, [r1, #0x830]
	ldr r3, =0xfa000000
	str r3, [r1, #0x834]
	ldr r3, =0x007f1d12
	str r3, [r1, #0x840]
	ldr r3, =0xff800000
	str r3, [r1, #0x844]
	ldr r3, =0x000f1b12
	str r3, [r1, #0x850]
	ldr r3, =0xfa800000
	str r3, [r1, #0x854]
	ldr r3, =0x007f0f12
	str r3, [r1, #0x860]
	ldr r3, =0xff800000
	str r3, [r1, #0x864]

	ldr     r10, =0x30
1:
	subs    r10, r10, #1
	bne     1b

	/* PCI Setup */
	ldr r1, =ORION5X_REGISTER(0x31000)
	ldr r3, =0x80000030
	str r3, [r1, #0xd00]	/* PCI Arbiter - Enable */
	ldr r1, =ORION5X_REGISTER(0x30000)
	ldr r3, =0x03fff000
	str r3, [r1, #0xc08]	/* CSn[0] BAR Size - 64MB */
	ldr r3, =0x001ff000
	str r3, [r1, #0xc10]	/* DevCSn[x] start, BAR Sizes */
	ldr r3, =0x007ff000
	str r3, [r1, #0xd10]
	ldr r3, =0x000ff000
	str r3, [r1, #0xd18]
	ldr r3, =0x007ff000
	str r3, [r1, #0xd14]	/* DevCSn[x] end */
	ldr r3, =0xfffffc8e
	str r3, [r1, #0xc3c]	/* Base Address Registers Enable */

	ldr     r10, =0x30
1:
	subs    r10, r10, #1
	bne     1b
#endif

	mov	pc, lr
