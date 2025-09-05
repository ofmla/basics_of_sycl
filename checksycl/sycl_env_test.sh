#!/usr/bin/env bash

# clear and clean
clear
rm -f CMakeLists.txt src/CMakeLists.txt
rm -rf build

# copy the CMakeLists.txt files
implem=$1
shift
cp -f ../cmake/CMakeLists.${implem}.txt CMakeLists.txt 
cp -f ../cmake/CMakeLists.src.txt src/CMakeLists.txt

# run cmake
echo
mkdir -p build
cd build
cmake -DCMAKE_VERBOSE_MAKEFILE=TRUE ..

# run make
echo
make all

# run the project
echo
./env_setup_test.exe $*

# fin
echo
