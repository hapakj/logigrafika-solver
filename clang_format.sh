#!/bin/bash

set -e

USED_CLANG_FORMAT="10.0.0"


CLANG_FORMAT_VERSION=$(clang-format --version | tr "-" " " | cut -d " " -f 4)

if [[ "$CLANG_FORMAT_VERSION" != "$USED_CLANG_FORMAT" ]]
then
  echo "Warning! clang-format $USED_CLANG_FORMAT is required"
  exit 1
fi

find . -regextype posix-extended -regex '.*\.(h|hpp|c|cpp)$' -type f -not -path "./out*" | xargs clang-format -i


