/*
 * (C) Copyright 2008 Byron Bradley <byron.bbradley@gmail.com>
 *
 * Modified for DNS-323 from Kuro Pro
 * (C) Copyright 2008 Veli-Matti Valtonen <maligor@gmail.com>
 *
 * Configuation settings for the DNS-323 board.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
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

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * High Level Configuration Options
 * (easy to change)
 */
#define CONFIG_ARM926EJS			1	/* This is a feroceon/arm926ejs CPU core */
#define	CONFIG_ORION5X				1	/* in a Marvell Orion 88F5181 SoC */
#define CONFIG_DNS323				1	/* on a DNS323 board */
#define CONFIG_FEROCEON				1
#define CONFIG_88F5182				1	

#undef CONFIG_USE_IRQ					/* we don't need IRQ/FIQ stuff	*/

#define CONFIG_CMDLINE_TAG	 		1	/* enable passing of ATAGs    	*/
#define CONFIG_SETUP_MEMORY_TAGS 		1
#define CONFIG_INITRD_TAG	 		1

#define CONFIG_SYS_BOOTMAPSZ			(8<<20)

/*
 * Command line configuration.
 */
#include <config_cmd_default.h>

#undef CONFIG_CMD_FPGA
#define CONFIG_CMD_NET
#undef CONFIG_CMD_NFS
#undef CONFIG_CMD_IDE
#undef CONFIG_CMD_SETGETDCR
#undef CONFIG_CMD_XIMG
#undef CONFIG_CMD_CACHE
#undef CONFIG_CMD_ELF
#define CONFIG_CMD_REGINFO
#define CONFIG_CMD_DIAG

#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2		"> "

//#define CONFIG_SKIP_LOWLEVEL_INIT
//#define CONFIG_SKIP_RELOCATE_UBOOT

//#define DEBUG
#define CONFIG_SYS_HZ				1000
#define CONFIG_SYS_TIMERBASE			0xf1020300

/*-----------------------------------------------------------------------
 * Board-specific values for Orion5x MPP low level init:
 */
#define ORION5X_MPP0_7				0x00000000
#define ORION5X_MPP8_15				0x00000000
#define ORION5X_MPP16_23			0x00000000

/*-----------------------------------------------------------------------
 * Board-specific values for Orion5x GPIO low level init:
 */
#define ORION5X_GPIO_OUT_ENABLE			0x00000126
#define ORION5X_GPIO_OUT_VALUE			0x00000000


/*-----------------------------------------------------------------------
 * Physical Memory Map
 */
#define CONFIG_NR_DRAM_BANKS			1	   /* we have 1 bank of DRAM */
#define CONFIG_SYS_FLASH_BASE			0xfff80000

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */

#define CONFIG_SYS_MAX_FLASH_BANKS		1	/* max number of memory banks */
#define CONFIG_SYS_MAX_FLASH_SECT		(135)	/* max number of sectors on one chip */

/* Not really sure where I should map this */
#define CONFIG_ENV_OFFSET 			0x4000
#define CONFIG_ENV_IS_IN_FLASH			1	/* use flash for environment vars */
#define CONFIG_ENV_SIZE				0x2000
#define CONFIG_ENV_SECT_SIZE			0x2000

#define CONFIG_SYS_FLASH_CFI			1       /* Flash memory is CFI compliant */
#define CONFIG_FLASH_CFI_DRIVER			1       /* Use drivers/cfi_flash.c */
//#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE 1   /* Use buffered writes (~10x faster) */
//#define CONFIG_SYS_FLASH_PROTECTION   1       /* Use hardware sector protection */
#define CONFIG_SYS_FLASH_CFI_WIDTH             FLASH_CFI_8BIT
#define CONFIG_SYS_FLASH_EMPTY_INFO
//#define CONFIG_FLASH_CFI_LEGACY
//#define CONFIG_SYS_FLASH_LEGACY_256Kx8 1

/*-----------------------------------------------------------------------
 * Network
 */
#ifdef CONFIG_CMD_NET
#define CONFIG_MVGBE				/* Enable Marvell GbE Driver */
#define CONFIG_MVGBE_PORTS	{1}		/* enable port 0 only */
#define CONFIG_SKIP_LOCAL_MAC_RANDOMIZATION	/* don't randomize MAC */
#define CONFIG_PHY_BASE_ADR	0x8
#define CONFIG_NETCONSOLE	/* include NetConsole support   */
#define CONFIG_NET_MULTI	/* specify more that one ports available */
#define CONFIG_RESET_PHY_R	/* use reset_phy() to init mv8831116 PHY */
#define	CONFIG_MII		/* expose smi ove miiphy interface */
#define CONFIG_SYS_FAULT_ECHO_LINK_DOWN	/* detect link using phy */
#define CONFIG_ENV_OVERWRITE	/* ethaddr can be reprogrammed */

#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP
#endif

/*-----------------------------------------------------------------------
 * IDE
 */
