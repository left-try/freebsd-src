/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Mitchell Horne <mhorne@FreeBSD.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _MACHINE_METADATA_H_
#define	_MACHINE_METADATA_H_

#define	MODINFOMD_DTBP		0x1001
#define	MODINFOMD_EFI_MAP	0x1002
#define	MODINFOMD_EFI_FB	0x1003
#define	MODINFOMD_BOOT_HARTID	0x1004

/*
 * This is not the same as the UEFI standard EFI_MEMORY_ATTRIBUTES_TABLE, though
 * memory_size / descritpr_size entries of EFI_MEMORY_DESCRIPTORS follow this table
 * starting at a 16-byte alignment.
 */
struct efi_map_header {
	size_t		memory_size;		/* Numnber of bytes that follow */
	size_t		descriptor_size;	/* Size of each EFI_MEMORY_DESCRIPTOR */
	uint32_t	descriptor_version;	/* Currently '1' */
};

/*
 * Placeholder for now
 */
struct efi_fb {
	uint64_t	fb_addr;
	uint64_t	fb_size;
	uint32_t	fb_height;
	uint32_t	fb_width;
	uint32_t	fb_stride;
	uint32_t	fb_mask_red;
	uint32_t	fb_mask_green;
	uint32_t	fb_mask_blue;
	uint32_t	fb_mask_reserved;
};

#endif /* !_MACHINE_METADATA_H_ */
