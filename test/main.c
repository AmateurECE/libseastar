///////////////////////////////////////////////////////////////////////////////
// NAME:            main.c
//
// AUTHOR:          Ethan D. Twardy <ethan.twardy@gmail.com>
//
// DESCRIPTION:     Test entrypoint
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

#include <stdio.h>
#include <stdlib.h>

#include <libseastar/vector.h>

void assert(bool test, const char* message) {
    if (!test) {
        fprintf(stderr, "%s\n", message);
        exit(1);
    }
}

int main() {
    Vector vector;
    cs_vector_init(&vector);
    int datum = 12;
    const size_t index = 0;
    IndexResult index_result = cs_vector_push_back(&vector, &datum);
    assert(index_result.ok, "cs_vector_push_back did not return ok");
    assert(index == index_result.value,
        "cs_vector_push_back did not return the correct value");

    PointerResult pointer_result = cs_vector_get(&vector, index);
    assert(pointer_result.ok, "cs_vector_get did not return .ok");
    assert(*(int*)pointer_result.value == datum,
        "cs_vector_get did not return the correct value");
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
