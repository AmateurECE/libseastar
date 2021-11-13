///////////////////////////////////////////////////////////////////////////////
// NAME:            vector.c
//
// AUTHOR:          Ethan D. Twardy <ethan.twardy@gmail.com>
//
// DESCRIPTION:     Implementation of the vector container
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

#include <errno.h>
#include <stdlib.h>

#include <libseastar/vector.h>

///////////////////////////////////////////////////////////////////////////////
// Private Interface
////

// Resize the vector, returning the new size
IndexResult priv_vector_resize(Vector *vector) {
    size_t new_size = vector->expander(vector->capacity);
    void **new_container =
        realloc(vector->container, new_size * sizeof(void *));

    // 1. Realloc fails--old memory block is untouched
    if (NULL == new_container) {
        return (IndexResult){.ok = false, .error = VECTOR_ERRNO_SET | errno};
    } else if (new_container != vector->container) {
        vector->container = new_container;
    }

    return (IndexResult){.ok = true, .value = vector->size};
}

///////////////////////////////////////////////////////////////////////////////
// Public Interface
////

///////////////////////////////////////////////////////////////////////////////
// FUNCTION:        cs_vector_default_expansion_function
//
// DESCRIPTION:     Default expansion function
//
// ARGUMENTS:       n: Current capacity of vector
//
// RETURN:          2 * n
////
size_t cs_vector_default_expansion_function(size_t n) { return 2 * n; }

///////////////////////////////////////////////////////////////////////////////
// FUNCTION:        cs_vector_init
//
// DESCRIPTION:     Initialize the vector with the default size
//
// ARGUMENTS:       none
//
// RETURN:          none
////
VoidResult cs_vector_init(Vector *vector) {
    vector->size = 0;
    vector->capacity = CS_VECTOR_DEFAULT_SIZE;
    vector->container = calloc(vector->capacity, sizeof(void *));
    if (NULL == vector->container) {
        return (VoidResult){.ok = false, .error = errno};
    }

    return (VoidResult){.ok = true, 0};
}

///////////////////////////////////////////////////////////////////////////////
// FUNCTION:        cs_vector_get
//
// DESCRIPTION:     Return a pointer to the vector element at index.
//
// ARGUMENTS:       index: index of the element to get
//
// RETURN:          PointerResult, with data set to pointer to element if ok.
////
PointerResult cs_vector_get(Vector *vector, size_t index) {
    if (index >= vector->size) {
        return (PointerResult){.ok = false, .error = VECTOR_INVALID_INDEX};
    }

    return (PointerResult){.ok = true, .value = vector->container[index]};
}

///////////////////////////////////////////////////////////////////////////////
// FUNCTION:        cs_vector_set
//
// DESCRIPTION:     Insert user_data at the specified index in the array. Will
//                  not attempt to resize the vector if index is out of bounds,
//                  instead will just return VECTOR_INVALID_INDEX. This
//                  container is non-owning, meaning it performs no memory
//                  management. i.e., if there is already an allocated datum
//                  at the specified index, it may result in a memory leak.
//
// ARGUMENTS:       index: The index to insert the data into.
//                  user_data: The data to insert.
//
// RETURN:          VoidResult
////
VoidResult cs_vector_set(Vector *vector, size_t index, void *user_data) {
    if (index >= vector->size) {
        return (VoidResult){.ok = false, .error = VECTOR_INVALID_INDEX};
    }

    vector->container[index] = user_data;
    return (VoidResult){.ok = true, 0};
}

///////////////////////////////////////////////////////////////////////////////
// FUNCTION:        cs_vector_push_back
//
// DESCRIPTION:     Attempt to push the element back onto the vector, returning
//                  the index of the element on success.
//
// ARGUMENTS:       user_data: The datum to push back onto the vector.
//
// RETURN:          IndexResult containing index of new element on success.
////
IndexResult cs_vector_push_back(Vector *vector, void *user_data) {
    if (vector->size >= vector->capacity) {
        IndexResult result = priv_vector_resize(vector);
        if (!result.ok) {
            return result;
        }
    }

    vector->container[vector->size++] = user_data;
    return (IndexResult){.ok = true, .value = vector->size - 1};
}

///////////////////////////////////////////////////////////////////////////////
// FUNCTION:        cs_vector_free
//
// DESCRIPTION:     De-initialize the vector, freeing any internally-allocated
//                  resources. Note that this does not assume any allocation
//                  scheme for data contained in the vector, so if data remains
//                  in the vector, this may result in a memory leak.
//
// ARGUMENTS:       none
//
// RETURN:          none
////
void cs_vector_free(Vector *vector) {
    if (NULL != vector->container) {
        free(vector->container);
        vector->container = NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////
