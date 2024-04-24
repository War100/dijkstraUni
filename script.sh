#!/bin/bash

# Define the program's source code file
source_code="dijkstra.cpp"

# Define the output directory for compiled binaries
bin_dir="bin"

# Define the list of optimization levels to test
optimization_levels="-O0 -O1 -O2 -O3 -Os"

# Function to compile the program with a specified optimization level
compile_with_opt() {
    opt_level="$1"
    out_file="$bin_dir/prog_$opt_level"

    # Create the output directory if it doesn't exist
    mkdir -p "$bin_dir"

    # Compile the program with the specified optimization level
    gcc -lstdc++ -o "$out_file" "$source_code" $opt_level

    # Measure the execution time using 'time'
    time ./"$out_file"
}

# Function to get CPU supported extensions
get_cpu_extensions() {
    # Use the 'cat' command to read the contents of '/proc/cpuinfo'
    cpuinfo=$(cat /proc/cpuinfo)

    # Extract supported extensions using regular expressions
    supported_extensions=$(grep -E 'flags: *(SSE2|AVX|AVX2|AVX512F)' <<< "$cpuinfo" | sed 's/flags: //g' | tr '\n' ' ')

    echo "$supported_extensions"
}

# Get CPU supported extensions
supported_extensions=$(get_cpu_extensions)

# Print the list of supported extensions
echo "Supported CPU extensions: $supported_extensions"

# Compile and time the program with different optimization levels
for opt_level in $optimization_levels; do
    echo "Optimization level: $opt_level"
    compile_with_opt $opt_level
done

# Compile and time the program with each supported extension
for extension in $supported_extensions; do
    echo "Optimization with extension: $extension"
    gcc -lstdc++ -o "$bin_dir/prog_$extension" "$source_code" -march=$extension -mtune=$extension
    time ./"$bin_dir/prog_$extension"
done

