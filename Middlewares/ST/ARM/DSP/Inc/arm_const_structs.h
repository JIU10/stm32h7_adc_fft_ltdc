/* ----------------------------------------------------------------------
    2 * Copyright (C) 2010-2014 ARM Limited. All rights reserved.
    3 *
    4 * $Date:        31. July 2014
    5 * $Revision:    V1.4.4
    6 *
    7 * Project:          CMSIS DSP Library
    8 * Title:            arm_const_structs.h
    9 *
   10 * Description:  This file has constant structs that are initialized for
   11 *              user convenience.  For example, some can be given as
   12 *              arguments to the arm_cfft_f32() function.
   13 *
   14 * Target Processor: Cortex-M4/Cortex-M3
   15 *
   16 * Redistribution and use in source and binary forms, with or without
   17 * modification, are permitted provided that the following conditions
   18 * are met:
   19 *   - Redistributions of source code must retain the above copyright
   20 *     notice, this list of conditions and the following disclaimer.
   21 *   - Redistributions in binary form must reproduce the above copyright
   22 *     notice, this list of conditions and the following disclaimer in
   23 *     the documentation and/or other materials provided with the
   24 *     distribution.
   25 *   - Neither the name of ARM LIMITED nor the names of its contributors
   26 *     may be used to endorse or promote products derived from this
   27 *     software without specific prior written permission.
   28 *
   29 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   30 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   31 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
   32 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
   33 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
   34 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
   35 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   36 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
   37 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
   38 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
   39 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   40 * POSSIBILITY OF SUCH DAMAGE.
   41 * -------------------------------------------------------------------- */

 #ifndef _ARM_CONST_STRUCTS_H
 #define _ARM_CONST_STRUCTS_H

 #include "arm_math.h"


   extern const arm_cfft_instance_f32 arm_cfft_sR_f32_len16;
    extern const arm_cfft_instance_f32 arm_cfft_sR_f32_len32;
    extern const arm_cfft_instance_f32 arm_cfft_sR_f32_len64;
    extern const arm_cfft_instance_f32 arm_cfft_sR_f32_len128;
    extern const arm_cfft_instance_f32 arm_cfft_sR_f32_len256;
    extern const arm_cfft_instance_f32 arm_cfft_sR_f32_len512;
    extern const arm_cfft_instance_f32 arm_cfft_sR_f32_len1024;
    extern const arm_cfft_instance_f32 arm_cfft_sR_f32_len2048;
    extern const arm_cfft_instance_f32 arm_cfft_sR_f32_len4096;

    extern const arm_cfft_instance_q31 arm_cfft_sR_q31_len16;
    extern const arm_cfft_instance_q31 arm_cfft_sR_q31_len32;
    extern const arm_cfft_instance_q31 arm_cfft_sR_q31_len64;
    extern const arm_cfft_instance_q31 arm_cfft_sR_q31_len128;
    extern const arm_cfft_instance_q31 arm_cfft_sR_q31_len256;
    extern const arm_cfft_instance_q31 arm_cfft_sR_q31_len512;
    extern const arm_cfft_instance_q31 arm_cfft_sR_q31_len1024;
    extern const arm_cfft_instance_q31 arm_cfft_sR_q31_len2048;
    extern const arm_cfft_instance_q31 arm_cfft_sR_q31_len4096;
    extern const arm_cfft_instance_q15 arm_cfft_sR_q15_len16;
    extern const arm_cfft_instance_q15 arm_cfft_sR_q15_len32;
    extern const arm_cfft_instance_q15 arm_cfft_sR_q15_len64;
    extern const arm_cfft_instance_q15 arm_cfft_sR_q15_len128;
    extern const arm_cfft_instance_q15 arm_cfft_sR_q15_len256;
    extern const arm_cfft_instance_q15 arm_cfft_sR_q15_len512;
    extern const arm_cfft_instance_q15 arm_cfft_sR_q15_len1024;
    extern const arm_cfft_instance_q15 arm_cfft_sR_q15_len2048;
    extern const arm_cfft_instance_q15 arm_cfft_sR_q15_len4096;

 #endif