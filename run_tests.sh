#!/usr/bin/bash

echo "Running Tests " `date`

cmake -B build tests >/dev/null
cmake --build build --parallel >/dev/null
ctest --test-dir build --output-on-error