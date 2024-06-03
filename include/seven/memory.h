/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

// BIOS ROM (16K)
#define MEM_BIOS                ((const void*)0x00000000)
#define MEM_BIOS_SIZE           UNIT_KIB(16)

// External Work RAM (256K)
#define MEM_EWRAM               ((void*)0x02000000)
#define MEM_EWRAM_SIZE          UNIT_KIB(256)

// Internal Work RAM (32K)
#define MEM_IWRAM               ((void*)0x03000000)
#define MEM_IWRAM_SIZE          UNIT_KIB(32)

// I/O Register Area
#define MEM_IO                  ((volatile void*)0x04000000)
#define MEM_IO_SIZE             ((size_t)0x20C)

// Common alias for MEM_IO
#define REG_BASE                MEM_IO

// Video Palette (1K)
#define MEM_PALETTE             ((void*)0x05000000)
#define MEM_PALETTE_SIZE        UNIT_KIB(1)

// Video RAM (96K)
#define MEM_VRAM                ((void*)0x06000000)
#define MEM_VRAM_SIZE           UNIT_KIB(96)

// Object Attribute Memory (1K)
#define MEM_OAM                 ((void*)0x07000000)
#define MEM_OAM_SIZE            UNIT_KIB(1)

// Cartridge ROM (32M)
#define MEM_ROM                 ((const void*)0x08000000)
#define MEM_ROM_SIZE            UNIT_MIB(32)

// Cartridge Static RAM (32K)
#define MEM_SRAM                ((void*)0x0E000000)
#define MEM_SRAM_SIZE           UNIT_KIB(32)

_LIBSEVEN_EXTERN_C_END
