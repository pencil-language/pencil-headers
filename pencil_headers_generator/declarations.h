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

#ifndef DECLARATIONS_H
#define	DECLARATIONS_H

#include "function.h"

#include <boost/regex.hpp>

namespace PENCIL {
    template<typename Stream>
    Stream& operator<<(Stream& s, const Function& fun) {
        //Iterate through all possible types
        for(auto&& typeData : fun.type) {
            //Function declaration
            s << typeData.typeStr << ' ' << typeData.prefix << fun.name << typeData.suffix;
            //Parameters
            fun.generateParameters(s, typeData.typeStr);
            //End of declaration
            s << " __attribute__((const));\n";
        }
        return s;
    }
}

namespace C_implementation {
    template<typename Stream>
    Stream& operator<<(Stream& s, const Function& fun) {
        //Iterate through all possible types
        for(auto&& typeData : fun.type) {
            if (fun.c_implementation.empty()) {
                //Default implementation: just simply use the corresponding C stdlib (math.h / stdlib.h / ..) function
                if (typeData.prefix != typeData.cprefix || typeData.suffix != typeData.csuffix) {
                    s << "#define " << typeData.prefix << fun.name << typeData.suffix << ' ' << typeData.cprefix << fun.name << typeData.csuffix << '\n';
                }
            } else {
                //Provided implementation: define a function.
                //Function declaration
                s << "static inline " << typeData.typeStr << " __attribute__((const, always_inline)) " << typeData.prefix << fun.name << typeData.suffix;
                //Parameters
                fun.generateParameters(s, typeData.typeStr);
                //End of declaration, start implementation
                boost::regex type("TYPE");
                boost::regex prefix("PREFIX");
                boost::regex suffix("SUFFIX");
                boost::regex cprefix("CPREFIX");
                boost::regex csuffix("CSUFFIX");
                
                std::string replaced = fun.c_implementation;
                replaced = boost::regex_replace(replaced,    type, typeData.typeStr);
                replaced = boost::regex_replace(replaced, cprefix, typeData.cprefix);
                replaced = boost::regex_replace(replaced, csuffix, typeData.csuffix);
                replaced = boost::regex_replace(replaced,  prefix, typeData.prefix);
                replaced = boost::regex_replace(replaced,  suffix, typeData.suffix);
                s << " { " << replaced << " }\n";
            }
        }
        return s;
    }
}

namespace OpenCL_implementation {
    template<typename Stream>
    Stream& operator<<(Stream& s, const Function& fun) {
        //Iterate through all possible types
        for(auto&& typeData : fun.type) {
            if (fun.opencl_implementation.empty()) {
                //Default implementation: define a macro that calls the corresponding builtin function, with parameters cast to the correct type
                s << "#define " << typeData.prefix << fun.name << typeData.suffix;
                //Parameters
                fun.generateParameters(s, "");
                s << ' ';
                //End of declaration, start implementation
                s << fun.name;
                fun.generateParameters(s, typeData.typeStr, true);
                s << '\n';
            } else {
                //Provided implementation: define a function.
                //Function declaration
                s << "inline " << typeData.typeStr << " __attribute__((const)) " << typeData.prefix << fun.name << typeData.suffix;
                //Parameters
                fun.generateParameters(s, typeData.typeStr);
                //End of declaration, start implementation
                s << " { " << fun.opencl_implementation << " }\n";
            }
        }
        return s;
    }
}

#endif	/* DECLARATIONS_H */

