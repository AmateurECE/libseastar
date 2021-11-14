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

#include <stdarg.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include <libseastar/pqueue.h>
#include <libseastar/vector.h>

void assert(bool test, const char *message, ...) {
    va_list argument_list;
    va_start(argument_list, message);
    if (!test) {
        char *formatted_message = NULL;
        int result = vasprintf(&formatted_message, message, argument_list);
        if (-1 == result) {
            fprintf(stderr, "Out of memory!");
            exit(2);
        }
        fprintf(stderr, "%s\n", formatted_message);
        free(formatted_message);
        exit(1);
    }
}

void print_int_vector(Vector *vector) {
    if (vector->size > 0) {
        printf("%d", *(int *)vector->container[0]);
    }
    for (size_t i = 1; i < vector->size; ++i) {
        printf(" %d", *(int *)vector->container[i]);
    }
    printf("\n");
}

void test_vector() {
    Vector vector;
    cs_vector_init(&vector);
    int datum = 12;
    const size_t index = 0;
    IndexResult index_result = cs_vector_push_back(&vector, &datum);
    assert(index_result.ok, "cs_vector_push_back did not return ok");
    assert(index == index_result.value,
        "cs_vector_push_back did not return the correct value");
    assert(vector.size == 1, "vector size is wrong");

    PointerResult pointer_result = cs_vector_get(&vector, index);
    assert(pointer_result.ok, "cs_vector_get did not return .ok");
    assert(*(int *)pointer_result.value == datum,
        "cs_vector_get did not return the correct value");

    Iterator vector_iter = cs_vector_iter(&vector);
    assert(*(int *)cs_iter_next(&vector_iter) == datum,
        "cs_iter_next did not return the correct value");
    assert(NULL == cs_iter_next(&vector_iter),
        "cs_iter_next did not return NULL");

    pointer_result = cs_vector_remove(&vector, 0);
    assert(pointer_result.ok, "cs_vector_remove failed");
    assert(*(int *)pointer_result.value == datum,
        "cs_vector_remove returned the wrong element");
    assert(vector.size == 0, "vector size is wrong");

    cs_vector_free(&vector);
}

int example_comparator(const void *one, const void *two) {
    int first = **(int **)one;
    int second = **(int **)two;
    if (first > second) {
        return 1;
    } else if (first == second) {
        return 0;
    } else {
        return -1;
    }
}

void test_pqueue() {
    PriorityQueue pqueue;
    cs_pqueue_init(&pqueue, example_comparator);
    int first = 12, second = 8, third = 26;

    IndexResult index_result = cs_pqueue_push(&pqueue, &first);
    assert(index_result.ok, "cs_pqueue_push returned error");
    assert(1 == index_result.value,
        "line %d: cs_pqueue_push, expected=%d, got=%d", __LINE__, 1,
        index_result.value);
    assert(1 == pqueue.container.size, "Pqueue has wrong size");

    index_result = cs_pqueue_push(&pqueue, &second);
    assert(index_result.ok, "cs_pqueue_push returned error");
    assert(2 == index_result.value, "cs_pqueue_push returned wrong size");
    assert(2 == pqueue.container.size, "Pqueue has wrong size");

    index_result = cs_pqueue_push(&pqueue, &third);
    assert(index_result.ok, "cs_pqueue_push returned error");
    assert(3 == index_result.value, "cs_pqueue_push returned wrong size");
    assert(3 == pqueue.container.size, "Pqueue has wrong size");

    PointerResult pointer_result = cs_pqueue_peek(&pqueue);
    assert(pointer_result.ok, "cs_pqueue_peek returned error");
    assert(*(int *)pointer_result.value == second,
        "line %d: cs_pqueue_peek, expected=%d, got=%d", __LINE__, second,
        *(int *)pointer_result.value);

    pointer_result = cs_pqueue_pop(&pqueue);
    assert(pointer_result.ok, "cs_pqueue_pop returned error");
    assert(*(int *)pointer_result.value == second,
        "cs_pqueue_pop returned wrong value");

    pointer_result = cs_pqueue_pop(&pqueue);
    assert(pointer_result.ok, "cs_pqueue_pop returned error");
    assert(*(int *)pointer_result.value == first,
        "cs_pqueue_pop returned wrong value");
    assert(1 == pqueue.container.size, "Pqueue has wrong size!");
}

int main() {
    test_vector();
    test_pqueue();
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
