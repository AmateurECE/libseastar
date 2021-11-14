///////////////////////////////////////////////////////////////////////////////
// NAME:            pqueue.c
//
// AUTHOR:          Ethan D. Twardy <ethan.twardy@gmail.com>
//
// DESCRIPTION:     Implementation of the pqueue.
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

#include <libseastar/pqueue.h>
#include <libseastar/error.h>

///////////////////////////////////////////////////////////////////////////////
// Public Interface
////

///////////////////////////////////////////////////////////////////////////////
// FUNCTION:        cs_pqueue_init
//
// DESCRIPTION:     Initialize a priority queue with the given comparator
//
// ARGUMENTS:       comparator: A comparison function for sorting elements
//
// RETURN:          VoidResult
////
VoidResult cs_pqueue_init(PriorityQueue* queue, ComparisonFn* comparator) {
    queue->comparator = comparator;
    return cs_vector_init(&queue->container);
}

///////////////////////////////////////////////////////////////////////////////
// FUNCTION:        cs_pqueue_push
//
// DESCRIPTION:     Push a new element into the queue (requires a sort)
//
// ARGUMENTS:       user_data: Data to insert into the queue
//
// RETURN:          IndexResult containing the new size of the queue.
////
IndexResult cs_pqueue_push(PriorityQueue* queue, void* user_data) {
    IndexResult result = cs_vector_push_back(&queue->container, user_data);
    if (!result.ok) {
        return result;
    }

    cs_pqueue_sort(queue);
    return (IndexResult){.ok=true, .value=queue->container.size};
}

///////////////////////////////////////////////////////////////////////////////
// FUNCTION:        cs_pqueue_peek
//
// DESCRIPTION:     Peek at the queue
//
// ARGUMENTS:       none
//
// RETURN:          PointerResult containing the next element to be popped.
////
PointerResult cs_pqueue_peek(PriorityQueue* queue) {
    if (queue->container.size > 0) {
        return cs_vector_get(&queue->container, 0);
    }

    return (PointerResult){.ok=false, .error=SEASTAR_ERROR_INVALID_INDEX};
}

///////////////////////////////////////////////////////////////////////////////
// FUNCTION:        cs_pqueue_pop
//
// DESCRIPTION:     Pop the next element from the queue
//
// ARGUMENTS:       none
//
// RETURN:          PointerResult containing the popped element
////
PointerResult cs_pqueue_pop(PriorityQueue* queue) {
    return cs_vector_remove(&queue->container, 0);
}

///////////////////////////////////////////////////////////////////////////////
// FUNCTION:        cs_pqueue_sort
//
// DESCRIPTION:     Explicitly sort the pqueue (e.g. after updating all the
//                  elements via an iterator).
//
// ARGUMENTS:       none
//
// RETURN:          none
////
void cs_pqueue_sort(PriorityQueue* queue) {
    qsort((void*)queue->container.container, queue->container.size,
        sizeof(void*), queue->comparator);
}

///////////////////////////////////////////////////////////////////////////////
// FUNCTION:        cs_pqueue_free
//
// DESCRIPTION:     Free internally allocated memory for the queue.
//
// ARGUMENTS:       none
//
// RETURN:          none
////
void cs_pqueue_free(PriorityQueue* queue) {
    cs_vector_free(&queue->container);
}

///////////////////////////////////////////////////////////////////////////////
// FUNCTION:        cs_pqueue_iter
//
// DESCRIPTION:     Create an iterator to iterate over elements of the queue
//
// ARGUMENTS:       none
//
// RETURN:          Iterator
////
Iterator cs_pqueue_iter(PriorityQueue* queue) {
    return cs_vector_iter(&queue->container);
}

///////////////////////////////////////////////////////////////////////////////
