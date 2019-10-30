#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

print_header "RUN cppcheck"
if [ "${1}" == "--local" ]; then
    CPPCHECK="cppcheck"
else
    CPPCHECK="./3rdparty/linters/cppcheck/cppcheck"
fi
${CPPCHECK} project --enable=all --suppress=missingIncludeSystem

print_header "RUN cpplint.py"
python2.7 ./3rdparty/linters/cpplint/cpplint.py --extensions=c project/naive/* project/parallel/*

print_header "SUCCESS"