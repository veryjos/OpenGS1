#!/bin/sh
find . | grep -E ".*\.(cpp|hpp)" | xargs clang-format -i -style=file
