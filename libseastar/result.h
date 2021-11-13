///////////////////////////////////////////////////////////////////////////////
// NAME:            result.h
//
// AUTHOR:          Ethan D. Twardy <ethan.twardy@gmail.com>
//
// DESCRIPTION:     The "Result" container is a struct combining a status code
//                  with a datum.
//
// CREATED:         11/13/2021
//
// LAST EDITED:     11/13/2021
//
// Copyright 2021, Ethan D. Twardy
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
////

#ifndef SEASTAR_RESULT_H
#define SEASTAR_RESULT_H

#include <stdbool.h>
#include <stddef.h>

// Result type containing a standard void* datum if .ok
typedef struct PointerResult {
    bool ok;
    union {
        void *value;
        int error;
    };
} PointerResult;

// Result type only containing error information--error is only set if !.ok
typedef struct VoidResult {
    bool ok;
    int error;
} VoidResult;

// Result type containing an index
typedef struct IndexResult {
    bool ok;
    union {
        size_t value;
        int error;
    };
} IndexResult;

#endif // SEASTAR_RESULT_H

///////////////////////////////////////////////////////////////////////////////
