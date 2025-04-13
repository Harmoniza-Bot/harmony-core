#!/usr/bin/env bash

find ./{include,sources}/ -type f -name "*.hpp" -o -name "*.cpp" | clang-format --verbose --style=file -i --files=/dev/stdin
