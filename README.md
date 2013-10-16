
What is libsimdpp
=================

libsimdpp is a header-only zero-overhead C++ wrapper around single-instruction
multiple-data (SIMD) intrinsics found in many compilers. Large subsets of
several SIMD instruction sets are supported via a single interface. Where
reasonable, the differences between the instruction sets are resolved by
implementing missing instructions in terms of a combination of other
instructions.

The library implements a lot of additional, commonly used functionality -
various variants of matrix transpositions, interleaving loads/stores, optimized
compile-time shuffling instructions, etc. Each of these are implemented in the
most efficient manner for the target instruction set.

The library sits somewhere in the middle between programming directly in
intrinsics and even higher-level SIMD libraries. As much control as possible
is given to the developer, so that it's possible to exactly predict what code
the compiler will generate.

Supported instruction sets
==========================

The library supports NEON and SSE2-AVX2 instruction sets. The library presents
a common interface for all those instruction sets in the simdpp:: namespace.
Some instruction set specific intrinsics are available in simdpp::sse:: or
simdpp::neon:: namespaces. However, a lot of domain-specific instructions are
not wrapped at all, the original intrinsics must be used for these.

The actual instruction set is selected at compile time by including appropriate
header. A single executable can include the library several times each time
specifying different target instruction set. The library thus may allow easier
implementation of a dynamic dispatch mechanism while using the same source
code. See the implementation of tests for an example of generation of object
files for different instruction sets from the same source code.

The support for AVX and AVX2 instruction sets is not complete. In particular,
interleaving loads and stores are not implemented yet.

Documentation
=============

Online documentation is provided at http://p12tic.github.io/libsimdpp/doc/html

64-bit floats on ARM
====================

On ARM systems 64 bit floating point support is provided only in scalar VFP
core. To make matters worse, the transition between the VFP and NEON
instruction sets is very expensive, so the traditional vector processing idioms
(such as performing IF by ANDNOT, AND and OR) can not be used. The intrinsics
are thus implemented in a way that helps the compiler to "devectorize" all such
masking operations back to regular IF statements. In this way, the same
interface can be used to perform 64-bit floating point math in both NEON VFP
and other instruction sets.

Usage
=====

To use the library, include appropriate header from the simdpp/ directory. It
will pull the rest of the library in.

A C++11-aware compiler is required in order to use the library.

License
=======

The library is distributed under two-clause BSD license:

    Copyright (C) 2011-2013  Povilas Kanapickas tir5c3@yahoo.co.uk
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
