#!/bin/bash

set -e  # Exit if any command fails

rm -f program *.gcda *.gcno *.gcov

g++ -fprofile-arcs -ftest-coverage -o program code.cpp

echo "Running program with input.txt..."
./program < input.txt > output.txt


if [ ! -f program-code.gcda ]; then
    echo "Error: No coverage data generated. Ensure the program runs correctly."
    exit 1
fi


gcov -o . program-code.cpp > /dev/null 2>&1  # Suppress extra output


if find . -name "*.gcov" | grep -q .; then
    echo "Generated .gcov files:"
    find . -name "*.gcov"
else
    echo "Warning: .gcov file not found!"
fi

echo ""
echo "Coverage Summary Table..."
gcovr --branches --txt --exclude '/usr/' --keep  # Keep .gcov files



