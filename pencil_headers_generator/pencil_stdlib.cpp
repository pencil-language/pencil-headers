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

#include "pencil_stdlib.h"

#define STR(s) #s

namespace {
    const std::vector<Function> functions {
        //Integer:
        //abs, absdiff, add_sat, hadd, rhadd, clz, mad_hi, mad24, mad_sat, max, min, mul_hi, mul24, rotate, sub_sat, upsample
         Function{Integer,    "abs", {"x"}, STR(return x < (TYPE)0 ? -x : x;)}
        //TODO: abs_diff
        //TODO: add_sat
        //TODO: hadd
        //TODO: rhadd
        //TODO: clz
        //TODO: ,{Integer, "mad_hi", {"a","b","c"}, STR(return mul_hi(a,b)+c;)}
        //TODO: mad24 (only int parameters)
        //TODO: mad_sat
        ,Function{Integer,    "max", {"a","b"      }, STR(return a>=b ? a : b;)}
        ,Function{Integer,    "min", {"a","b"      }, STR(return a<=b ? a : b;)}
        //TODO: mul_hi
        //TODO: mul24 (only int parameters)
        //TODO: rotate
        //TODO: sub_sat
        //TODO: upsample (returns bigger type)

        //Common:
        //clamp, degrees, mix, radians, sign, smoothstep, step
        ,Function{Float,  "clamp" , {"val","min", "max"}, STR(return (val<min) ? min : ((val>max) ? max : val);)}
        ,Function{Float, "degrees", {"rad"             }, STR(return (TYPE)(180.0/M_PI) * rad;                 )}
        ,Function{Float,    "mix" , {  "x",  "y",   "a"}, STR(return x + (y-x)*a;                              )}
        ,Function{Float, "radians", {"deg"             }, STR(return (TYPE)(M_PI/180.0) * deg;                 )}
        ,Function{Float,    "sign", {  "x"             }, STR( if(isnan(x))
                                                                   return (TYPE)0.0;
                                                               if (x>(TYPE)0.0)
                                                                   return (TYPE)1.0;
                                                               if (x<(TYPE)0.0)
                                                                   return (TYPE)-1.0;
                                                               return copysignCSUFFIX(x,(TYPE)0.0); )}
        //TODO: smoothstep
        ,Function{Float,    "step", {"edge", "x"       }, STR(return x<edge ? (TYPE)0.0 : (TYPE)1.0; )}

        //Math:
        //Basic: fmod, remainder, remquo, fma, mad, fdim, nan
        ,Function{Float,      "fmod", {"x"        }}
        ,Function{Float, "remainder", {"a","b"    }}
        ,Function{Float,    "remquo", {"x","y","int* quo"}}
        ,Function{Float,       "fma", {"a","b","c"}}
        ,Function{Float,       "mad", {"a","b","c"}, STR(return a*b+c;)}
        ,Function{Float,      "fdim", {"x","y"    }}
        //TODO: ,Function{Float,       "nan", {                 }}
        //Min/max: fabs, fmax, fmin, maxmag, minmag
        ,Function{Float,      "fmax", {"a","b"    }}
        ,Function{Float,      "fmin", {"a","b"    }}
        ,Function{Float,      "fabs", {"x"        }}
        //TODO: maxmag
        //TODO: minmag
        //Exponential: exp, exp2, exp10, expm1, log, log2, log10, log1p
        ,Function{Float,   "exp", {"x"}}
        ,Function{Float,  "exp2", {"x"}}
        ,Function{Float, "exp10", {"x"}, STR( return powCSUFFIX((TYPE)10, x); )}
        ,Function{Float, "expm1", {"x"}}
        ,Function{Float,   "log", {"x"}}
        ,Function{Float,  "log2", {"x"}}
        ,Function{Float, "log10", {"x"}}
        ,Function{Float, "log1p", {"x"}}
        //Power: pow, pown, powr, sqrt, rsqrt, cbrt, rootn, hypot
        ,Function{Float,   "pow", {"x","y"}}
        ,Function{Float,  "pown", {"x","int y"}, STR( return powCSUFFIX(x,y); )}
        ,Function{Float,  "powr", {"x","y"}    , STR( return powCSUFFIX(x,y); )}
        ,Function{Float,  "sqrt", {"x"    }}
        ,Function{Float, "rsqrt", {"x"    }, STR(return 1/sqrtCSUFFIX(x);)}
        ,Function{Float,  "cbrt", {"x"    }}
        ,Function{Float, "rootn", {"x","int n"}, STR( return powCSUFFIX(x,(TYPE)1.0/(TYPE)n); )}
        ,Function{Float, "hypot", {"x","y"}}
        //Trigonometric: sin, cos, tan, asin, acos, atan, atan2, sinpi, cospi, tanpi, asinpi, acospi, atanpi, atan2pi, sincos
        ,Function{Float,    "sin", {"x"    }}
        ,Function{Float,    "cos", {"x"    }}
        ,Function{Float,    "tan", {"x"    }}
        ,Function{Float,   "asin", {"x"    }}
        ,Function{Float,   "acos", {"x"    }}
        ,Function{Float,   "atan", {"x"    }}
        ,Function{Float,  "atan2", {"x","y"}}
        ,Function{Float,  "sinpi", {"x"    }, STR(return sinCSUFFIX((TYPE)M_PI*x);)}
        ,Function{Float,  "cospi", {"x"    }, STR(return cosCSUFFIX((TYPE)M_PI*x);)}
        ,Function{Float,  "tanpi", {"x"    }, STR(return tanCSUFFIX((TYPE)M_PI*x);)}
        ,Function{Float, "asinpi", {"x"    }, STR(return asinCSUFFIX(x)/(TYPE)M_PI;)}
        ,Function{Float, "acospi", {"x"    }, STR(return acosCSUFFIX(x)/(TYPE)M_PI;)}
        ,Function{Float, "atanpi", {"x"    }, STR(return atanCSUFFIX(x)/(TYPE)M_PI;)}
        ,Function{Float,"atan2pi", {"x","y"}, STR(return atan2CSUFFIX(x,y)/(TYPE)M_PI;)}
        //TODO: sincos
        //Hyperbolic: sinh, cosh, tanh, asinh, acosh, atanh
        ,Function{Float,  "sinh", {"x"}}
        ,Function{Float,  "cosh", {"x"}}
        ,Function{Float,  "tanh", {"x"}}
        ,Function{Float, "asinh", {"x"}}
        ,Function{Float, "acosh", {"x"}}
        ,Function{Float, "atanh", {"x"}}
        //Error and gamma: erf, erfc, tgamma, lgamma, lgamma_r
        ,Function{Float,    "erf", {"x"}}
        ,Function{Float,   "erfc", {"x"}}
        ,Function{Float, "tgamma", {"x"}}
        ,Function{Float, "lgamma", {"x"}}
        ,Function{Float, "lgamma_r", {"x", "int* signp"}}
        //Rounding: ceil, floor, trunc, round, rint, fract
        ,Function{Float,  "ceil", {"x"}}
        ,Function{Float, "floor", {"x"}}
        ,Function{Float, "trunc", {"x"}}
        ,Function{Float, "round", {"x"}}
        //TODO: rint
        //TODO: fract
        //Floating-point manipulation: frexp, ldexp, modf, ilogb, logb, nextafter, copysign
        //TODO: frexp
        //TODO: ldexp
        //TODO: modf
        //TODO: ilogb
        ,Function{Float,      "logb", {"x"        }}
        ,Function{Float, "nextafter", {"from","to"}}
        ,Function{Float,  "copysign", {"x"   ,"y" }}
        //Extra: clampi
        ,{Integer, "clampi", {"val", "min", "max"}, STR(return (val<min) ? min : ((val>max) ? max : val);), STR(return (val<min) ? min : ((val>max) ? max : val);)}
    };
}

#undef STR

const std::vector<Function>& get_functions() {
    return functions;
}