#ifdef CONFIG_CMD_IDE
#define __io
#define CONFIG_IDE_PREINIT
#define CONFIG_DOS_PARTITION
#define CONFIG_CMD_EXT2
/* ED Mini V has an IDE-compatible SATA connector for port 1 */
#define CONFIG_MVSATA_IDE
#define CONFIG_MVSATA_IDE_USE_PORT1
/* Needs byte-swapping for ATA data register */
#define CONFIG_IDE_SWAP_IO
/* Data, registers and alternate blocks are at the same offset */
#define CONFIG_SYS_ATA_DATA_OFFSET	(0x0100)
#define CONFIG_SYS_ATA_REG_OFFSET	(0x0100)
#define CONFIG_SYS_ATA_ALT_OFFSET	(0x0100)
/* Each 8-bit ATA register is aligned to a 4-bytes address */
#define CONFIG_SYS_ATA_STRIDE		4
/* Controller supports 48-bits LBA addressing */
#define CONFIG_LBA48
/* A single bus, a single device */
#define CONFIG_SYS_IDE_MAXBUS		1
#define CONFIG_SYS_IDE_MAXDEVICE	1
/* ATA registers base is at SATA controller base */
#define CONFIG_SYS_ATA_BASE_ADDR	ORION5X_SATA_BASE
/* ATA bus 0 is orion5x port 1 on ED Mini V2 */
#define CONFIG_SYS_ATA_IDE0_OFFSET	ORION5X_SATA_PORT1_OFFSET
/* end of IDE defines */
#endif /* CMD_IDE */

/*-----------------------------------------------------------------------
 * Size of malloc() pool
 */
#define CONFIG_SYS_GBL_DATA_SIZE		128		/* size in bytes reserved for initial data */

#define CONFIG_SYS_MALLOC_LEN			(1024 * 1024)
#define CONFIG_SYS_MONITOR_LEN			(252 * 1024)
#define CONFIG_SYS_MONITOR_BASE			(CONFIG_SYS_FLASH_BASE)
#define CONFIG_SYS_MONITOR_IMAGE_OFFSET 	0x0

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

/*-----------------------------------------------------------------------
 * Serial
 */
#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE		-4               /* NS16550 register size */
#define CONFIG_SYS_NS16550_COM1			ORION5X_UART0_BASE      /* Base address of UART0 */
#define CONFIG_SYS_NS16550_CLK			CONFIG_SYS_TCLK          /* Input clock to NS16550 */
#define CONFIG_CONS_INDEX			1               /* use UART0 for console */
#define CONFIG_BAUDRATE				115200          /* Default baud rate */
#define CONFIG_SYS_BAUDRATE_TABLE		{ 9600, 19200, 38400, 57600, 115200, 230400 }

#define CONFIG_BOOTDELAY	5
#define CONFIG_ZERO_BOOTDELAY_CHECK  	/* check console even if bootdelay = 0 */

//#define CONFIG_BOOTCOMMAND "cp.b 0xff9a0000 0x400000 0x60d653;bootm 0xff820000 0x400000" /* for standard dns-323 flash map */
//#define CONFIG_BOOTARGS "root=/dev/ram console=ttyS0,115200 :::DB88FXX81:egiga0:none"

/*
 * Miscellaneous configurable options
 */
//#define	CONFIG_SYS_LONGHELP			/* undef to save memory		*/
#define	CONFIG_SYS_PROMPT		"z5 # "	/* Monitor Command Prompt	*/
#define	CONFIG_SYS_CBSIZE		256		/* Console I/O Buffer Size	*/
#define	CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define	CONFIG_SYS_MAXARGS		16		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_MEMTEST_START		0x00400000
#define CONFIG_SYS_MEMTEST_END			0x00800000

#define CONFIG_SYS_ALT_MEMTEST
#define	CONFIG_SYS_LOAD_ADDR			0x00400000	/* default load address	*/

#undef  CONFIG_SYS_CLKS_IN_HZ		/* everything, incl board info, in Hz */

/* support BZIP2 compression */
//#define CONFIG_BZIP2		1

/************************************************************
 * Ident
 ************************************************************/
#define VERSION_TAG "unstable"
#define CONFIG_IDENT_STRING " Z5 " VERSION_TAG

/*-----------------------------------------------------------------------
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */
#define CONFIG_STACKSIZE	(128*1024)	/* regular stack */
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ	(4*1024)	/* IRQ stack */
#define CONFIG_STACKSIZE_FIQ	(4*1024)	/* FIQ stack */
#endif

/*
 * Other required minimal configurations
 */
#define CONFIG_CONSOLE_INFO_QUIET	/* some code reduction */
#define CONFIG_ARCH_CPU_INIT		/* call arch_cpu_init() */
#define CONFIG_ARCH_MISC_INIT		/* call arch_misc_init() */
#define CONFIG_DISPLAY_CPUINFO		/* Display cpu info */

#define CONFIG_SYS_RESET_ADDRESS	0xffff0000


#define CONFIG_CMDLINE_EDITING
#define CONFIG_COMMAND_HISTORY
#define CONFIG_COMMAND_EDIT

#undef BOARD_LATE_INIT

#endif	/* __CONFIG_H */
