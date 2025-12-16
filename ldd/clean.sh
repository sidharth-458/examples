#!/bin/bash

BASE_DIR="${1:-.}"

for dir in "$BASE_DIR"/*/; do
    [ -d "$dir" ] || continue

    if [ -f "$dir/Makefile" ] || [ -f "$dir/makefile" ]; then
        echo "Running make clean in $dir"
        (cd "$dir" && make clean)
    else
        echo "Skipping $dir (no Makefile)"
    fi
done

