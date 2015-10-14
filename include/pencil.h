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

/* There are 2 ways to use a PENCIL file:
 *
 * 1. As Normal C file:
 *    - All PENCIL specific functions (like __pencil_assert) must be ignored.
 *    - All PENCIL built-in functions (math functions, for example) must be
 *      implemented.
 *
 * 2. As PENCIL file supplied to the PENCIL compiler:
 *    - All PENCIL specific functions must be preserved.
 *    - All PENCIL build-in function must be declared (to make the front-end
 *      happy), but not implemented.
 *
 * It is possible by the spec to have PENCIL-functions as an extension to C
 * embedded into C-code. This mode is broken because we cannot have different
 * macro defintions within the embedded PENCIL-functions than around. It is
 * still the mode used most of the time.
 */

#ifndef PENCIL_H
#define PENCIL_H

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
