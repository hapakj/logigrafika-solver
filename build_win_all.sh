#!/bin/bash

set -e

PLATFORM=win-msvc2019-x64 CONFIG=Debug ./build.sh
PLATFORM=win-clang-x64 CONFIG=Debug ./build.sh

PLATFORM=win-msvc2019-x64 CONFIG=Release ./build.sh
PLATFORM=win-clang-x64 CONFIG=Release ./build.sh
