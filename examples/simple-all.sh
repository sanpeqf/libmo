#!/bin/sh
for path in $(find "examples/simple-mo" -name "*.mo"); do
    file=$(basename "$path")
    LANG="${file%.*}" examples/simple
done
