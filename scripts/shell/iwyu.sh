#!/bin/bash

# Set the output file
OUTPUT_FILE="scripts/shell/out/iwyu.out"

# Get the directory of the output file
OUTPUT_DIR=$(dirname "$OUTPUT_FILE")

# Check if the directory exists, if not, create it
if [ ! -d "$OUTPUT_DIR" ]; then
    mkdir -p "$OUTPUT_DIR"
fi

# Specify the directory to check
SOURCE_DIR="servers common tests"

# Build the find command to search for .cpp and .h files in the specified directory
FIND_CMD="find $SOURCE_DIR -name '*.cpp' -o -name '*.h'"

# Execute the find command and store the result in SOURCE_FILES
SOURCE_FILES=$(eval $FIND_CMD)

# Clear the output file if it exists
>$OUTPUT_FILE

# Check for the --verbose option
VERBOSE=false
if [ "$1" = "--verbose" ]; then
    VERBOSE=true
fi

# Run IWYU on each source file and append the output to the output file
for FILE in $SOURCE_FILES; do
    # echo "Processing $FILE"
    if [ "$VERBOSE" = true ]; then
        include-what-you-use $FILE | tee -a $OUTPUT_FILE # TODO: 头文件查询错误，以及会递归查找检查引用的头文件
    else
        include-what-you-use $FILE >>$OUTPUT_FILE 2>&1
    fi
done

echo "IWYU analysis complete. Results saved to $OUTPUT_FILE."
