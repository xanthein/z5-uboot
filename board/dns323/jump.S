/*
 * The kuropro flash starts at 0xfffc0000 but booting begins at
 * 0xffff0000. u-boot.lds puts this code at 0xffff0000
 *
 *  Copyright (c) 2008 Byron Bradley <byron.bbradley@gmail.com>
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

jump_reset:

.section	".jump_reset", #alloc, #execinstr
	ldr lr, = 0xfffd0000
	mov pc, lr
