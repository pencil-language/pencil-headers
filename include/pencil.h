/*
 * Copyright (c) 2014, ARM Limited
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*

Toolchains:

 ___________________ ___________________ ___________________ ___________________
 |     .pencil     | |     .pencil     | |       .c        | |   .c/.pencil.c  |
 ------------------- ------------------- ------------------- -------------------

 ___________________
 |       cpp       |
 |-D__PENCIL__=1   |
 |-D__PENCIL_PURE__|
 |-D__PENCIL_OPT__ |
 -------------------

 ___________________
 | pencil-optimizer|
 -------------------

 ___________________ ___________________ ___________________
 |      ppcg       | |      ppcg       | |      ppcg       |
 |--pet-autodetect | |--pet-autodetect | |                 |
 |-D__PENCIL__=2   | |-D__PENCIL__=2   | |-D__PENCIL__=2   |
 |-D__PENCIL_PURE__| |-D__PENCIL_PURE__| |                 |
 |-D__PENCIL_OPT__ | |                 | |                 |
 ------------------- ------------------- -------------------

 ___________________ ___________________ ___________________ ___________________
 |    gcc/nvcc     | |    gcc/nvcc     | |    gcc/nvcc     | |       gcc       |
 |                 | |                 | |                 | |                 |
 |-D__PENCIL__=3   | |-D__PENCIL__=3   | |-D__PENCIL__=3   | |                 |
 ------------------- ------------------- ------------------- -------------------

 The toolchain with pencil-optimizer is currently unsupported.


Backends:

* OpenCL
  - gcc
  - -D__PENCIL_OPENCL__

* CUDA
  - nvcc
  - -D__PENCIL_CUDA__

*/

#ifndef PENCIL_H
#define PENCIL_H

#include <math.h>


#if defined(__PENCIL_CUDA__) && (__PENCIL__==3)
#define _PENCIL_USE_C99_VLA 0
#else
#define _PENCIL_USE_C99_VLA 1
#endif



#define _PENCIL_CONCAT_internal(x,y) x ## y
#define _PENCIL_CONCAT(x,y) _PENCIL_CONCAT_internal(x,y)
//#define _PENCIL_CONCAT3(x,y,z)  _PENCIL_CONCAT_internal(x, _PENCIL_CONCAT_internal(y,z))
#define _PENCIL_INVOKE(x,...) x(__VA_ARGS__)

#define _PENCIL_NARGS_internal(unused, _1, _2, _3, _4, _5, VAL, ...) VAL
#define _PENCIL_NARGS(...) _PENCIL_NARGS_internal(unused, ## __VA_ARGS__, 5, 4, 3, 2, 1, 0)

#define _PENCIL_NARGS_DIV2_internal(unused, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, VAL, ...) VAL
#define _PENCIL_NARGS_DIV2(...) _PENCIL_NARGS_DIV2_internal(unused, ## __VA_ARGS__, 5, invalid, 4, invalid, 3, invalid, 2, invalid, 1, invalid, 0)



#if _PENCIL_USE_C99_VLA
#define _PENCIL_VLA_PARAM_1(type,name,size1) type name[static const restrict size1]
#define _PENCIL_VLA_DEREF_1(name,size1,index1) name[index1]
#else
#define _PENCIL_VLA_PARAM_1(type,name,SIZE1) type *name
#define _PENCIL_VLA_DEREF_1(name,size1,index1) name[index1]
#endif


#define PENCIL_VLA_PARAM(type,name,...) _PENCIL_INVOKE(_PENCIL_CONCAT(_PENCIL_VLA_PARAM_,_PENCIL_NARGS     (__VA_ARGS__)),type,name,__VA_ARGS__)
#define PENCIL_VLA_DEREF(     name,...) _PENCIL_INVOKE(_PENCIL_CONCAT(_PENCIL_VLA_DEREF_,_PENCIL_NARGS_DIV2(__VA_ARGS__)),     name,__VA_ARGS__)




/* Preprocessor aliases for PENCIL builtins */
#define USE __pencil_use
#define DEF __pencil_def
#define MAYBE __pencil_maybe()

#ifdef __PENCIL__
/* The file is processed by the PENCIL-to-OpenCL code generator. */

/* Custom stdbool.h */
#define bool _Bool
#define true 1
#define false 0
#define __bool_true_false_are_defined 1

/* PENCIL-specific macros */
#define ACCESS(...) __attribute__((pencil_access(__VA_ARGS__)))

#include "pencil_prototypes.h"

#else /* __PENCIL__ */
/* The file is processed as a C file. */

/* PENCIL to C compatibility layer. */
#include "pencil_compat.h"

#endif /* __PENCIL__ */

#ifndef PRL_PENCIL_H
/* This is for outer C-code not itself PENCIL-code calling PENCIL functions. */
/* TODO: We maybe should put it into a separate header file because it is not
 * compatible to the PENCIL grammar. It is not sufficient to put it into the
 * "The file is processed as a C file" branch it would not be available to host
 * code when compiling embedded PENCIL functions using ppcg.
 */
enum npr_mem_tags {
	PENCIL_NPR_MEM_NOWRITE = 1,
	PENCIL_NPR_MEM_NOREAD = 2,
	PENCIL_NPR_MEM_NOACCESS = PENCIL_NPR_MEM_NOWRITE | PENCIL_NPR_MEM_NOREAD,
	PENCIL_NPR_MEM_READ = 4,
	PENCIL_NPR_MEM_WRITE = 8,
	PENCIL_NPR_MEM_READWRITE = PENCIL_NPR_MEM_READ | PENCIL_NPR_MEM_WRITE
};
void __prl_npr_mem_tag(void *location, enum npr_mem_tags mode) __attribute__((weak));
static void __pencil_npr_mem_tag(void *location, enum npr_mem_tags mode) {
	if (&__prl_npr_mem_tag)
		__prl_npr_mem_tag(location, mode);
}
#endif /* PRL_PENCIL_H */

#endif /* PENCIL_H */
