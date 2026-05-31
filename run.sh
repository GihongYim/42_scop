#!/bin/sh

set -e

if command -v g++ >/dev/null 2>&1; then
	CXX_COMPILER="$(command -v g++)"
elif command -v clang++ >/dev/null 2>&1; then
	CXX_COMPILER="$(command -v clang++)"
elif command -v c++ >/dev/null 2>&1; then
	CXX_COMPILER="$(command -v c++)"
else
	echo "error: C++ compiler not found. Please install g++ or clang++." >&2
	exit 1
fi

if [ -f build/CMakeCache.txt ]; then
	CACHED_CXX="$(sed -n 's/^CMAKE_CXX_COMPILER:FILEPATH=//p' build/CMakeCache.txt)"
	if [ -n "$CACHED_CXX" ] && [ ! -x "$CACHED_CXX" ]; then
		rm -rf build
	fi
fi

cmake -S . -B build -DCMAKE_CXX_COMPILER="$CXX_COMPILER"
cmake --build build
./build/scop "$@"
