#!/bin/bash
SRC_DIR="."
INCLUDE_DIRS="-I$SRC_DIR -I .."
SOURCES="$SRC_DIR/main.c ../file_impl.c "
OUTPUT_DIR="bin"
OUTPUT_FILE="test_app"

mkdir -p $OUTPUT_DIR

clang $INCLUDE_DIRS $SOURCES -o $OUTPUT_DIR/$OUTPUT_FILE

if [ $? -ne 0 ]; then
    echo "Compilation failed."
else
    # Cleanup object files
    rm -f *.o
    rm -f *.obj

    cd $OUTPUT_DIR
    ./test_app
fi
