///////////////////////////////////////////////////////////////////////////////
// NAME:            vector.h
//
// AUTHOR:          Ethan D. Twardy <ethan.twardy@gmail.com>
//
// DESCRIPTION:     An array-based container that expands dynamically
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

#ifndef SEASTAR_VECTOR_H
#define SEASTAR_VECTOR_H

#include <stddef.h>

#include <libseastar/iterator.h>
#include <libseastar/result.h>

static const size_t CS_VECTOR_DEFAULT_SIZE = 10;

// A function that determines how much to expand the vector given its current
// capacity. Can be used to override the default behavior.
typedef size_t ExpansionFunction(size_t n);

// These error codes can be used to determine the problem. If a system error
// occurs, the value of result.error will be VECTOR_ERRNO_SET | errno, so an
// error string can be extracted in the following way:
//  if (result.error & VECTOR_ERRNO_SET) {
//      const char* message = strerror(result.error ^ VECTOR_ERRNO_SET);
//  }
enum VectorError {
    VECTOR_ERRNO_SET = 1 << 16,     // errno is set in this result
    VECTOR_INVALID_INDEX = 2 << 16, // Attempted access on invalid index
};

// The default expansion function
size_t cs_vector_default_expansion_function(size_t n);

// Vector struct
typedef struct Vector {
    // USER CUSTOMIZABLE
    ExpansionFunction *expander;

    // NOT USER CUSTOMIZABLE
    size_t size;
    size_t capacity;
    void **container;
} Vector;

// Initialize a vector
VoidResult cs_vector_init(Vector *vector);

// Get/set values
PointerResult cs_vector_get(Vector *vector, size_t index);
VoidResult cs_vector_set(Vector *vector, size_t index, void *user_data);

// Push the data onto the back of the vector, expanding if necessary.
IndexResult cs_vector_push_back(Vector *vector, void *user_data);

// De-initialize the vector
void cs_vector_free(Vector *vector);

// Iterator function
Iterator cs_vector_iter(Vector *vector);

#endif // SEASTAR_VECTOR_H

///////////////////////////////////////////////////////////////////////////////
