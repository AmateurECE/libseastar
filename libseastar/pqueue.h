///////////////////////////////////////////////////////////////////////////////
// NAME:            pqueue.h
//
// AUTHOR:          Ethan D. Twardy <ethan.twardy@gmail.com>
//
// DESCRIPTION:     Priority Queue implementation
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

#ifndef SEASTAR_PQUEUE_H
#define SEASTAR_PQUEUE_H

#include <libseastar/iterator.h>
#include <libseastar/result.h>
#include <libseastar/vector.h>

// This function needs to return which of the two pointers has a higher
// priority. Note that the container doesn't care whether this comparison
// yields the higher of the two, or the lower, as long as behavior is
// consistent. Also, note that this signature is required for the purposes of
// the sorting function, but the arguments and return type are really void**.
typedef int ComparisonFn(const void *, const void *);

// PriorityQueue: Sorts elements upon insertion/deletion. As of right now, the
// sorting algorithm chosen is not stable. Also is implemented using a vector,
// which may change in the future.
typedef struct PriorityQueue {
    // USER CUSTOMIZABLE FIELDS
    ComparisonFn *comparator;

    // NON USER CUSTOMIZABLE FIELDS
    Vector container;
} PriorityQueue;

// Initialize a queue
VoidResult cs_pqueue_init(PriorityQueue *queue, ComparisonFn *comparator);

// Push a new element into the queue (requires a sort), return new queue size
IndexResult cs_pqueue_push(PriorityQueue *queue, void *user_data);

// Peek at the queue
PointerResult cs_pqueue_peek(PriorityQueue *queue);

// Pop the next element from the queue
PointerResult cs_pqueue_pop(PriorityQueue *queue);

// Explicitly sort the queue
void cs_pqueue_sort(PriorityQueue *queue);

// Free internally allocated memory
void cs_pqueue_free(PriorityQueue *queue);

// Create an iterator for the priority queue
Iterator cs_pqueue_iter(PriorityQueue *queue);

#endif // SEASTAR_PQUEUE_H

///////////////////////////////////////////////////////////////////////////////
