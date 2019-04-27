#!/usr/bin/env bash

set -eu -o pipefail

echo "-- Installing CMake"
if [[ -f $HOME/cmake/$1/bin/cmake ]]; then
echo "-- CMake $1 FOUND in cache"
else
echo "-- CMake $1 NOT FOUND in cache"
target_path=$HOME/cmake/$1
cmake_url="https://cmake.org/files/v${1%.*}/cmake-${1}-Linux-x86_64.tar.gz"
mkdir -p "$target_path"
curl -Ls "$cmake_url" | tar -xz -C "$target_path" --strip-components=1
fi
echo "-- Done installing CMake"
