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
 */

#include "types.h"

#include <cassert>

namespace {
    const std::vector<TypeData> floatTypes {{"float" , "", "f", "", "f"}
                                           ,{"double", "", "d", "", ""}
                                           };
    const std::vector<TypeData> integerTypes {{"char" , "b", "", "ERROR", "ERROR"}
                                             ,{"short", "s", "", "ERROR", "ERROR"}
                                             ,{"int"  , "i", "", "", ""}
                                             ,{"long" , "l", "", "l", ""}
                                             ,{"unsigned char" , "ub", "", "ERROR", "ERROR"}
                                             ,{"unsigned short", "us", "", "ERROR", "ERROR"}
                                             ,{"unsigned int"  , "u" , "", "u", ""}
                                             ,{"unsigned long" , "ul", "", "ul", ""}
                                             };
}

std::vector<TypeData>::const_iterator begin(Type t) {
    if (t == Float) return floatTypes.begin();
    if (t == Integer) return integerTypes.begin();
    assert(false);
}

std::vector<TypeData>::const_iterator end(Type t) {
    if (t == Float) return floatTypes.end();
    if (t == Integer) return integerTypes.end();
    assert(false);
}
