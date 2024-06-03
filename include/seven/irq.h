/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

#define IRQ_ENTRY _LIBSEVEN_TARGET_ARM

// Interrupt Enable Register.
#define REG_IE     VOLADDR(0x04000200, uint16_t)

// Interrupt Flags Register.
#define REG_IF     VOLADDR(0x04000202, uint16_t)

// Interrupt Master Enable Register.
#define REG_IME    VOLADDR(0x04000208, uint16_t)

// Interrupt Entry Function Pointer.
#define MEM_ISR    VOLADDR(0x03FFFFFC, IrqEntryFn*)

// Interrupt Flags used by BIOS wait functions.
#define MEM_IFBIOS VOLADDR(0x03FFFFF8, uint16_t)

// Interrupt flags.
enum IRQFlag
{
    IRQ_VBLANK    = BIT(0),
    IRQ_HBLANK    = BIT(1),
    IRQ_VCOUNT    = BIT(2),
    IRQ_TIMER_0   = BIT(3),
    IRQ_TIMER_1   = BIT(4),
    IRQ_TIMER_2   = BIT(5),
    IRQ_TIMER_3   = BIT(6),
    IRQ_SERIAL    = BIT(7),
    IRQ_DMA_0     = BIT(8),
    IRQ_DMA_1     = BIT(9),
    IRQ_DMA_2     = BIT(10),
    IRQ_DMA_3     = BIT(11),
    IRQ_KEYPAD    = BIT(12),
    IRQ_CARTRIDGE = BIT(13),
};

// Common sets of interrupts.
enum IRQGroup
{
    IRQS_BLANK    = IRQ_VBLANK  | IRQ_HBLANK,
    IRQS_TIMER    = IRQ_TIMER_0 | IRQ_TIMER_1 | IRQ_TIMER_2 | IRQ_TIMER_3,
    IRQS_DMA      = IRQ_DMA_0   | IRQ_DMA_1   | IRQ_DMA_2   | IRQ_DMA_3,
    // IRQs in this group can wake up the GBA from biosStop().
    IRQS_EXTERNAL = IRQ_SERIAL  | IRQ_KEYPAD  | IRQ_CARTRIDGE,
    IRQS_ALL      = BITS(14),
};

// Bit indices of interrupts.
enum IRQIndex
{
    IRQ_INDEX_VBLANK,
    IRQ_INDEX_HBLANK,
    IRQ_INDEX_VCOUNT,
    IRQ_INDEX_TIMER_0,
    IRQ_INDEX_TIMER_1,
    IRQ_INDEX_TIMER_2,
    IRQ_INDEX_TIMER_3,
    IRQ_INDEX_SERIAL,
    IRQ_INDEX_DMA_0,
    IRQ_INDEX_DMA_1,
    IRQ_INDEX_DMA_2,
    IRQ_INDEX_DMA_3,
    IRQ_INDEX_KEYPAD,
    IRQ_INDEX_CARTRIDGE,
    IRQ_INDEX_MAX,
};

// Function type for interrupt entry.
//
// The interrupt entry function is called by the BIOS when the CPU receives an interrupt request
// (IRQ). This function must use ARM code, and is typically located in IWRAM.
//
// Libseven provides two optimized interrupt entry functions, available through `irqInitVectored`
// and `irqInitMinimal`. To use your own interrupt entry function, call `irqInit`.
//
// Use the IRQ_ENTRY attribute to define your own entry function.
typedef void IrqEntryFn(void);

// Function type for interrupt callbacks.
//
// Callback functions are used by libseven's "vectored" and "minimal" interrupt entry functions.
//
// The function receives the triggered IRQs as the first parameter.
typedef void IrqFn(uint16_t);

// Initialize interrupt handling with a user-provided function.
//
extern void irqInit(IrqEntryFn *entry);

// Initialize interrupt handling using an array of handler functions.
//
// Uses the system mode stack for operation, so more stack space is available by default.
// Nested interrupts can be opted into by calling `irqUnmask`.
//
// See the `irqHandler*` functions for setting up handler functions.
extern void irqInitVectored(void);

// Initialize interrupt handling using a single, optional handler function.
//
// Uses the interrupt mode stack for operation, so stack space is limited by default.
// Nested interrupts are *not* supported by default.
//
// If `fn` is NULL, no function will be called. This provides the minimum handling required for
// `biosIntrWait` / `biosVBlankIntrWait` to work.
extern void irqInitMinimal(IrqFn *fn);

// Set the callback associated with the specified irq.
//
// Fails if irq specifies more than one interrupt.
extern bool irqCallbackSet(uint16_t irq, IrqFn *fn);

// Get the callback associated with the specified irq.
//
// Fails if irq specifies more than one interrupt.
extern bool irqCallbackGet(uint16_t irq, IrqFn **fn);

// Swap the callback associated with the specified irq, returning the old one.
//
// Fails if irq specifies more than one interrupt.
extern bool irqCallbackSwap(uint16_t, IrqFn **fn);

// Enable the specified IRQs.
//
// Returns the old value of the IE register.
extern uint16_t irqEnable(uint16_t irqs);

// Disable the specified IRQs.
//
// Returns the old value of the IE register.
extern uint16_t irqDisable(uint16_t irqs);

// Calls `f(arg)` with interrupts disabled.
extern void irqFree(void (*f)(void *), void *arg);

// Mask IRQs at the CPU level.
extern void irqMask(void);

// Unmask IRQs at the CPU level.
extern void irqUnmask(void);

// Returns whether IRQs are masked at the CPU level.
extern bool irqMasked(void);

_LIBSEVEN_EXTERN_C_END
