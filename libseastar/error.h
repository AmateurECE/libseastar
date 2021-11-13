///////////////////////////////////////////////////////////////////////////////
// NAME:            error.h
//
// AUTHOR:          Ethan D. Twardy <ethan.twardy@gmail.com>
//
// DESCRIPTION:     Error handling for the library
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

#ifndef SEASTAR_ERROR_H
#define SEASTAR_ERROR_H

// These error codes can be used to determine the problem. If a system error
// occurs, the value of result.error will be VECTOR_ERRNO_SET | errno, so an
// error string can be extracted in the following way:
//  if (result.error & VECTOR_ERRNO_SET) {
//      const char* message = strerror(result.error ^ VECTOR_ERRNO_SET);
//  }
enum SeaStarError {
    SEASTAR_ERRNO_SET = 1 << 16,           // errno is set in this result
    SEASTAR_ERROR_INVALID_INDEX = 2 << 16, // Attempt access on invalid index
};

const char *cs_strerror(enum SeaStarError);

#endif // SEASTAR_ERROR_H

///////////////////////////////////////////////////////////////////////////////
