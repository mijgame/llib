#!/usr/bin/env bash

set -eu -o pipefail

echo "-- Installing CMake"
if [[ -f $HOME/cmake/$CMAKE_VERSION/bin/cmake ]]; then
echo "-- CMake $CMAKE_VERSION FOUND in cache"
else
echo "-- CMake $CMAKE_VERSION NOT FOUND in cache"
target_path=$HOME/cmake/$CMAKE_VERSION
cmake_url="https://cmake.org/files/v${CMAKE_VERSION%.*}/cmake-${CMAKE_VERSION}-Linux-x86_64.tar.gz"
mkdir -p "$target_path"
curl -Ls "$cmake_url" | tar -xz -C "$target_path" --strip-components=1
fi
echo "-- Done installing CMake"