///////////////////////////////////////////////////////////////////////////////
// NAME:            iterator.h
//
// AUTHOR:          Ethan D. Twardy <ethan.twardy@gmail.com>
//
// DESCRIPTION:     Iterators for containers
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

#ifndef SEASTAR_ITERATOR_H
#define SEASTAR_ITERATOR_H

#include <stdlib.h>

union IteratorState {
    size_t size;
    void *pointer;
};

typedef void *NextFn(void *, union IteratorState *);

// The iterator is more-or-less just a vtable. Don't attempt to edit fields of
// this struct. Iterators can be created on the stack and destroyed
// automatically since they do not allocate any memory. If the container they
// reference goes out of scope, though, they are no longer valid.
typedef struct Iterator {
    // NO USER CUSTOMIZABLE FIELDS
    NextFn *next;
    void *private;
    union IteratorState state;
} Iterator;

// Return the next element in this iterator
void *cs_iter_next(Iterator *iterator);

#endif // SEASTAR_ITERATOR_H

///////////////////////////////////////////////////////////////////////////////
