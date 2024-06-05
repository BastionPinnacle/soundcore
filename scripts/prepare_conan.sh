#!/bin/bash

# Check the number of command-line arguments
if [ "$#" -ne 3 ]; then
    echo "prepare_conan.sh <source-directory> <build-directory> <build-type>"
else
      conan install $1 -s:a compiler=gcc -s:a compiler.version=11 -s:a compiler.cppstd=20 \
      -s:a build_type=$3  -c:a tools.system.package_manager:mode=install --build=missing -of $2
fi