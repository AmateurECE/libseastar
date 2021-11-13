# C*, a light C library providing basic idioms

This library contains some programming idioms in C that I happen to find myself
rewriting on every codebase. It's statically linked, because I don't want this
to be a transitive dependency on any consumers of anything else I write.

## Modules Provided

1. `Vector`: Non-owning array-based container that automatically expands using
