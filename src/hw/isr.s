@
@ This Source Code Form is subject to the terms of the Mozilla Public
@ License, v. 2.0. If a copy of the MPL was not distributed with this
@ file, You can obtain one at https://mozilla.org/MPL/2.0/.
@
.syntax         unified
.cpu            arm7tdmi

.include        "constants.s"
.include        "macros.s"

.equiv OFF_IE,          REG_IE - REG_BASE
.equiv OFF_IME,         REG_IME - REG_BASE
.equiv OFF_IE_IF,       REG_IF  - REG_IE
.equiv OFF_IE_IME,      REG_IME - REG_IE
.equiv OFF_IE_IFBIOS,   REG_IFBIOS - REG_IE

@ r0: REG_BASE
@ r1: Interrupt flag
@ r2: <scratch>
@ r3: Handler function
fn isrDefault arm
    @ The GBA BIOS always calls the IRQ handler with r0 = 0x04000000,
    @ however this is unreliable in emulators/GBARunner/etc.
    mov         r0, 0x04000000                                  @ 1

    @ Read IE & IF
    ldr         r1, [r0, OFF_IE]!                               @ 4
    and         r1, r1, r1, lsr 16                              @ 5

    @ Handle the lowest set IRQ
    rsb         r2, r1, 0                                       @ 6
    and         r1, r1, r2                                      @ 7

    @ Acknowlegde IF
    strh        r1, [r0, OFF_IE_IF]                             @ 9

    @ Acknowledge IFBIOS
    ldr         r2, [r0, OFF_IE_IFBIOS]!                        @ 12
    orr         r2, r2, r1                                      @ 13
    strh        r2, [r0], 8                                     @ 15

    @ Lookup the IRQ handler using a 16-bit Debruijn sequence.
    mov         r0, 0x09 << 24                                  @ 16
    orr         r0, 0xAF << 16                                  @ 17
    mul         r2, r0, r1                                      @ 19 / 20
    lsr         r2, r2, 28                                      @ 21

    @ Load handler
    adr         r3, ISR_DEFAULT_HANDLERS                        @ 22
    ldr         r3, [r3, r2, lsl 2]                             @ 25
    cmp         r3, 0                                           @ 26
    bxeq        lr                                              @ 27 / 29

    @ Enable nesting
    mrs         r2, spsr                                        @ 28
    msr         cpsr_c, 0x9F                                    @ 29
    push        {r2, lr}                                        @ 32

    @ Call
    mov         r0, r1                                          @ 33
    mov         lr, pc                                          @ 34
    bx          r3                                              @ 37

    @ Return
    pop         {r2, lr}                                        @ 41
    msr         cpsr_c, 0x92                                    @ 42
    msr         spsr, r2                                        @ 43
    bx          lr                                              @ 46
data ISR_DEFAULT_HANDLERS global .inline=1
    .fill       16, 4, 0
endd
endfn

@ r0: REG_BASE
@ r1: Interrupt flag
@ r2: <scratch>
@ r3: Handler function
fn isrMinimal arm
    mov         r0, 0x04000000                                  @ 1

    @ Read IE & IF
    ldr         r1, [r0, #OFF_IE]!                              @ 4
    and         r1, r1, r1, lsr #16                             @ 5

    @ Acknowledge IF
    strh        r1, [r0, #OFF_IE_IF]                            @ 7

    @ Acknowledge IFBIOS
    ldr         r2, [r0, #OFF_IE_IFBIOS]!                       @ 10
    orr         r2, r2, r1                                      @ 11
    strh        r2, [r0], 8                                     @ 13

    @ Load handler
    ldr         r3, ISR_MINIMAL_HANDLER                         @ 16
    cmp         r3, 0                                           @ 17
    bxeq        lr                                              @ 18 / 20 (exit)

    @ Call
    mov         r0, r1                                          @ 19
    bx          r3                                              @ 22
data ISR_MINIMAL_HANDLER global .inline=1
    .word       0
endd
endfn

@ vim: ft=armv4 et sta sw=4 sts=8
