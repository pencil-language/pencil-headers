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

#include "declarations.h"
#include "pencil_stdlib.h"

#include <iostream>
#include <fstream>

static const std::string copyrightNotice = R"(/*
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
 */
)";

int main() {
    {
        std::cout << "PENCIL\n";
        std::ofstream header("pencil_prototypes.h");
        header << copyrightNotice;
        header << "#ifndef PENCIL_PROTOTYPES_H\n";
        header << "#define PENCIL_PROTOTYPES_H\n";
        for(auto&& function : get_functions()) {
            using namespace PENCIL;
            std::cout << function;
            header << function;
        }
        header << "#endif\n";
    }
    {
        std::cout << "C\n";
        std::ofstream header("pencil_lib.h");
        header << copyrightNotice;
        header << "#ifndef PENCIL_LIB_H\n";
        header << "#define PENCIL_LIB_H\n";
        header << "#include <math.h>\n";
        header << "#ifndef M_PI\n";
        header << "#define M_PI 3.14159265358979323846\n";
        header << "#endif\n";
        for(auto&& function : get_functions()) {
            using namespace C_implementation;
            std::cout << function;
            header << function;
        }
        header << "#endif\n";
    }
    {
        std::cout << "OpenCL\n";
        std::ofstream header("pencil_opencl.h");
        header << copyrightNotice;
        header << "#ifndef PENCIL_OPENCL_H\n";
        header << "#define PENCIL_OPENCL_H\n";
        for(auto&& function : get_functions()) {
            using namespace OpenCL_implementation;
            std::cout << function;
            header << function;
        }
        header << "#endif\n";
    }
}
