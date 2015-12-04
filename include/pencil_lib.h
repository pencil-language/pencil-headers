/*
 * Copyright (c) 2014, Realeyes
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
 * 
 * Note: this is a generated file. Do not modify.
 * Note supplement: The vanilla generated file clashes with defintions of other
 * standard libraries. It doesn't even match the PENCIL specification. Until
 * these clashes have been worked out, do not re-generate this file.
 */
#ifndef PENCIL_LIB_H
#define PENCIL_LIB_H
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


// sinf declared in <math.h>
static inline double __attribute__((const, always_inline)) sind(double x) { return sin(x); }
// cosf declared in <math.h>
static inline double __attribute__((const, always_inline)) cosd(double x) { return cos(x); }

static inline float __attribute__((const, always_inline)) mixf(float x, float y, float a) { return x + (y - x) * a; }
static inline double  __attribute__((const, always_inline)) mixd(double x, double y, double a) { return x + (y - x) * a; }

static inline double  __attribute__((pure, always_inline)) clamp(int x, int hi, int lo) { if (x>hi) return hi; if (x<lo) return lo; return x; }

#endif
