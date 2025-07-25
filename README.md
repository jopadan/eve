<img src="https://github.com/jfalcou/eve/raw/main/doc/logo.png" alt="" data-canonical-src="https://github.com/jfalcou/eve/raw/main/doc/logo.png" align="left"  width="15%" height="15%" />

# EVE - the Expressive Vector Engine

[![Licence](https://img.shields.io/github/license/jfalcou/eve?style=plastic)](https://img.shields.io/github/license/jfalcou/eve?style=plastic)
[![Discord](https://img.shields.io/discord/692734675726237696?style=plastic)](https://discord.gg/8A4Q4HkhcW)

## Purpose

EVE is a re-implementation of the old EVE SIMD library by Falcou et al., which for a while was
named Boost.SIMD. It's a C++20 and onward implementation of a type-based wrapper around
SIMD extensions sets for most current architectures. It aims to show how C++20 can be used
to design and implement an efficient, low-level, high-abstraction library suited for high performance.

It's a research project first and an open-source library second. We reserve the right to
change the API and baseline compiler required until the first official 0.1 release. However, we'll try
to minimise disruption. Semantic versioning will ensure API retro-compatibility if anything huge
needs to change.

## Getting Started

 - [Installing and using the library](https://jfalcou.github.io/eve/setup.html)
 - [Your first SIMD code using EVE](https://jfalcou.github.io/eve/intro-01.html)
 - [The complete set of EVE tutorials](https://jfalcou.github.io/eve/usergroup1.html)
 - [References Documentation](https://jfalcou.github.io/eve/usergroup4.html)

## Video materials

### SIMD in C++20: EVE of a new Era - CppCon 2021

[![SIMD in C++20: EVE of a new Era - CppCon 2021](http://img.youtube.com/vi/WZGNCPBMInI/0.jpg)](http://www.youtube.com/watch?v=WZGNCPBMInI "Video Title")

### SIMD Algorithms Design

[![Playlist by Denis Yaroshevskiy](http://img.youtube.com/vi/U1e_k8xmwR0/0.jpg)](https://www.youtube.com/playlist?list=PLYCMvilhmuPEM8DUvY6Wg_jaSFHpmlSBD)

## Current status - Operational

EVE is considered **operational**: it's usable and has a large feature set for a sensible number of instruction sets. However, some values or performance issues may still remain. Don't hesitate to report any funky code generation or bad optimisations so we can deliver the best performance around.

### Current roster of supported Instruction Sets

In terms of SIMD extension sets, we actively support (ie code is optimised and regularly tested) the following:

Full support with tests:
  - **Intel**
    - SSE2, SSSE3, SSE3, SSE4.1, SSE4.2
    - AVX, AVX2, FMA3
    - AVX512 in Skylake-AVX512 mode (F, CD, VL, DQ, BW)
  - **ARM**
    - NEON A32 (64 & 128 bits)
    - NEON A64 (64 & 128 bits)
    - ASIMD
    - SVE with fixed sizes of 128, 256 and 512 bits registers.

Partial/In-progress support with minimal checks:
  - **PowerPC**
    - VMX
    - VSX

We **do not support** ARM SVE with **dynamic size** or GPGPU; this is the job of another tool.

### Current roster of supported compilers

EVE requires a C++20-compliant compiler. The main features from C++17/20 we require are:
 - Concepts and requires
 - Template lambdas
 - Inline variables
 - Non-Type Template Parameters
 - `if constexpr`
 - Functions from `<bits>`

Here is the current minimal compiler version supported:

| Compiler       | Version       |
| -------------- | ------------- |
| g++            | 13 or above   |
| clang++        | 16 or above   |
| Visual Studio  | *TBD*         |

Visual Studio support is currently being added.

The current **recommended** compiler version are:

| Compiler       | Version       |
| -------------- | ------------- |
| g++            | 14 or above   |
| clang++        | 19 or above   |

## FAQ

 - **Why C++20 ?** We want to be able to use modern design components like Concepts and, later, Modules. C++14 is for 2014.
   We fully know it may hinder adoption in some situations, but we're not running a race. We value proper design and API choice over
   complex retro-compatibility.

 - **Why this instead of std::simd or any other libraries?** EVE is a playground for testing proper
   design and implementation decisions for such libraries. Vc and its standard version are fine work, 
   but we aim to push the envelope regarding API and implementation without standard
   restrictions. We will try to keep up with standard naming as much as possible.

 - **Is this Boost.SIMD v42.69?** Yes and no. This reimplementation is based on slightly different
   premises and some radical new ideas. Our previous Boost exhibited all results.SIMD papers
   still hold, and we'll try to improve upon.

 - **I want to help!** That's Good. We need tests on exotic configurations, maybe a stable PPC test machine.
   Write code, make it fail, and fork and hack away. This will allow us to improve for use cases we may have missed.
   We would also value input (even harsh ones) on how we use our CI infrastructure or how our CMake looks.
   We tried our best, but those elements are complex all by themselves.

## Bibliographic References

If you want to refer to EVE, you can use those papers (by order of preference in citation).
A new, more up-to-date EVE-specific journal paper is in the works at the moment.

 - **Modern Generative Programming for Optimizing Small Matrix-Vector Multiplication**, Jules Penuchot, Joel Falcou, Amal Khabou in *HPCS 2018*
 - **Boost. simd: generic programming for portable simdization**, Pierre Estérie, Joel Falcou, Mathias Gaunard, Jean-Thierry Lapresté, *PACT 2012*
 - **EVE, an object oriented SIMD library**, Joel Falcou, Jocelyn Serot in *Scalable Computing: Practice and Experience 6 (4)*

 ## License

```
Boost Software License

Copyright: EVE Project Contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
