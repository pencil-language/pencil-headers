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

#ifndef FUNCTION_H
#define	FUNCTION_H

#include "types.h"

#include <string>
#include <functional>

struct Parameter {
    std::string name;
    std::string type;
};

struct Function {
    Type type;
    std::string name;
    std::vector<Parameter> parameters;
    std::string c_implementation;
    std::string opencl_implementation;
    
    Function( Type                     type
            , std::string              name
            , std::vector<std::string> parameters
            , std::string              c_implementation = ""
            , std::string              opencl_implementation = ""
            )
        : type(type)
        , name(name)
        , c_implementation(c_implementation)
        , opencl_implementation(opencl_implementation)
    {
        for(const auto& param : parameters) {
            auto pos = param.find(' ');
            if (std::string::npos == pos) {
                this->parameters.push_back({param});
            } else {
                this->parameters.push_back({param.substr(pos+1), param.substr(0, pos)});
            }
        }
    }

    template<typename Stream>
    void generateParameters(Stream& s, const std::string& typeStr, bool cast = false) const {
        s << '(';
        if (not parameters.empty()) {
            auto paramIt = parameters.begin();
            //First parameter's type
            if (not typeStr.empty()) {
                if (paramIt->type.empty()) {
                    if (cast) s << '(';
                    s << typeStr;
                    if (cast) s << ')';
                } else {
                    if (not cast) {
                        s << paramIt->type;
                    }
                }
                s << ' ';
            }
            //First parameter's name
            if (cast) s << '(';
            s << paramIt->name;
            if (cast) s << ')';
            //Rest of the parameters (might be empty)
            for (++paramIt; paramIt != parameters.end(); ++paramIt) {
                //Separator
                s << ", ";
                //Other parameter's type
                if (not typeStr.empty()) {
                    if (paramIt->type.empty()) {
                        if (cast) s << '(';
                        s << typeStr;
                        if (cast) s << ')';
                    } else {
                        if (not cast) {
                            s << paramIt->type;
                        }
                    }
                    s << ' ';
                }
                //Other parameter's name
                if (cast) s << '(';
                s << paramIt->name;
                if (cast) s << ')';
            }
        }
        s << ')';
    }
};

#endif	/* FUNCTION_H */

