###############################################################################
# NAME:             meson.build
#
# AUTHOR:           Ethan D. Twardy <ethan.twardy@gmail.com>
#
# DESCRIPTION:      Build script for the library
#
# CREATED:          11/13/2021
#
# LAST EDITED:      11/13/2021
#
# Copyright 2021, Ethan D. Twardy
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
###

project('libseastar', 'c', version: '0.1.0')

seastar_files = files([
  'libseastar/error.c',
  'libseastar/iterator.c',
  'libseastar/pqueue.c',
  'libseastar/vector.c',
])

libseastar = static_library(
  'seastar',
  sources: seastar_files,
  c_args: ['-Wall', '-Wextra', '-Os'],
  install: true,
)

install_headers(
  'libseastar/error.h',
  'libseastar/iterator.h',
  'libseastar/pqueue.h',
  'libseastar/result.h',
  'libseastar/vector.h',
  subdir: 'libseastar',
)

pkgconfig = import('pkgconfig')
pkgconfig.generate(libseastar, filebase: 'libseastar')

executable(
  'seastar_test',
  'test/main.c',
  c_args: ['-Wall', '-Wextra'],
  include_directories: ['libseastar'],
  link_with: [libseastar],
)

###############################################################################
