/*-
 * Copyright (c) 2011 NetApp, Inc.
 * All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY NETAPP, INC ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL NETAPP, INC OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#ifndef VMCS_H
#define VMCS_H

#include <Hypervisor/hv.h>
#include <Hypervisor/hv_vmx.h>

#define VMCS_INITIAL 0xffffffffffffffff

#define VMCS_IDENT(encoding) ((encoding) | 0x80000000)
/*
 * VMCS field encodings from Appendix H, Intel Architecture Manual Vol3B.
 */
#define VMCS_INVALID_ENCODING 0xffffffff

/* 64-bit control fields */
#define VMCS_EOI_EXIT(vector) (VMCS_CTRL_EOI_EXIT_BITMAP_0 + ((vector) / 64) * 2)

/*
 * VM instruction error numbers
 */
#define VMRESUME_WITH_NON_LAUNCHED_VMCS 5

/*
 * NMI unblocking due to IRET.
 *
 * Applies to VM-exits due to hardware exception or EPT fault.
 */
#define EXIT_QUAL_NMIUDTI (1 << 12)

/*
 * VMCS interrupt information fields
 */
#define VMCS_INTR_T_MASK 0x700 /* Interruption-info type */

/*
 * VMCS IDT-Vectoring information fields
 */
#define VMCS_IDT_VEC_VECNUM 0xFF
#define VMCS_IDT_VEC_TYPE 0x700

/*
 * VMCS Guest interruptibility field
 */
#define VMCS_INTERRUPTIBILITY_STI_BLOCKING (1 << 0)
#define VMCS_INTERRUPTIBILITY_MOVSS_BLOCKING (1 << 1)
#define VMCS_INTERRUPTIBILITY_SMI_BLOCKING (1 << 2)
#define VMCS_INTERRUPTIBILITY_NMI_BLOCKING (1 << 3)

/*
 * Exit qualification for EXIT_REASON_INVAL_VMCS
 */
#define EXIT_QUAL_NMI_WHILE_STI_BLOCKING 3

/*
 * Exit qualification for EPT violation
 */
#define EPT_VIOLATION_DATA_READ (1UL << 0)
#define EPT_VIOLATION_DATA_WRITE (1UL << 1)
#define EPT_VIOLATION_INST_FETCH (1UL << 2)
#define EPT_VIOLATION_GPA_READABLE (1UL << 3)
#define EPT_VIOLATION_GPA_WRITEABLE (1UL << 4)
#define EPT_VIOLATION_GPA_EXECUTABLE (1UL << 5)
#define EPT_VIOLATION_GLA_VALID (1UL << 7)
#define EPT_VIOLATION_XLAT_VALID (1UL << 8)

/*
 * Exit qualification for APIC-access VM exit
 */
#define APIC_ACCESS_OFFSET(qual) ((qual) & 0xFFF)
#define APIC_ACCESS_TYPE(qual) (((qual) >> 12) & 0xF)

/*
 * Exit qualification for APIC-write VM exit
 */
#define APIC_WRITE_OFFSET(qual) ((qual) & 0xFFF)

enum task_switch_reason {
    TSR_CALL,
    TSR_IRET,
    TSR_JMP,
    TSR_IDT_GATE, /* task gate in IDT */
};

#endif
